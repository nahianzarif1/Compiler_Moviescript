#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"
#include "ir.h"

static int tempCounter;
static int labelCounter;
static int blockCounter;

static char* temporary(void)
{
    char text[32]; snprintf(text, sizeof(text), "t%d", tempCounter++); return msCopy(text);
}

static char* expressionIR(ASTNode* node)
{
    if (!node) return msCopy("_");
    if (node->type == NODE_VALUE) return msCopy(node->name ? node->name : node->value);
    char* result = temporary();
    if (node->type == NODE_CALL || node->type == NODE_BUILTIN) {
        /* Keep argument temporaries stable across nested calls. */
        int count = 0;
        for (ASTNode* arg = node->left; arg; arg = arg->next) ++count;
        char** args = msAlloc((count + 1UL) * sizeof(char*));
        int i = 0;
        for (ASTNode* arg = node->left; arg; arg = arg->next) args[i++] = expressionIR(arg);
        for (i = 0; i < count; ++i) { printf("ARG %s\n", args[i]); free(args[i]); }
        printf("%s = %s %s, %d\n", result, node->type == NODE_CALL ? "CALL" : "BUILTIN", node->name, count);
        free(args); return result;
    }
    char* left = expressionIR(node->left);
    if (node->type == NODE_UNARY_OP) printf("%s = %s %s\n", result, node->name, left);
    else if (!strcmp(node->name, "AND") || !strcmp(node->name, "OR")) {
        int skip = labelCounter++, end = labelCounter++;
        printf("IF %s == %s GOTO L%d\n", left, !strcmp(node->name, "AND") ? "FALSE" : "TRUE", skip);
        char* right = expressionIR(node->right);
        printf("%s = %s\nGOTO L%d\nL%d:\n%s = %s\nL%d:\n", result, right, end, skip, result, !strcmp(node->name, "AND") ? "FALSE" : "TRUE", end);
        free(right);
    } else {
        char* right = expressionIR(node->right);
        printf("%s = %s %s %s\n", result, left, node->name, right); free(right);
    }
    free(left); return result;
}

static void irList(ASTNode* node)
{
    for (; node; node = node->next) {
        switch (node->type) {
            case NODE_DECL:
            case NODE_ASSIGN: {
                if (node->type == NODE_DECL) printf("DECL %s %s\n", node->value, node->name);
                if (node->left) {
                    char* expr = expressionIR(node->left);
                    printf("CHECK_STORE %s, %s\n", node->name, expr); free(expr);
                }
                break;
            }
            case NODE_COLLECTION:
                printf("COLLECTION %s = {", node->name);
                for (ASTNode* item = node->left; item; item = item->next) printf("%s%s", item == node->left ? "" : ", ", item->value);
                puts("}"); break;
            case NODE_COLLECTION_ADD: {
                char* value = expressionIR(node->left); printf("ADD_TO %s, %s\n", node->name, value); free(value); break;
            }
            case NODE_FUNCTION:
                printf("FUNCTION %s RETURNS %s\n", node->name, node->value);
                for (ASTNode* p = node->left; p; p = p->next) printf("CHECK_PARAM %s %s\n", p->value, p->name);
                irList(node->right); printf("END_FUNCTION %s\n", node->name); break;
            case NODE_RETURN: {
                char* value = expressionIR(node->left); printf("CHECK_RETURN %s\n", value); free(value); break;
            }
            case NODE_CALL: { char* value = expressionIR(node); free(value); break; }
            case NODE_ACTION:
                if (node->value && !strcmp(node->value, "ANALYZE")) printf("ANALYZE %s\n", node->name);
                else if (node->left) {
                    char* value = expressionIR(node->left);
                    printf("%s %s", node->name, value);
                    if (node->value) printf(", %s", node->value);
                    putchar('\n'); free(value);
                } else printf("%s\n", node->name);
                break;
            case NODE_IF: {
                int other = labelCounter++, end = labelCounter++;
                char* condition = expressionIR(node->left);
                printf("IF_FALSE %s GOTO L%d\nSCOPE_BEGIN\n", condition, other); free(condition);
                irList(node->right);
                printf("SCOPE_END\nGOTO L%d\nL%d:\nSCOPE_BEGIN\n", end, other);
                irList(node->elseBranch); printf("SCOPE_END\nL%d:\n", end); break;
            }
            case NODE_WHILE: {
                int start = labelCounter++, end = labelCounter++;
                printf("L%d:\n", start);
                char* condition = expressionIR(node->left);
                printf("IF_FALSE %s GOTO L%d\nSCOPE_BEGIN\n", condition, end); free(condition);
                irList(node->right); printf("SCOPE_END\nGOTO L%d\nL%d:\n", start, end); break;
            }
            case NODE_FOR: {
                int start = labelCounter++, end = labelCounter++;
                char* iterator = temporary();
                printf("%s = ITER_SNAPSHOT %s\nL%d:\nIF_DONE %s GOTO L%d\nSCOPE_BEGIN\n", iterator, node->name, start, iterator, end);
                if (node->value) printf("GENRE %s = CURRENT %s\n", node->value, iterator);
                irList(node->right); printf("SCOPE_END\nNEXT %s\nGOTO L%d\nL%d:\n", iterator, start, end); free(iterator); break;
            }
            default: break;
        }
    }
}

