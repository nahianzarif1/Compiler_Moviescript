#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"
#include "limits.h"
#include "semantic.h"
#include "symbol_table.h"
#include "value.h"

typedef struct FunctionEntry {
    ASTNode* node;
    struct FunctionEntry* next;
} FunctionEntry;

typedef struct {
    ValueKind kind;
    int known;
    Value value;
} ExprInfo;

static FunctionEntry* functions;
static ASTNode* activeFunction;
static const char* phase = "Semantic Error";

ASTNode* lookupFunctionNode(const char* name)
{
    for (FunctionEntry* f = functions; f; f = f->next)
        if (!strcmp(f->node->name, name)) return f->node;
    return NULL;
}

void freeFunctionTable(void)
{
    while (functions) { FunctionEntry* next = functions->next; free(functions); functions = next; }
}

static Symbol* requireSymbol(const char* name, int line, int read)
{
    Symbol* s = lookupSymbol(name);
    if (!s) {
        if (lookupFunctionNode(name)) reportError(phase, line, "%s is a function; call it with parentheses", name);
        else reportError(phase, line, "undefined variable %s", name);
    } else if (read && !s->initialized && !(activeFunction && isGlobalSymbol(s))) {
        reportError(phase, line, "variable %s may be uninitialized", name);
    }
    return s;
}

static ExprInfo infer(ASTNode* node);

static void checkTarget(const char* type, ExprInfo* info, int line, const char* target)
{
    if (info->kind == VALUE_NONE) return;
    if (typeKind(type) != info->kind) reportError(phase, line, "%s requires %s, got %s", target, type, kindName(info->kind));
    else if (info->known) validateValue(type, &info->value, line, target, phase);
}

static ExprInfo inferCall(ASTNode* node)
{
    ExprInfo result = {0};
    ASTNode* function = node->type == NODE_CALL ? lookupFunctionNode(node->name) : NULL;
    int count = 0;
    ASTNode* param = function ? function->left : NULL;
    Value args[MS_PARAM_MAX] = {{0}};
    ValueKind kinds[MS_PARAM_MAX] = {0};
    int allKnown = 1;
    for (ASTNode* arg = node->left; arg; arg = arg->next) {
        ExprInfo info = infer(arg);
        if (param) { checkTarget(param->value, &info, arg->line, param->name); param = param->next; }
        if (count < MS_PARAM_MAX) { args[count] = info.value; kinds[count] = info.kind; }
        else freeValue(&info.value);
        allKnown &= info.known;
        ++count;
    }
    if (node->type == NODE_CALL) {
        if (!function) reportError(phase, node->line, "undefined function %s", node->name);
        else {
            int expected = 0;
            for (ASTNode* p = function->left; p; p = p->next) ++expected;
            if (expected != count) reportError(phase, node->line, "function %s expects %d arguments, got %d", node->name, expected, count);
            result.kind = typeKind(function->value);
        }
    } else {
        int valid = 0;
        if (!strcmp(node->name, "COUNT")) valid = count == 1 && kinds[0] == VALUE_COLLECTION;
        else if (!strcmp(node->name, "LENGTH")) valid = count == 1 && kinds[0] == VALUE_TEXT;
        else if (!strcmp(node->name, "CONTAINS")) valid = count == 2 && kinds[0] == VALUE_COLLECTION && kinds[1] == VALUE_TEXT;
        else if (!strcmp(node->name, "CLAMP")) valid = count == 3 && kinds[0] == VALUE_NUMBER && kinds[1] == VALUE_NUMBER && kinds[2] == VALUE_NUMBER;
        if (!valid) reportError(phase, node->line, "invalid arguments for %s", node->name);
        else {
            result.kind = !strcmp(node->name, "CONTAINS") ? VALUE_SIGNAL : VALUE_NUMBER;
            if (allKnown) result.known = applyBuiltin(node->name, args, count, &result.value, node->line, phase);
        }
    }
    for (int i = 0; i < count && i < MS_PARAM_MAX; ++i) freeValue(&args[i]);
    return result;
}

