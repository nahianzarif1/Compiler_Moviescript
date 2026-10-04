#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "limits.h"
#include "value.h"
#define TABLE_SIZE 100

typedef struct Symbol {
    char name[MS_IDENTIFIER_MAX + 1];
    char type[32];
    Value value;
    int declaredLine;
    int initialized;
    struct Symbol* next;
} Symbol;

typedef struct SymbolState {
    Symbol* symbol;
    int before;
    int branch;
    struct SymbolState* next;
} SymbolState;

SymbolState* snapshotSymbols(void);
void restoreSymbols(SymbolState* state);
void saveBranchSymbols(SymbolState* state);
void mergeBranchSymbols(SymbolState* state, int thenReturns, int elseReturns);
void freeSymbolStates(SymbolState* state);
int isGlobalSymbol(const Symbol* symbol);
void initSymbolTable(void);
void freeSymbolTable(void);
void enterScope(void);
void enterFunctionScope(void);
void leaveScope(void);
Symbol* insertSymbolWithLine(const char* name, const char* type, int declaredLine);
Symbol* lookupSymbol(const char* name);
Symbol* lookupCurrentSymbol(const char* name);
int storeValue(Symbol* symbol, const Value* value, int line, const char* phase);
void printSymbolTable(void);

#endif