static ASTNode* statements(ASTNode* root)
{
    return root && root->type == NODE_PROGRAM && root->left ? root->left->left : root;
}

void generateIR(ASTNode* root) { tempCounter = labelCounter = 0; irList(statements(root)); }

static int block(void) { return blockCounter++; }
static void edge(int from, int to, const char* label)
{
    printf("B%d -> B%d", from, to);
    if (label) printf(" [%s]", label);
    putchar('\n');
}

/* Return the actual fall-through block; -1 means the path returned. */
static int cfgList(ASTNode* node, int entry)
{
    int current = entry;
    for (; node; node = node->next) {
        if (node->type == NODE_FUNCTION) continue;
        if (current < 0) break;
        if (node->type == NODE_IF) {
            printf("B%d: IF [line %d]\n", current, node->line);
            int yes = block(), no = block();
            edge(current, yes, "true"); edge(current, no, "false");
            int yesEnd = cfgList(node->right, yes), noEnd = cfgList(node->elseBranch, no);
            if (yesEnd < 0 && noEnd < 0) current = -1;
            else {
                current = block();
                if (yesEnd >= 0) edge(yesEnd, current, NULL);
                if (noEnd >= 0) edge(noEnd, current, NULL);
            }
        } else if (node->type == NODE_WHILE || node->type == NODE_FOR) {
            printf("B%d: %s [line %d]\n", current, nodeTypeName(node->type), node->line);
            int body = block(), exit = block();
            edge(current, body, node->type == NODE_FOR ? "item available" : "true");
            edge(current, exit, node->type == NODE_FOR ? "exhausted" : "false");
            int tail = cfgList(node->right, body);
            if (tail >= 0) edge(tail, current, "loop");
            current = exit;
        } else {
            printf("B%d: %s [line %d]\n", current, nodeTypeName(node->type), node->line);
            if (node->type == NODE_RETURN) current = -1;
            else {
                int next = block(); edge(current, next, NULL); current = next;
            }
        }
    }
    if (current >= 0) printf("B%d: fall-through\n", current);
    return current;
}

void generateCFG(ASTNode* root)
{
    blockCounter = 0;
    ASTNode* list = statements(root);
    int entry = block(); printf("B%d: screenplay entry\n", entry); cfgList(list, entry);
    for (ASTNode* n = list; n; n = n->next) {
        if (n->type == NODE_FUNCTION) {
            entry = block(); printf("B%d: function %s entry\n", entry, n->name); cfgList(n->right, entry);
        }
    }
}

void generateFunctionIndex(ASTNode* root)
{
    for (ASTNode* n = statements(root); n; n = n->next) {
        if (n->type != NODE_FUNCTION) continue;
        printf("%s(", n->name);
        for (ASTNode* p = n->left; p; p = p->next) printf("%s%s %s", p == n->left ? "" : ", ", p->value, p->name);
        printf(") RETURNS %s [line %d]\n", n->value, n->line);
    }
}
