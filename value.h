#ifndef MOVIESCRIPT_VALUE_H
#define MOVIESCRIPT_VALUE_H
#include <stddef.h>

typedef enum {
    VALUE_NONE, VALUE_NUMBER, VALUE_TEXT, VALUE_STATUS, VALUE_SIGNAL, VALUE_COLLECTION
} ValueKind;

typedef struct {
    ValueKind kind;
    double number;
    char* text;
    char** items;
    size_t count;
} Value;

Value numberValue(double number);
Value signalValue(int truth);
Value textValue(const char* text);
Value copyValue(const Value* value);
void freeValue(Value* value);
int parseLiteral(const char* literal, Value* result, int line, const char* phase);
ValueKind typeKind(const char* type);
const char* kindName(ValueKind kind);
int validateValue(const char* type, const Value* value, int line, const char* target, const char* phase);
int applyUnary(const char* op, const Value* input, Value* result, int line, const char* phase);
int applyBinary(const char* op, const Value* left, const Value* right, Value* result, int line, const char* phase);
int applyBuiltin(const char* name, const Value* args, int count, Value* result, int line, const char* phase);
int appendItem(Value* collection, const char* text, int line, const char* phase);
void printValue(const Value* value);

#endif
