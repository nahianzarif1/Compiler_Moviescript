#ifndef AST_H
#define AST_H

typedef enum {
	NODE_PROGRAM,
	NODE_SCREENPLAY,
	NODE_STATEMENTS,
	NODE_DECL,
	NODE_ASSIGN,
	NODE_BINARY_OP,
	NODE_UNARY_OP,
	NODE_BUILTIN,
	NODE_IF,
	NODE_CONDITION,
	NODE_WHILE,
	NODE_FOR,
	NODE_COLLECTION,
	NODE_COLLECTION_ADD,
	NODE_FUNCTION,
	NODE_PARAM,
	NODE_RETURN,
	NODE_CALL,
	NODE_ACTION,
	NODE_VALUE
} NodeType;

typedef struct ASTNode {
	NodeType type;
	char* name;
	char* value;
	int line;
	struct ASTNode* left;
	struct ASTNode* right;
	struct ASTNode* elseBranch;
	struct ASTNode* next;
	struct ASTNode* tail; /* Cached tail for constant-time list construction. */
} ASTNode;

ASTNode* createNode(NodeType type, const char* name, const char* value);
ASTNode* createNodeWithLine(NodeType type, const char* name, const char* value, int line);
void addChild(ASTNode* parent, ASTNode* child);
void appendSibling(ASTNode* node, ASTNode* sibling);
void setNodeValue(ASTNode* node, const char* value);
const char* nodeTypeName(NodeType type);
int validateAST(ASTNode* root);
void printAST(ASTNode* node, int level);
void freeAST(ASTNode* node);

#endif