static ExprInfo infer(ASTNode* node)
{
    ExprInfo info = {0};
    if (!node) return info;
    if (node->type == NODE_VALUE) {
        if (node->name) {
            Symbol* s = requireSymbol(node->name, node->line, 1);
            if (s) info.kind = typeKind(s->type);
        } else {
            info.known = parseLiteral(node->value, &info.value, node->line, phase);
            info.kind = info.value.kind;
        }
        return info;
    }
    if (node->type == NODE_CALL || node->type == NODE_BUILTIN) return inferCall(node);
    ExprInfo a = infer(node->left), b = {0};
    if (node->type == NODE_UNARY_OP) {
        ValueKind expected = !strcmp(node->name, "NOT") ? VALUE_SIGNAL : VALUE_NUMBER;
        if (a.kind != VALUE_NONE && a.kind != expected) reportError(phase, node->line, "%s requires %s", node->name, kindName(expected));
        else if (a.kind != VALUE_NONE) {
            info.kind = !strcmp(node->name, "-") ? VALUE_NUMBER : VALUE_SIGNAL;
            if (a.known) info.known = applyUnary(node->name, &a.value, &info.value, node->line, phase);
        }
    } else {
        b = infer(node->right);
        if (a.kind != VALUE_NONE && b.kind != VALUE_NONE) {
            if (!strcmp(node->name, "AND") || !strcmp(node->name, "OR")) {
                if (a.kind == VALUE_SIGNAL && b.kind == VALUE_SIGNAL) info.kind = VALUE_SIGNAL;
            } else if (!strcmp(node->name, "==") || !strcmp(node->name, "!=")) {
                if (a.kind == b.kind && a.kind != VALUE_COLLECTION) info.kind = VALUE_SIGNAL;
            } else if (node->type == NODE_CONDITION) {
                if (a.kind == VALUE_NUMBER && b.kind == VALUE_NUMBER) info.kind = VALUE_SIGNAL;
            } else if (a.kind == VALUE_NUMBER && b.kind == VALUE_NUMBER) info.kind = VALUE_NUMBER;
            else if (!strcmp(node->name, "+") && a.kind == VALUE_TEXT && b.kind == VALUE_TEXT) info.kind = VALUE_TEXT;
            if (info.kind == VALUE_NONE) reportError(phase, node->line, "operator %s does not accept %s and %s", node->name, kindName(a.kind), kindName(b.kind));
            else if (a.known && b.known) info.known = applyBinary(node->name, &a.value, &b.value, &info.value, node->line, phase);
            if ((!strcmp(node->name, "/") || !strcmp(node->name, "%")) && !a.known && b.known && b.kind == VALUE_NUMBER && b.value.number == 0)
                reportError(phase, node->line, "division by zero");
        }
    }
    freeValue(&a.value); freeValue(&b.value);
    return info;
}

static int listReturns(ASTNode* node)
{
    for (; node; node = node->next) {
        if (node->type == NODE_RETURN) return 1;
        if (node->type == NODE_IF && node->elseBranch && listReturns(node->right) && listReturns(node->elseBranch)) return 1;
    }
    return 0;
}

static void checkList(ASTNode* node, int topLevel);
static void checkBlock(ASTNode* node) { enterScope(); checkList(node, 0); leaveScope(); }

static int checkCondition(ASTNode* node)
{
    ExprInfo info = infer(node);
    if (info.kind != VALUE_NONE && info.kind != VALUE_SIGNAL) reportError(phase, node->line, "condition requires SIGNAL, got %s", kindName(info.kind));
    if (info.known && info.kind == VALUE_SIGNAL) reportWarning(node->line, "condition is always %s", info.value.number ? "TRUE" : "FALSE");
    int truth = info.known && info.kind == VALUE_SIGNAL ? !!info.value.number : -1;
    freeValue(&info.value);
    if (node->type == NODE_CONDITION && node->left && node->left->name && node->left->type == NODE_VALUE && node->right && node->right->type == NODE_VALUE && node->right->value) {
        Symbol* s = lookupSymbol(node->left->name);
        char* end;
        double threshold = strtod(node->right->value, &end);
        if (s && !strcmp(s->type, "RATING") && end != node->right->value && !*end && isfinite(threshold)) {
            if ((!strcmp(node->name, ">") && threshold >= 5) || (!strcmp(node->name, ">=") && threshold > 5))
                reportWarning(node->line, "unreachable branch: RATING %s cannot exceed 5", s->name);
        }
    }
    return truth;
}

