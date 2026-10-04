#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"
#include "interpreter.h"
#include "limits.h"
#include "semantic.h"
#include "symbol_table.h"
#include "value.h"

typedef struct { int returned; Value value; } Flow;
static unsigned long steps;
static unsigned long stepLimit;
static int callDepth;
static int initialErrors;
static const char* phase = "Runtime Error";

static int healthy(void) { return errorCount() == initialErrors; }
static int tick(int line)
{
    if (!healthy()) return 0;
    if (steps >= stepLimit) {
        reportError(phase, line, "execution step limit (%lu) reached; check for an infinite loop", stepLimit); return 0;
    }
    ++steps; return 1;
}

static int evaluate(ASTNode* node, Value* result);
static Flow executeList(ASTNode* node);
static Flow executeBlock(ASTNode* node)
{
    enterScope(); Flow flow = executeList(node); leaveScope(); return flow;
}

static Symbol* runtimeSymbol(const char* name, int line)
{
    Symbol* symbol = lookupSymbol(name);
    if (!symbol) reportError(phase, line, "undefined variable %s", name);
    else if (symbol->value.kind == VALUE_NONE) reportError(phase, line, "variable %s is uninitialized", name);
    else return symbol;
    return NULL;
}

static int evaluateCall(ASTNode* node, Value* result)
{
    Value args[MS_PARAM_MAX] = {{0}};
    int count = 0, valid = 1;
    /* Evaluate in the caller before binding any callee parameters. */
    for (ASTNode* arg = node->left; arg && valid; arg = arg->next) {
        if (count >= MS_PARAM_MAX) { reportError(phase, node->line, "call exceeds %d arguments", MS_PARAM_MAX); valid = 0; break; }
        valid = evaluate(arg, &args[count++]);
    }
    if (valid && node->type == NODE_BUILTIN) valid = applyBuiltin(node->name, args, count, result, node->line, phase);
    else if (valid) {
        ASTNode* function = lookupFunctionNode(node->name);
        if (!function) { reportError(phase, node->line, "undefined function %s", node->name); valid = 0; }
        else if (callDepth >= MS_CALL_DEPTH_MAX) { reportError(phase, node->line, "call depth exceeds %d", MS_CALL_DEPTH_MAX); valid = 0; }
        else {
            int expected = 0;
            for (ASTNode* param = function->left; param; param = param->next) {
                if (expected >= count || !validateValue(param->value, &args[expected], node->line, param->name, phase)) valid = 0;
                ++expected;
            }
            if (expected != count) { reportError(phase, node->line, "function %s expects %d arguments, got %d", node->name, expected, count); valid = 0; }
            if (valid) {
                enterFunctionScope(); ++callDepth;
                int index = 0;
                for (ASTNode* param = function->left; param; param = param->next) {
                    Symbol* s = insertSymbolWithLine(param->name, param->value, param->line);
                    storeValue(s, &args[index++], node->line, phase);
                }
                Flow flow = executeList(function->right);
                if (healthy()) {
                    if (!flow.returned) { reportError(phase, node->line, "function %s did not RETURN", node->name); valid = 0; }
                    else valid = validateValue(function->value, &flow.value, node->line, function->name, phase);
                } else valid = 0;
                if (valid) { *result = flow.value; flow.value = (Value){0}; }
                freeValue(&flow.value); --callDepth; leaveScope();
            }
        }
    }
    for (int i = 0; i < count; ++i) freeValue(&args[i]);
    return valid;
}

static int evaluate(ASTNode* node, Value* result)
{
    *result = (Value){0};
    if (!node || !tick(node->line)) return 0;
    if (node->type == NODE_VALUE) {
        if (!node->name) return parseLiteral(node->value, result, node->line, phase);
        Symbol* s = runtimeSymbol(node->name, node->line);
        if (!s) return 0;
        *result = copyValue(&s->value); return 1;
    }
    if (node->type == NODE_CALL || node->type == NODE_BUILTIN) return evaluateCall(node, result);
    Value a = {0}, b = {0};
    int valid = evaluate(node->left, &a);
    if (valid && node->type == NODE_UNARY_OP) valid = applyUnary(node->name, &a, result, node->line, phase);
    else if (valid) {
        if (a.kind == VALUE_SIGNAL && ((!strcmp(node->name, "AND") && !a.number) || (!strcmp(node->name, "OR") && a.number))) {
            *result = signalValue(a.number);
        } else {
            valid = evaluate(node->right, &b);
            if (valid) valid = applyBinary(node->name, &a, &b, result, node->line, phase);
        }
    }
    freeValue(&a); freeValue(&b); return valid;
}

static int condition(ASTNode* node)
{
    Value v = {0};
    int valid = evaluate(node, &v);
    if (valid && v.kind != VALUE_SIGNAL) { reportError(phase, node->line, "condition requires SIGNAL"); valid = 0; }
    int truth = valid && v.number;
    freeValue(&v); return truth;
}

