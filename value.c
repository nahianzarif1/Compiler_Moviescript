#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"
#include "limits.h"
#include "value.h"

Value numberValue(double number) { Value v = {0}; v.kind = VALUE_NUMBER; v.number = number; return v; }
Value signalValue(int truth) { Value v = {0}; v.kind = VALUE_SIGNAL; v.number = !!truth; return v; }
Value textValue(const char* text) { Value v = {0}; v.kind = VALUE_TEXT; v.text = msCopy(text); return v; }

void freeValue(Value* v)
{
    free(v->text);
    for (size_t i = 0; i < v->count; ++i) free(v->items[i]);
    free(v->items);
    memset(v, 0, sizeof(*v));
}

Value copyValue(const Value* v)
{
    Value copy = *v;
    copy.text = msCopy(v->text);
    copy.items = NULL;
    if (v->count) {
        copy.items = msAlloc(v->count * sizeof(char*));
        for (size_t i = 0; i < v->count; ++i) copy.items[i] = msCopy(v->items[i]);
    }
    return copy;
}

ValueKind typeKind(const char* type)
{
    if (!strcmp(type, "RATING") || !strcmp(type, "BUDGET") || !strcmp(type, "WHOLE")) return VALUE_NUMBER;
    if (!strcmp(type, "CHARACTER") || !strcmp(type, "SCENE") || !strcmp(type, "DIALOGUE") || !strcmp(type, "GENRE")) return VALUE_TEXT;
    if (!strcmp(type, "STATUS")) return VALUE_STATUS;
    if (!strcmp(type, "SIGNAL")) return VALUE_SIGNAL;
    if (!strcmp(type, "GENRE_COLLECTION")) return VALUE_COLLECTION;
    return VALUE_NONE;
}

const char* kindName(ValueKind kind)
{
    const char* names[] = {"uninitialized", "number", "text", "STATUS", "SIGNAL", "GENRE_COLLECTION"};
    return names[kind];
}

int parseLiteral(const char* text, Value* result, int line, const char* phase)
{
    *result = (Value){0};
    if (text[0] == '"') {
        size_t len = strlen(text);
        char* decoded = msAlloc(len);
        size_t out = 0;
        for (size_t i = 1; i + 1 < len; ++i) {
            char c = text[i];
            if (c == '\\') {
                c = text[++i];
                switch (c) {
                    case 'n': c = '\n'; break;
                    case 't': c = '\t'; break;
                    case 'r': c = '\r'; break;
                    case '\\': case '"': break;
                    default:
                        reportError(phase, line, "unsupported string escape \\%c", c);
                        free(decoded); return 0;
                }
            }
            decoded[out++] = c;
        }
        if (out > MS_STRING_MAX) {
            reportError(phase, line, "string exceeds %d bytes (got %lu)", MS_STRING_MAX, (unsigned long)out);
            free(decoded); return 0;
        }
        result->kind = VALUE_TEXT;
        result->text = decoded;
        return 1;
    }
    if (!strcmp(text, "TRUE") || !strcmp(text, "FALSE")) {
        *result = signalValue(!strcmp(text, "TRUE")); return 1;
    }
    if (!strcmp(text, "SUCCESS") || !strcmp(text, "FAILURE") || !strcmp(text, "BLOCKBUSTER") || !strcmp(text, "FLOP") || !strcmp(text, "AVERAGE")) {
        result->kind = VALUE_STATUS;
        result->text = msCopy(text); return 1;
    }
    errno = 0;
    char* end;
    double number = strtod(text, &end);
    if (end == text || *end || errno == ERANGE || !isfinite(number)) {
        reportError(phase, line, "numeric literal is outside the finite number range"); return 0;
    }
    *result = numberValue(number); return 1;
}

