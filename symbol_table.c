#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol* table[TABLE_SIZE];

static int hash(const char* str)
{
	int h = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		h = (h * 31 + (unsigned char)str[i]) % TABLE_SIZE;
	}
	return h;
}

void initSymbolTable(void)
{
	for (int i = 0; i < TABLE_SIZE; ++i) {
		table[i] = NULL;
	}
}

void insertSymbol(const char* name, const char* type)
{
	insertSymbolWithLine(name, type, 0);
}

void insertSymbolWithLine(const char* name, const char* type, int declaredLine)
{
	if (name == NULL || type == NULL || lookupSymbol(name) != NULL) {
		return;
	}

	int h = hash(name);
	Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
	if (symbol == NULL) {
		fprintf(stderr, "Fatal Error: unable to allocate symbol\n");
		exit(EXIT_FAILURE);
	}

	strncpy(symbol->name, name, sizeof(symbol->name) - 1);
	symbol->name[sizeof(symbol->name) - 1] = '\0';
	strncpy(symbol->type, type, sizeof(symbol->type) - 1);
	symbol->type[sizeof(symbol->type) - 1] = '\0';
	symbol->value[0] = '\0';
	symbol->declaredLine = declaredLine;
	symbol->next = table[h];
	table[h] = symbol;
}

Symbol* lookupSymbol(const char* name)
{
	if (name == NULL) {
		return NULL;
	}

	int h = hash(name);
	Symbol* current = table[h];

	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}

	return NULL;
}

void setValue(const char* name, const char* value)
{
	Symbol* symbol = lookupSymbol(name);
	if (symbol == NULL || value == NULL) {
		return;
	}

	strncpy(symbol->value, value, sizeof(symbol->value) - 1);
	symbol->value[sizeof(symbol->value) - 1] = '\0';
}

void printSymbolTable(void)
{
	printf("\nSymbol Table:\n");

	for (int i = 0; i < TABLE_SIZE; ++i) {
		Symbol* current = table[i];
		while (current != NULL) {
			printf("%s %s %s", current->name, current->type, current->value);
			if (current->declaredLine > 0) {
				printf(" (declared at line %d)", current->declaredLine);
			}
			printf("\n");
			current = current->next;
		}
	}
}