static Flow executeStatement(ASTNode* node)
{
    Flow flow = {0};
    if (!tick(node->line)) return flow;
    switch (node->type) {
        case NODE_DECL: {
            Symbol* s = insertSymbolWithLine(node->name, node->value, node->line);
            if (node->left) { Value v = {0}; if (evaluate(node->left, &v)) storeValue(s, &v, node->line, phase); freeValue(&v); }
            break;
        }
        case NODE_ASSIGN: {
            Symbol* s = lookupSymbol(node->name);
            if (!s) reportError(phase, node->line, "undefined variable %s", node->name);
            else { Value v = {0}; if (evaluate(node->left, &v)) storeValue(s, &v, node->line, phase); freeValue(&v); }
            break;
        }
        case NODE_COLLECTION: {
            Symbol* s = insertSymbolWithLine(node->name, "GENRE_COLLECTION", node->line);
            Value coll = {.kind = VALUE_COLLECTION};
            for (ASTNode* item = node->left; item && healthy(); item = item->next) {
                Value v = {0};
                if (evaluate(item, &v)) appendItem(&coll, v.text, item->line, phase);
                freeValue(&v);
            }
            if (healthy()) storeValue(s, &coll, node->line, phase);
            freeValue(&coll); break;
        }
        case NODE_COLLECTION_ADD: {
            Symbol* s = runtimeSymbol(node->name, node->line);
            if (s) {
                Value v = {0};
                if (evaluate(node->left, &v) && validateValue("GENRE", &v, node->line, "collection item", phase)) {
                    if (s->value.kind != VALUE_COLLECTION) reportError(phase, node->line, "ADD_TO requires GENRE_COLLECTION");
                    else appendItem(&s->value, v.text, node->line, phase);
                }
                freeValue(&v);
            }
            break;
        }
        case NODE_IF:
            if (condition(node->left)) flow = executeBlock(node->right);
            else if (healthy()) flow = executeBlock(node->elseBranch);
            break;
        case NODE_WHILE:
            while (healthy() && condition(node->left)) {
                flow = executeBlock(node->right);
                if (flow.returned) break;
            }
            break;
        case NODE_FOR: {
            Symbol* s = runtimeSymbol(node->name, node->line);
            if (!s) break;
            if (s->value.kind != VALUE_COLLECTION) { reportError(phase, node->line, "FOR_EACH_SCENE requires GENRE_COLLECTION"); break; }
            /* Snapshot iteration is stable even if the body appends to the source. */
            Value collection = copyValue(&s->value);
            for (size_t i = 0; i < collection.count && healthy(); ++i) {
                if (!tick(node->line)) break;
                enterScope();
                if (node->value) {
                    Symbol* item = insertSymbolWithLine(node->value, "GENRE", node->line);
                    Value text = textValue(collection.items[i]); storeValue(item, &text, node->line, phase); freeValue(&text);
                }
                flow = executeList(node->right); leaveScope();
                if (flow.returned) break;
            }
            freeValue(&collection); break;
        }
        case NODE_FUNCTION: break;
        case NODE_RETURN:
            flow.returned = evaluate(node->left, &flow.value);
            break;
        case NODE_CALL: { Value v = {0}; evaluate(node, &v); freeValue(&v); break; }
        case NODE_ACTION: {
            if (node->value && !strcmp(node->value, "ANALYZE")) {
                Symbol* s = runtimeSymbol(node->name, node->line);
                if (s) { printf("%s (%s) = ", s->name, s->type); printValue(&s->value); putchar('\n'); }
            } else if (!strcmp(node->name, "BUILD_SUSPENSE")) puts("Building suspense...");
            else if (!strcmp(node->name, "ENTER_STAGE")) puts("Entering stage...");
            else {
                Value v = {0};
                if (evaluate(node->left, &v)) {
                    if (!strcmp(node->name, "ASSERT")) {
                        if (!v.number) {
                            Value message = {0};
                            if (parseLiteral(node->value, &message, node->line, phase)) reportError(phase, node->line, "assertion failed: %s", message.text);
                            freeValue(&message);
                        }
                    } else {
                        if (strcmp(node->name, "PRINT")) printf("%s: ", node->name);
                        printValue(&v); putchar('\n');
                    }
                }
                freeValue(&v);
            }
            break;
        }
        default: break;
    }
    return flow;
}

static Flow executeList(ASTNode* node)
{
    Flow flow = {0};
    for (; node && healthy(); node = node->next) {
        flow = executeStatement(node);
        if (flow.returned) break;
    }
    return flow;
}

int execute(ASTNode* node, unsigned long maxSteps)
{
    initialErrors = errorCount(); steps = 0; stepLimit = maxSteps; callDepth = 0;
    initSymbolTable();
    Flow flow = executeList(node && node->left ? node->left->left : NULL);
    freeValue(&flow.value);
    return healthy();
}
