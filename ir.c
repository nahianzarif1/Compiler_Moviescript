#include <stdio.h>
#include <string.h>
#include "ir.h"

static int tempCounter = 0;
static int labelCounter = 0;

static int nextTemp(void)
{
    return tempCounter++;
}

static int nextLabel(void)
{
    return labelCounter++;
}

static const char* valueName(ASTNode* node)
{
    if (node == NULL) {
        return "_";
    }

    if (node->name != NULL) {
        return node->name;
    }

    if (node->value != NULL) {
        return node->value;
    }

    return "_";
}

static void generateIRList(ASTNode* node);
static void generateCFGList(ASTNode* node, int parentBlock);

static void generateConditionIR(ASTNode* node, int trueLabel, int falseLabel)
{
    if (node == NULL) {
        return;
    }

    if (node->name != NULL && strcmp(node->name, "RISING") == 0) {
        printf("IF %s RISING GOTO L%d\n", valueName(node->left), trueLabel);
    } else {
        printf("IF %s > %s GOTO L%d\n", valueName(node->left), valueName(node->right), trueLabel);
    }
    printf("GOTO L%d\n", falseLabel);
}

static void generateSingleIR(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case NODE_DECL:
            if (node->left != NULL) {
                printf("DECL %s %s = %s\n", node->value, node->name, valueName(node->left));
            } else {
                printf("DECL %s %s\n", node->value, node->name);
            }
            break;

        case NODE_ASSIGN: {
            int temp = nextTemp();
            printf("t%d = %s\n", temp, valueName(node->left));
            printf("%s = t%d\n", node->name, temp);
            break;
        }

        case NODE_BINARY_OP: {
            int temp = nextTemp();
            printf("t%d = %s %s %s\n", temp, valueName(node->left), node->name != NULL ? node->name : "?", valueName(node->right));
            break;
        }

        case NODE_ACTION:
            if (node->value != NULL) {
                printf("CALL %s, %s\n", node->name, node->value);
            } else if (node->left != NULL && node->name != NULL && strcmp(node->name, "PRINT") == 0) {
                printf("PRINT %s\n", valueName(node->left));
            } else {
                printf("CALL %s\n", node->name);
            }
            break;

        case NODE_FUNCTION:
            printf("FUNCTION %s RETURNS %s\n", node->name, node->value != NULL ? node->value : "UNKNOWN");
            generateIRList(node->right);
            printf("END_FUNCTION %s\n", node->name);
            break;

        case NODE_RETURN:
            if (node->left != NULL && node->left->type == NODE_BINARY_OP) {
                int temp = nextTemp();
                printf("t%d = %s %s %s\n", temp, valueName(node->left->left), node->left->name != NULL ? node->left->name : "?", valueName(node->left->right));
                printf("RETURN t%d\n", temp);
            } else if (node->left != NULL && node->left->type == NODE_CALL) {
                printf("RETURN %s\n", node->left->name != NULL ? node->left->name : "<call>");
            } else {
                printf("RETURN %s\n", valueName(node->left));
            }
            break;

        case NODE_CALL:
            printf("CALL %s\n", node->name != NULL ? node->name : "<anonymous>");
            break;

        case NODE_COLLECTION: {
            printf("COLLECTION %s = { ", node->name);
            ASTNode* item = node->left;
            int first = 1;
            while (item != NULL) {
                if (!first) {
                    printf(", ");
                }
                printf("%s", valueName(item));
                first = 0;
                item = item->next;
            }
            printf(" }\n");
            break;
        }

        case NODE_COLLECTION_ADD:
            printf("ADD_TO %s, %s\n", node->name, node->value != NULL ? node->value : "_");
            break;

        case NODE_IF: {
            int trueLabel = nextLabel();
            int falseLabel = nextLabel();
            int endLabel = nextLabel();
            generateConditionIR(node->left, trueLabel, falseLabel);
            printf("L%d:\n", trueLabel);
            generateIRList(node->right);
            printf("GOTO L%d\n", endLabel);
            printf("L%d:\n", falseLabel);
            generateIRList(node->elseBranch);
            printf("L%d:\n", endLabel);
            break;
        }

        case NODE_WHILE: {
            int startLabel = nextLabel();
            int bodyLabel = nextLabel();
            int endLabel = nextLabel();
            printf("L%d:\n", startLabel);
            generateConditionIR(node->left, bodyLabel, endLabel);
            printf("L%d:\n", bodyLabel);
            generateIRList(node->right);
            printf("GOTO L%d\n", startLabel);
            printf("L%d:\n", endLabel);
            break;
        }

        case NODE_FOR: {
            int loopLabel = nextLabel();
            int endLabel = nextLabel();
            printf("ITER %s\n", node->name != NULL ? node->name : "_");
            printf("L%d:\n", loopLabel);
            generateIRList(node->right);
            printf("NEXT %s\n", node->name != NULL ? node->name : "_");
            printf("IF_MORE %s GOTO L%d\n", node->name != NULL ? node->name : "_", loopLabel);
            printf("L%d:\n", endLabel);
            break;
        }

        default:
            break;
    }
}