static void checkList(ASTNode* node, int topLevel)
{
    int unreachable = 0;
    for (; node; node = node->next) {
        if (unreachable && node->type != NODE_FUNCTION) reportWarning(node->line, "unreachable statement after RETURN");
        switch (node->type) {
            case NODE_DECL: {
                Symbol* s = insertSymbolWithLine(node->name, node->value, node->line);
                if (node->left) {
                    ExprInfo info = infer(node->left);
                    checkTarget(node->value, &info, node->line, node->name);
                    if (s && info.kind != VALUE_NONE) s->initialized = 1;
                    freeValue(&info.value);
                }
                break;
            }
            case NODE_ASSIGN: {
                Symbol* s = requireSymbol(node->name, node->line, 0);
                ExprInfo info = infer(node->left);
                if (s) { checkTarget(s->type, &info, node->line, s->name); if (info.kind != VALUE_NONE) s->initialized = 1; }
                freeValue(&info.value); break;
            }
            case NODE_COLLECTION: {
                Symbol* s = insertSymbolWithLine(node->name, "GENRE_COLLECTION", node->line);
                Value coll = {.kind = VALUE_COLLECTION};
                for (ASTNode* item = node->left; item; item = item->next) {
                    ExprInfo info = infer(item);
                    if (info.known && info.kind == VALUE_TEXT) appendItem(&coll, info.value.text, item->line, phase);
                    freeValue(&info.value);
                }
                freeValue(&coll); if (s) s->initialized = 1; break;
            }
            case NODE_COLLECTION_ADD: {
                Symbol* s = requireSymbol(node->name, node->line, 1);
                if (s && typeKind(s->type) != VALUE_COLLECTION) reportError(phase, node->line, "ADD_TO requires GENRE_COLLECTION");
                ExprInfo info = infer(node->left); checkTarget("GENRE", &info, node->line, "collection item"); freeValue(&info.value); break;
            }
            case NODE_IF: {
                int truth = checkCondition(node->left);
                SymbolState* state = snapshotSymbols();
                checkBlock(node->right); saveBranchSymbols(state);
                checkBlock(node->elseBranch);
                mergeBranchSymbols(state, truth == 0 || listReturns(node->right), truth == 1 || listReturns(node->elseBranch));
                freeSymbolStates(state);
                if (listReturns(node->right) && listReturns(node->elseBranch)) unreachable = 1;
                break;
            }
            case NODE_WHILE: {
                checkCondition(node->left);
                SymbolState* state = snapshotSymbols(); checkBlock(node->right);
                restoreSymbols(state); freeSymbolStates(state); break;
            }
            case NODE_FOR: {
                Symbol* coll = requireSymbol(node->name, node->line, 1);
                if (coll && typeKind(coll->type) != VALUE_COLLECTION) reportError(phase, node->line, "FOR_EACH_SCENE requires GENRE_COLLECTION");
                SymbolState* state = snapshotSymbols(); enterScope();
                if (node->value) {
                    Symbol* item = insertSymbolWithLine(node->value, "GENRE", node->line);
                    if (item) item->initialized = 1;
                }
                checkList(node->right, 0); leaveScope(); restoreSymbols(state); freeSymbolStates(state); break;
            }
            case NODE_FUNCTION:
                if (!topLevel) reportError(phase, node->line, "functions must be declared at screenplay level");
                break;
            case NODE_RETURN: {
                ExprInfo info = infer(node->left);
                if (!activeFunction) reportError(phase, node->line, "RETURN is only valid inside a function");
                else checkTarget(activeFunction->value, &info, node->line, activeFunction->name);
                freeValue(&info.value); unreachable = 1; break;
            }
            case NODE_CALL: { ExprInfo info = infer(node); freeValue(&info.value); break; }
            case NODE_ACTION: {
                if (node->value && !strcmp(node->value, "ANALYZE")) { requireSymbol(node->name, node->line, 1); break; }
                if (node->left) {
                    ExprInfo info = infer(node->left);
                    if (!strcmp(node->name, "AWARD") || !strcmp(node->name, "REVIEW")) checkTarget("DIALOGUE", &info, node->line, node->name);
                    if (!strcmp(node->name, "ASSERT")) {
                        checkTarget("SIGNAL", &info, node->line, "ASSERT condition");
                        Value message = {0}; parseLiteral(node->value, &message, node->line, phase); freeValue(&message);
                    }
                    freeValue(&info.value);
                }
                break;
            }
            default: break;
        }
    }
}