int validateValue(const char* type, const Value* value, int line, const char* target, const char* phase)
{
    if (typeKind(type) != value->kind) {
        reportError(phase, line, "%s requires %s, got %s", target, type, kindName(value->kind)); return 0;
    }
    if (value->kind == VALUE_NUMBER) {
        double n = value->number;
        if (!isfinite(n)) { reportError(phase, line, "%s must be a finite number", target); return 0; }
        if (!strcmp(type, "RATING") && (n < MS_RATING_MIN || n > MS_RATING_MAX)) {
            reportError(phase, line, "RATING %s must be between 0 and 5 (got %.15g)", target, n); return 0;
        }
        if (!strcmp(type, "BUDGET") && (n < 0 || n > MS_BUDGET_MAX)) {
            reportError(phase, line, "BUDGET %s must be between 0 and 1000000000000 (got %.15g)", target, n); return 0;
        }
        if (!strcmp(type, "WHOLE") && (n < MS_WHOLE_MIN || n > MS_WHOLE_MAX || trunc(n) != n)) {
            reportError(phase, line, "WHOLE %s must be an integer between -2147483648 and 2147483647 (got %.15g)", target, n); return 0;
        }
    }
    if (value->kind == VALUE_TEXT) {
        size_t max = MS_STRING_MAX;
        if (!strcmp(type, "CHARACTER")) max = MS_CHARACTER_MAX;
        if (!strcmp(type, "SCENE")) max = MS_SCENE_MAX;
        if (!strcmp(type, "GENRE")) max = MS_GENRE_MAX;
        size_t size = strlen(value->text);
        if (size > max) {
            reportError(phase, line, "%s %s exceeds %lu bytes (got %lu)", type, target, (unsigned long)max, (unsigned long)size); return 0;
        }
    }
    if (value->kind == VALUE_COLLECTION) {
        if (value->count > MS_COLLECTION_MAX) { reportError(phase, line, "collection exceeds %d items", MS_COLLECTION_MAX); return 0; }
        for (size_t i = 0; i < value->count; ++i) {
            Value item = textValue(value->items[i]);
            int valid = validateValue("GENRE", &item, line, target, phase);
            freeValue(&item);
            if (!valid) return 0;
        }
    }
    return 1;
}

int applyUnary(const char* op, const Value* v, Value* result, int line, const char* phase)
{
    if (!strcmp(op, "NOT") && v->kind == VALUE_SIGNAL) { *result = signalValue(!v->number); return 1; }
    if (!strcmp(op, "-") && v->kind == VALUE_NUMBER) { *result = numberValue(-v->number); return 1; }
    if (!strcmp(op, "RISING") && v->kind == VALUE_NUMBER) { *result = signalValue(v->number > 0); return 1; }
    reportError(phase, line, "%s cannot be applied to %s", op, kindName(v->kind)); return 0;
}

int applyBinary(const char* op, const Value* a, const Value* b, Value* result, int line, const char* phase)
{
    if ((!strcmp(op, "AND") || !strcmp(op, "OR")) && a->kind == VALUE_SIGNAL && b->kind == VALUE_SIGNAL) {
        *result = signalValue(!strcmp(op, "AND") ? a->number && b->number : a->number || b->number); return 1;
    }
    if ((!strcmp(op, "==") || !strcmp(op, "!=")) && a->kind == b->kind && a->kind != VALUE_COLLECTION) {
        int equal = (a->kind == VALUE_TEXT || a->kind == VALUE_STATUS) ? !strcmp(a->text, b->text) : a->number == b->number;
        *result = signalValue(!strcmp(op, "==") ? equal : !equal); return 1;
    }
    if (!strcmp(op, "+") && a->kind == VALUE_TEXT && b->kind == VALUE_TEXT) {
        size_t total = strlen(a->text) + strlen(b->text);
        if (total > MS_STRING_MAX) { reportError(phase, line, "concatenated text exceeds %d bytes", MS_STRING_MAX); return 0; }
        result->kind = VALUE_TEXT;
        result->text = msAlloc(total + 1);
        strcpy(result->text, a->text); strcat(result->text, b->text); return 1;
    }
    if (a->kind == VALUE_NUMBER && b->kind == VALUE_NUMBER) {
        double x = a->number, y = b->number, n;
        if (!strcmp(op, ">")) { *result = signalValue(x > y); return 1; }
        if (!strcmp(op, ">=")) { *result = signalValue(x >= y); return 1; }
        if (!strcmp(op, "<")) { *result = signalValue(x < y); return 1; }
        if (!strcmp(op, "<=")) { *result = signalValue(x <= y); return 1; }
        if (!strcmp(op, "+")) n = x + y;
        else if (!strcmp(op, "-")) n = x - y;
        else if (!strcmp(op, "*")) n = x * y;
        else if (!strcmp(op, "/") || !strcmp(op, "%")) {
            if (y == 0) { reportError(phase, line, "division by zero"); return 0; }
            n = !strcmp(op, "/") ? x / y : fmod(x, y);
        } else goto invalid;
        if (!isfinite(n)) { reportError(phase, line, "arithmetic result is outside the finite number range"); return 0; }
        *result = numberValue(n); return 1;
    }
invalid:
    reportError(phase, line, "operator %s does not accept %s and %s", op, kindName(a->kind), kindName(b->kind)); return 0;
}

