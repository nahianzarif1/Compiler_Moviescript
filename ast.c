#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "diagnostic.h"
#include "limits.h"

ASTNode* createNode(NodeType type, const char* name, const char* value)
{
	return createNodeWithLine(type, name, value, 0);
}

ASTNode* createNodeWithLine(NodeType type, const char* name, const char* value, int line)
{
	ASTNode* node = msAlloc(sizeof(ASTNode));
	node->type = type;
	node->name = msCopy(name);
	node->value = msCopy(value);
	node->line = line;
	node->left = NULL;
	node->right = NULL;
	node->elseBranch = NULL;
	node->next = NULL;
	node->tail = node;

	return node;
}

void addChild(ASTNode* parent, ASTNode* child)
{
	if (parent == NULL || child == NULL) {
		return;
	}

	if (parent->left == NULL) {
		parent->left = child;
	} else if (parent->right == NULL) {
		parent->right = child;
	} else {
		appendSibling(parent->right, child);
	}
}

void appendSibling(ASTNode* node, ASTNode* sibling)
{
	if (node == NULL || sibling == NULL) {
		return;
	}

    node->tail->next = sibling;
    node->tail = sibling->tail;
}

void setNodeValue(ASTNode* node, const char* value)
{
	if (node == NULL) {
		return;
	}

	free(node->value);
	node->value = msCopy(value);
}

static void printIndent(int level)
{
	for (int i = 0; i < level; ++i) {
		printf("  ");
	}
}

const char* nodeTypeName(NodeType type)
{
	switch (type) {
		case NODE_PROGRAM: return "PROGRAM";
		case NODE_SCREENPLAY: return "SCREENPLAY";
		case NODE_STATEMENTS: return "STATEMENTS";
		case NODE_DECL: return "DECLARATION";
		case NODE_ASSIGN: return "ASSIGNMENT";
		case NODE_BINARY_OP: return "BINARY_OP";
		case NODE_UNARY_OP: return "UNARY_OP";
		case NODE_BUILTIN: return "BUILTIN";
		case NODE_IF: return "IF";
		case NODE_CONDITION: return "CONDITION";
		case NODE_WHILE: return "WHILE";
		case NODE_FOR: return "FOREACH";
		case NODE_COLLECTION: return "COLLECTION";
		case NODE_COLLECTION_ADD: return "COLLECTION_ADD";
		case NODE_FUNCTION: return "FUNCTION";
		case NODE_PARAM: return "PARAM";
		case NODE_RETURN: return "RETURN";
		case NODE_CALL: return "CALL";
		case NODE_ACTION: return "ACTION";
		case NODE_VALUE: return "VALUE";
		default: return "UNKNOWN";
	}
}

void printAST(ASTNode* node, int level)
{
    for (; node; node = node->next) {
        printIndent(level);
        printf("%s", nodeTypeName(node->type));
        if (node->name) printf(" (%s)", node->name);
        if (node->value) printf(" = %s", node->value);
        if (node->line > 0) printf(" [line %d]", node->line);
        putchar('\n');
        printAST(node->left, level + 1);
        printAST(node->right, level + 1);
        if (node->elseBranch) {
            printIndent(level + 1); puts("ELSE");
            printAST(node->elseBranch, level + 2);
        }
    }
}

void freeAST(ASTNode* node)
{
    /* Flatten children into a work list, avoiding recursion on malformed input. */
    while (node) {
        ASTNode* pending = node->next;
        if (node->left) { ASTNode* tail = node->left; while (tail->next) tail = tail->next; tail->next = pending; pending = node->left; }
        if (node->right) { ASTNode* tail = node->right; while (tail->next) tail = tail->next; tail->next = pending; pending = node->right; }
        if (node->elseBranch) { ASTNode* tail = node->elseBranch; while (tail->next) tail = tail->next; tail->next = pending; pending = node->elseBranch; }
        free(node->name); free(node->value); free(node); node = pending;
    }
}

int validateAST(ASTNode* root)
{
    typedef struct { ASTNode* node; int depth; } Visit;
    Visit* stack = msAlloc((MS_AST_NODE_MAX + 4UL) * sizeof(Visit));
    size_t size = 0, count = 0;
    int valid = 1;
    if (root) stack[size++] = (Visit){root, 1};
    while (size) {
        Visit visit = stack[--size];
        if (++count > MS_AST_NODE_MAX || visit.depth > MS_AST_DEPTH_MAX) {
            reportError("Input Error", visit.node->line, "program exceeds %d AST nodes or %d nesting levels", MS_AST_NODE_MAX, MS_AST_DEPTH_MAX);
            valid = 0; break;
        }
        ASTNode* n = visit.node;
        if (n->next) stack[size++] = (Visit){n->next, visit.depth};
        if (n->left) stack[size++] = (Visit){n->left, visit.depth + 1};
        if (n->right) stack[size++] = (Visit){n->right, visit.depth + 1};
        if (n->elseBranch) stack[size++] = (Visit){n->elseBranch, visit.depth + 1};
    }
    free(stack); return valid;
}