int semanticCheck(ASTNode* root)
{
    int before = errorCount();
    freeFunctionTable(); initSymbolTable(); activeFunction = NULL;
    ASTNode* statements = root && root->left ? root->left->left : NULL;
    for (ASTNode* n = statements; n; n = n->next) {
        if (n->type != NODE_FUNCTION) continue;
        if (lookupFunctionNode(n->name)) reportError(phase, n->line, "duplicate function %s", n->name);
        else { FunctionEntry* f = msAlloc(sizeof(FunctionEntry)); f->node = n; f->next = functions; functions = f; }
        int count = 0;
        for (ASTNode* p = n->left; p; p = p->next) ++count;
        if (count > MS_PARAM_MAX) reportError(phase, n->line, "function exceeds %d parameters", MS_PARAM_MAX);
    }
    checkList(statements, 1);
    for (FunctionEntry* f = functions; f; f = f->next) {
        activeFunction = f->node;
        SymbolState* state = snapshotSymbols();
        enterFunctionScope();
        for (ASTNode* p = activeFunction->left; p; p = p->next) {
            Symbol* s = insertSymbolWithLine(p->name, p->value, p->line);
            if (s) s->initialized = 1;
        }
        checkList(activeFunction->right, 0);
        if (!listReturns(activeFunction->right)) reportError(phase, activeFunction->line, "function %s must RETURN on every path", activeFunction->name);
        leaveScope(); restoreSymbols(state); freeSymbolStates(state);
    }
    activeFunction = NULL;
    return errorCount() == before;
}

/* Only safe numeric subtrees are folded, after semantic validation. */
void foldConstants(ASTNode* node)
{
    for (; node; node = node->next) {
        foldConstants(node->left); foldConstants(node->right); foldConstants(node->elseBranch);
        if ((node->type == NODE_BINARY_OP || node->type == NODE_UNARY_OP) && node->left && node->left->type == NODE_VALUE && !node->left->name && node->left->value && (node->right == NULL || (node->right->type == NODE_VALUE && !node->right->name && node->right->value))) {
            Value a = {0}, b = {0}, result = {0};
            int valid = parseLiteral(node->left->value, &a, node->line, phase);
            if (node->right) valid &= parseLiteral(node->right->value, &b, node->line, phase);
            if (valid && a.kind == VALUE_NUMBER && (!node->right || b.kind == VALUE_NUMBER)) {
                valid = node->right ? applyBinary(node->name, &a, &b, &result, node->line, phase) : applyUnary(node->name, &a, &result, node->line, phase);
                if (valid && result.kind == VALUE_NUMBER) {
                    char buffer[64]; snprintf(buffer, sizeof(buffer), "%.17g", result.number);
                    freeAST(node->left); freeAST(node->right); node->left = node->right = NULL;
                    free(node->name); node->name = NULL; setNodeValue(node, buffer); node->type = NODE_VALUE;
                }
            }
            freeValue(&a); freeValue(&b); freeValue(&result);
        }
    }
}
