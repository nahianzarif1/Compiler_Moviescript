#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol_table.h"

static int isQuotedString(const char* text)
{
    size_t len = text != NULL ? strlen(text) : 0;
    return len >= 2 && text[0] == '"' && text[len - 1] == '"';
}

static int isNumericLiteral(const char* text)
{
    if (text == NULL || *text == '\0') {
        return 0;
    }

    int seenDot = 0;
    for (const char* p = text; *p != '\0'; ++p) {
        if (*p == '.') {
            if (seenDot) {
                return 0;
            }
            seenDot = 1;
        } else if (*p < '0' || *p > '9') {
            return 0;
        }
    }
    return 1;
}

static double numericValue(const char* text)
{
    return strtod(text, NULL);
}

static void formatNumber(double value, char* buffer, size_t bufferSize)
{
    snprintf(buffer, bufferSize, "%.6f", value);
    for (int i = (int)strlen(buffer) - 1; i > 0 && buffer[i] == '0'; --i) {
        buffer[i] = '\0';
    }
    if (buffer[strlen(buffer) - 1] == '.') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

static int isNumericType(const char* type)
{
    return type != NULL && (
        strcmp(type, "RATING") == 0 ||
        strcmp(type, "BUDGET") == 0 ||
        strcmp(type, "WHOLE") == 0
    );
}

static const char* inferExpressionType(ASTNode* node)
{
    if (node == NULL) {
        return "UNKNOWN";
    }

    if (node->type == NODE_VALUE) {
        if (node->name != NULL) {
            Symbol* symbol = lookupSymbol(node->name);
            return symbol != NULL ? symbol->type : "UNKNOWN";
        }

        if (node->value != NULL) {
            if (isQuotedString(node->value)) {
                return "DIALOGUE";
            }

            if (isNumericLiteral(node->value)) {
                return "RATING";
            }
        }
    }

    if (node->type == NODE_BINARY_OP) {
        const char* leftType = inferExpressionType(node->left);
        const char* rightType = inferExpressionType(node->right);
        if (isNumericType(leftType) && isNumericType(rightType)) {
            return "RATING";
        }
    }

    return "UNKNOWN";
}

static void checkDeadCode(ASTNode* condition)
{
    if (condition == NULL || condition->type != NODE_CONDITION || condition->value == NULL) {
        return;
    }

    Symbol* symbol = condition->name != NULL ? lookupSymbol(condition->name) : NULL;
    if (symbol == NULL) {
        return;
    }

    if (strcmp(symbol->type, "RATING") == 0 && isNumericLiteral(condition->value) && numericValue(condition->value) > 10.0) {
        printf("Warning at line %d: dead code detected because RATING %s cannot be greater than 10\n", condition->line, condition->name);
    }
}

void foldConstants(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    foldConstants(node->left);
    foldConstants(node->right);
    foldConstants(node->next);

    if (node->type == NODE_BINARY_OP && node->left != NULL && node->right != NULL &&
        node->left->type == NODE_VALUE && node->right->type == NODE_VALUE &&
        node->left->value != NULL && node->right->value != NULL &&
        isNumericLiteral(node->left->value) && isNumericLiteral(node->right->value)) {
        double lhs = numericValue(node->left->value);
        double rhs = numericValue(node->right->value);
        double result = 0.0;
        int valid = 1;

        if (strcmp(node->name, "+") == 0) {
            result = lhs + rhs;
        } else if (strcmp(node->name, "-") == 0) {
            result = lhs - rhs;
        } else if (strcmp(node->name, "*") == 0) {
            result = lhs * rhs;
        } else if (strcmp(node->name, "/") == 0) {
            if (rhs == 0.0) {
                valid = 0;
            } else {
                result = lhs / rhs;
            }
        } else {
            valid = 0;
        }

        if (valid) {
            char buffer[64];
            formatNumber(result, buffer, sizeof(buffer));
            free(node->name);
            node->name = NULL;
            setNodeValue(node, buffer);
            freeAST(node->left);
            freeAST(node->right);
            node->left = NULL;
            node->right = NULL;
            node->type = NODE_VALUE;
        }
    }
}

void checkIdentifierUsage(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_VALUE && node->name != NULL) {
        if (lookupSymbol(node->name) == NULL) {
            printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->name);
        }
    }

    if (node->type == NODE_ACTION && node->name != NULL && strcmp(node->name, "ANALYZE") == 0 && node->value != NULL) {
        if (lookupSymbol(node->value) == NULL) {
            printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->value);
        }
    }

    if (node->type == NODE_CONDITION && node->name != NULL) {
        if (lookupSymbol(node->name) == NULL) {
            printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->name);
        }
    }

    if (node->type == NODE_ASSIGN && node->name != NULL) {
        if (lookupSymbol(node->name) == NULL) {
            printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->name);
        }
    }

    if (node->type == NODE_COLLECTION_ADD && node->name != NULL) {
        if (lookupSymbol(node->name) == NULL) {
            printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->name);
        }
    }
}

static void checkAssignment(ASTNode* node)
{
    Symbol* symbol = lookupSymbol(node->name);

    if (symbol == NULL) {
        printf("Semantic Error at line %d: undefined variable %s\n", node->line, node->name);
        return;
    }

    const char* rhsType = inferExpressionType(node->left);
    if (strcmp(rhsType, "UNKNOWN") == 0) {
        return;
    }

    if (strcmp(symbol->type, rhsType) == 0) {
        return;
    }

    if (isNumericType(symbol->type) && isNumericType(rhsType)) {
        return;
    }

    printf("Type Error at line %d: cannot assign %s to %s variable %s\n",
           node->line,
           rhsType,
           symbol->type,
           node->name);
}

void semanticCheck(ASTNode* node)
{
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_DECL) {
        if (lookupSymbol(node->name) != NULL) {
            printf("Semantic Error at line %d: duplicate variable %s\n", node->line, node->name);
        } else {
            insertSymbolWithLine(node->name, node->value, node->line);
            if (node->left != NULL && node->left->value != NULL) {
                const char* rhsType = inferExpressionType(node->left);
                if (strcmp(node->value, rhsType) == 0 || (isNumericType(node->value) && isNumericType(rhsType))) {
                    setValue(node->name, node->left->value);
                } else if (strcmp(rhsType, "UNKNOWN") != 0) {
                    printf("Type Error at line %d: cannot assign %s to %s variable %s\n",
                           node->line,
                           rhsType,
                           node->value,
                           node->name);
                }
            }
        }
    }

    if (node->type == NODE_COLLECTION) {
        if (lookupSymbol(node->name) != NULL) {
            printf("Semantic Error at line %d: duplicate variable %s\n", node->line, node->name);
        } else {
            insertSymbolWithLine(node->name, node->value, node->line);
        }
    }

    if (node->type == NODE_ASSIGN) {
        checkAssignment(node);
        if (lookupSymbol(node->name) != NULL && node->value != NULL) {
            setValue(node->name, node->value);
        }
    }

    if (node->type == NODE_IF || node->type == NODE_WHILE) {
        checkDeadCode(node->left);
    }

    if (node->type != NODE_DECL) {
        if (node->type == NODE_ASSIGN || node->type == NODE_IF || node->type == NODE_WHILE || node->type == NODE_FOR || node->type == NODE_COLLECTION || node->type == NODE_COLLECTION_ADD || node->type == NODE_ACTION || node->type == NODE_CONDITION) {
            checkIdentifierUsage(node);
        }
    }

    semanticCheck(node->left);
    semanticCheck(node->right);
    semanticCheck(node->next);
}