static void generateIRList(ASTNode* node)
{
    ASTNode* current = node;
    while (current != NULL) {
        generateSingleIR(current);
        current = current->next;
    }
}

void generateIR(ASTNode* node)
{
    tempCounter = 0;
    labelCounter = 0;

    if (node == NULL) {
        return;
    }

    if (node->type == NODE_PROGRAM && node->left != NULL) {
        generateIR(node->left);
        return;
    }

    if (node->type == NODE_SCREENPLAY) {
        generateIRList(node->left);
        return;
    }

    generateIRList(node);
}

static int nextBlockId(void)
{
    static int blockCounter = 0;
    return blockCounter++;
}

static void printBlockEdge(int from, int to, const char* label)
{
    if (label != NULL) {
        printf("B%d -> B%d [%s]\n", from, to, label);
    } else {
        printf("B%d -> B%d\n", from, to);
    }
}

static void generateCFGNode(ASTNode* node, int currentBlock)
{
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case NODE_IF: {
            int thenBlock = nextBlockId();
            int elseBlock = nextBlockId();
            int joinBlock = nextBlockId();
            printf("B%d: IF %s\n", currentBlock, node->left != NULL ? valueName(node->left) : "condition");
            printBlockEdge(currentBlock, thenBlock, "true");
            printBlockEdge(currentBlock, elseBlock, "false");
            generateCFGList(node->right, thenBlock);
            printBlockEdge(thenBlock, joinBlock, NULL);
            generateCFGList(node->elseBranch, elseBlock);
            printBlockEdge(elseBlock, joinBlock, NULL);
            break;
        }

        case NODE_WHILE: {
            int bodyBlock = nextBlockId();
            int exitBlock = nextBlockId();
            printf("B%d: WHILE %s\n", currentBlock, node->left != NULL ? valueName(node->left) : "condition");
            printBlockEdge(currentBlock, bodyBlock, "true");
            printBlockEdge(currentBlock, exitBlock, "false");
            generateCFGList(node->right, bodyBlock);
            printBlockEdge(bodyBlock, currentBlock, "loop");
            break;
        }

        case NODE_FUNCTION: {
            printf("B%d: FUNCTION %s\n", currentBlock, node->name != NULL ? node->name : "<anonymous>");
            generateCFGList(node->right, currentBlock);
            break;
        }

        default:
            printf("B%d: %s\n", currentBlock, nodeTypeName(node->type));
            break;
    }
}

static void generateCFGList(ASTNode* node, int parentBlock)
{
    ASTNode* current = node;
    int activeBlock = parentBlock;
    while (current != NULL) {
        generateCFGNode(current, activeBlock);
        if (current->next != NULL) {
            int nextBlock = nextBlockId();
            printBlockEdge(activeBlock, nextBlock, NULL);
            activeBlock = nextBlock;
        }
        current = current->next;
    }
}

void generateCFG(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_PROGRAM && node->left != NULL) {
        generateCFG(node->left);
        return;
    }

    if (node->type == NODE_SCREENPLAY) {
        generateCFGList(node->left, nextBlockId());
        return;
    }

    generateCFGList(node, nextBlockId());
}

void generateFunctionIndex(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_FUNCTION) {
        printf("FUNCTION %s (%s)\n", node->name != NULL ? node->name : "<anonymous>", node->value != NULL ? node->value : "UNKNOWN");
    }

    generateFunctionIndex(node->left);
    generateFunctionIndex(node->right);
    generateFunctionIndex(node->elseBranch);
    generateFunctionIndex(node->next);
}