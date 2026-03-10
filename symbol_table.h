#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TABLE_SIZE 100

typedef struct Symbol {
	char name[64];
	char type[32];
	char value[128];
	int declaredLine;
	struct Symbol* next;
} Symbol;

void initSymbolTable(void);
void insertSymbol(const char* name, const char* type);
void insertSymbolWithLine(const char* name, const char* type, int declaredLine);
Symbol* lookupSymbol(const char* name);
void setValue(const char* name, const char* value);
void printSymbolTable(void);

#endif