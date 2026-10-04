#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "diagnostic.h"
#include "interpreter.h"
#include "ir.h"
#include "limits.h"
#include "semantic.h"
#include "symbol_table.h"

extern int yyparse(void);
extern int yylex_destroy(void);
extern ASTNode* root;
typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_bytes(const char*, int);
extern void yy_delete_buffer(YY_BUFFER_STATE);

static void usage(void)
{
    puts("MovieScript 2.0 — a movie-themed language with checked values\n"
         "Usage: moviescript [options] [file.ms | -]\n\n"
         "  --check            Validate without executing\n"
         "  --ast              Show the abstract syntax tree\n"
         "  --ir               Show three-address intermediate code\n"
         "  --cfg              Show the control-flow graph\n"
         "  --functions        Show function signatures\n"
         "  --symbols          Show global symbols (final values when executed)\n"
         "  --trace            Show all compiler stages\n"
         "  --no-optimize      Disable constant folding\n"
         "  --max-steps N      Execution budget (default: 100000)\n"
         "  --help             Show this help\n"
         "  --version          Show version\n\n"
         "Omit file or use - to read standard input. Diagnostics go to stderr.");
}

int main(int argc, char** argv)
{
    int check = 0, ast = 0, ir = 0, cfg = 0, symbols = 0, functions = 0, optimize = 1;
    unsigned long maxSteps = MS_DEFAULT_STEPS;
    const char* filename = NULL;
    for (int i = 1; i < argc; ++i) {
        const char* option = argv[i];
        if (!strcmp(option, "--help") || !strcmp(option, "-h")) { usage(); return 0; }
        if (!strcmp(option, "--version")) { puts("MovieScript 2.0"); return 0; }
        if (!strcmp(option, "--check")) check = 1;
        else if (!strcmp(option, "--ast")) ast = 1;
        else if (!strcmp(option, "--ir")) ir = 1;
        else if (!strcmp(option, "--cfg")) cfg = 1;
        else if (!strcmp(option, "--symbols")) symbols = 1;
        else if (!strcmp(option, "--functions")) functions = 1;
        else if (!strcmp(option, "--trace")) ast = ir = cfg = symbols = functions = 1;
        else if (!strcmp(option, "--no-optimize")) optimize = 0;
        else if (!strcmp(option, "--max-steps")) {
            if (++i >= argc) { fputs("MovieScript: --max-steps requires a positive integer\n", stderr); return 2; }
            errno = 0; char* end;
            maxSteps = strtoul(argv[i], &end, 10);
            if (errno || !*argv[i] || *end || argv[i][0] == '-' || !maxSteps) { fputs("MovieScript: invalid --max-steps value\n", stderr); return 2; }
        } else if (option[0] == '-' && strcmp(option, "-")) { fprintf(stderr, "MovieScript: unknown option %s\n", option); return 2; }
        else if (filename) { fputs("MovieScript: provide one input file\n", stderr); return 2; }
        else filename = option;
    }
    const char* source = filename && strcmp(filename, "-") ? filename : "<stdin>";
    resetDiagnostics(source);
    FILE* input = !strcmp(source, "<stdin>") ? stdin : fopen(filename, "rb");
    if (!input) { perror(filename); return 2; }
    char* contents = msAlloc(MS_SOURCE_MAX + 1UL);
    size_t length = fread(contents, 1, MS_SOURCE_MAX + 1UL, input);
    int readFailed = ferror(input);
    if (input != stdin) fclose(input);
    if (readFailed) { fputs("MovieScript: failed to read input\n", stderr); free(contents); return 2; }
    if (length > MS_SOURCE_MAX || memchr(contents, '\0', length)) {
        reportError("Input Error", 1, length > MS_SOURCE_MAX ? "source exceeds 1 MiB" : "source contains a NUL byte");
        free(contents); return 1;
    }
    YY_BUFFER_STATE buffer = yy_scan_bytes(contents, (int)length);
    free(contents);
    int parsed = yyparse();
    yy_delete_buffer(buffer); yylex_destroy();
    int valid = !parsed && !errorCount();
    if (valid) valid = validateAST(root) && semanticCheck(root);
    if (valid && optimize) foldConstants(root);
    if (valid && ast) { puts("== Abstract syntax tree =="); printAST(root, 0); }
    if (valid && ir) { puts("== Intermediate code =="); generateIR(root); }
    if (valid && cfg) { puts("== Control-flow graph =="); generateCFG(root); }
    if (valid && functions) { puts("== Function index =="); generateFunctionIndex(root); }
    if (valid && !check) {
        if (ast || ir || cfg || functions || symbols) puts("== Program output ==");
        valid = execute(root, maxSteps);
    }
    if (valid && symbols) { puts("== Global symbols =="); printSymbolTable(); }
    if (valid && check) printf("Check passed (%d warning%s).\n", warningCount(), warningCount() == 1 ? "" : "s");
    freeFunctionTable(); freeSymbolTable();
    /* Bison destructors own partial trees after a parse failure. */
    freeAST(root);
    return valid && !errorCount() ? 0 : 1;
}
