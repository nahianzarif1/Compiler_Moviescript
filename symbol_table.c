#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"
#include "symbol_table.h"

typedef struct Scope {
    Symbol* table[TABLE_SIZE];
    struct Scope* parent;   /* Lexical lookup chain. */
    struct Scope* previous; /* Execution/analysis stack. */
} Scope;

static Scope* currentScope;
static Scope* globalScope;

static unsigned hash(const char* str)
{
    unsigned h = 0;
    for (; *str; ++str) h = (h * 31 + (unsigned char)*str) % TABLE_SIZE;
    return h;
}

void enterScope(void)
{
    Scope* scope = msAlloc(sizeof(Scope));
    scope->parent = scope->previous = currentScope;
    currentScope = scope;
    if (globalScope == NULL) globalScope = scope;
}

void enterFunctionScope(void)
{
    Scope* caller = currentScope;
    enterScope();
    currentScope->parent = globalScope;
    currentScope->previous = caller;
}

void leaveScope(void)
{
    if (!currentScope) return;
    Scope* old = currentScope;
    currentScope = old->previous;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Symbol* s = old->table[i];
        while (s) { Symbol* next = s->next; freeValue(&s->value); free(s); s = next; }
    }
    if (old == globalScope) globalScope = NULL;
    free(old);
}

void freeSymbolTable(void) { while (currentScope) leaveScope(); }
void initSymbolTable(void) { freeSymbolTable(); enterScope(); }

static Symbol* findInScope(Scope* scope, const char* name)
{
    if (!scope || !name) return NULL;
    for (Symbol* s = scope->table[hash(name)]; s; s = s->next)
        if (!strcmp(s->name, name)) return s;
    return NULL;
}

Symbol* lookupCurrentSymbol(const char* name) { return findInScope(currentScope, name); }
Symbol* lookupSymbol(const char* name)
{
    for (Scope* scope = currentScope; scope; scope = scope->parent) {
        Symbol* s = findInScope(scope, name);
        if (s) return s;
    }
    return NULL;
}

Symbol* insertSymbolWithLine(const char* name, const char* type, int line)
{
    if (!name || !type || !currentScope) return NULL;
    if (strlen(name) > MS_IDENTIFIER_MAX || strlen(type) >= sizeof(((Symbol*)0)->type)) {
        reportError("Semantic Error", line, "identifier or type exceeds its length limit"); return NULL;
    }
    if (lookupCurrentSymbol(name)) {
        reportError("Semantic Error", line, "duplicate variable %s", name); return NULL;
    }
    Symbol* s = msAlloc(sizeof(Symbol));
    strcpy(s->name, name); strcpy(s->type, type);
    s->declaredLine = line;
    unsigned h = hash(name);
    s->next = currentScope->table[h]; currentScope->table[h] = s;
    return s;
}

int storeValue(Symbol* s, const Value* value, int line, const char* phase)
{
    if (!s || !validateValue(s->type, value, line, s->name, phase)) return 0;
    Value copy = copyValue(value);
    freeValue(&s->value); s->value = copy; s->initialized = 1;
    return 1;
}

void printSymbolTable(void)
{
    printf("%-24s %-18s %-8s %s\n", "Identifier", "Type", "Line", "Value");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        for (Symbol* s = globalScope ? globalScope->table[i] : NULL; s; s = s->next) {
            printf("%-24s %-18s %-8d ", s->name, s->type, s->declaredLine);
            if (s->initialized && s->value.kind == VALUE_NONE) fputs("<initialized; value not evaluated>", stdout);
            else printValue(&s->value);
            putchar('\n');
        }
    }
}

int isGlobalSymbol(const Symbol* symbol)
{
    return globalScope && findInScope(globalScope, symbol->name) == symbol;
}

SymbolState* snapshotSymbols(void)
{
    SymbolState* head = NULL;
    for (Scope* scope = currentScope; scope; scope = scope->parent) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (Symbol* s = scope->table[i]; s; s = s->next) {
                SymbolState* state = msAlloc(sizeof(SymbolState));
                state->symbol = s; state->before = s->initialized;
                state->next = head; head = state;
            }
        }
    }
    return head;
}
void restoreSymbols(SymbolState* state)
{
    for (; state; state = state->next) state->symbol->initialized = state->before;
}
void saveBranchSymbols(SymbolState* state)
{
    for (; state; state = state->next) {
        state->branch = state->symbol->initialized;
        state->symbol->initialized = state->before;
    }
}
void mergeBranchSymbols(SymbolState* state, int thenReturns, int elseReturns)
{
    for (; state; state = state->next) {
        if (thenReturns) continue;
        if (elseReturns) state->symbol->initialized = state->branch;
        else state->symbol->initialized = state->branch && state->symbol->initialized;
    }
}
void freeSymbolStates(SymbolState* state)
{
    while (state) { SymbolState* next = state->next; free(state); state = next; }
}
