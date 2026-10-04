#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"

static const char* sourceName = "<stdin>";
static int errors;
static int warnings;

void resetDiagnostics(const char* source)
{
    sourceName = source != NULL ? source : "<stdin>";
    errors = warnings = 0;
}

static void report(const char* phase, int line, const char* format, va_list args)
{
    fprintf(stderr, "%s:%d: %s: ", sourceName, line > 0 ? line : 1, phase);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
}

void reportError(const char* phase, int line, const char* format, ...)
{
    va_list args;
    ++errors;
    va_start(args, format);
    report(phase, line, format, args);
    va_end(args);
}

void reportWarning(int line, const char* format, ...)
{
    va_list args;
    ++warnings;
    va_start(args, format);
    report("Warning", line, format, args);
    va_end(args);
}

int errorCount(void) { return errors; }
int warningCount(void) { return warnings; }

void* msAlloc(unsigned long size)
{
    void* result = calloc(1, size);
    if (result == NULL) {
        fputs("MovieScript: out of memory\n", stderr);
        exit(EXIT_FAILURE);
    }
    return result;
}

char* msCopy(const char* text)
{
    if (text == NULL) return NULL;
    char* result = msAlloc(strlen(text) + 1);
    strcpy(result, text);
    return result;
}