int appendItem(Value* collection, const char* text, int line, const char* phase)
{
    if (collection->count >= MS_COLLECTION_MAX) { reportError(phase, line, "collection exceeds %d items", MS_COLLECTION_MAX); return 0; }
    Value item = textValue(text);
    int valid = validateValue("GENRE", &item, line, "collection item", phase);
    freeValue(&item);
    if (!valid) return 0;
    char** items = msAlloc((collection->count + 1) * sizeof(char*));
    if (collection->count) memcpy(items, collection->items, collection->count * sizeof(char*));
    free(collection->items);
    collection->items = items;
    collection->items[collection->count++] = msCopy(text); return 1;
}

int applyBuiltin(const char* name, const Value* args, int count, Value* result, int line, const char* phase)
{
    if (!strcmp(name, "COUNT") && count == 1 && args[0].kind == VALUE_COLLECTION) { *result = numberValue((double)args[0].count); return 1; }
    if (!strcmp(name, "LENGTH") && count == 1 && args[0].kind == VALUE_TEXT) { *result = numberValue((double)strlen(args[0].text)); return 1; }
    if (!strcmp(name, "CONTAINS") && count == 2 && args[0].kind == VALUE_COLLECTION && args[1].kind == VALUE_TEXT) {
        int found = 0;
        for (size_t i = 0; i < args[0].count; ++i) if (!strcmp(args[0].items[i], args[1].text)) found = 1;
        *result = signalValue(found); return 1;
    }
    if (!strcmp(name, "CLAMP") && count == 3 && args[0].kind == VALUE_NUMBER && args[1].kind == VALUE_NUMBER && args[2].kind == VALUE_NUMBER) {
        if (args[1].number > args[2].number) { reportError(phase, line, "CLAMP minimum cannot exceed maximum"); return 0; }
        *result = numberValue(fmax(args[1].number, fmin(args[0].number, args[2].number))); return 1;
    }
    reportError(phase, line, "invalid arguments for %s", name); return 0;
}

static void printQuoted(const char* text)
{
    putchar('"');
    for (; *text; ++text) {
        switch (*text) {
            case '\n': fputs("\\n", stdout); break;
            case '\r': fputs("\\r", stdout); break;
            case '\t': fputs("\\t", stdout); break;
            case '"': fputs("\\\"", stdout); break;
            case '\\': fputs("\\\\", stdout); break;
            default: putchar((unsigned char)*text); break;
        }
    }
    putchar('"');
}

void printValue(const Value* v)
{
    if (v->kind == VALUE_NUMBER) printf("%.15g", v->number);
    else if (v->kind == VALUE_TEXT || v->kind == VALUE_STATUS) fputs(v->text, stdout);
    else if (v->kind == VALUE_SIGNAL) fputs(v->number ? "TRUE" : "FALSE", stdout);
    else if (v->kind == VALUE_COLLECTION) {
        fputc('{', stdout);
        for (size_t i = 0; i < v->count; ++i) {
            if (i) fputs(", ", stdout);
            printQuoted(v->items[i]);
        }
        fputc('}', stdout);
    } else fputs("<uninitialized>", stdout);
}
