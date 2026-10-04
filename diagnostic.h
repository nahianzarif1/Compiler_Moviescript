#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

void resetDiagnostics(const char* source);
void reportError(const char* phase, int line, const char* format, ...);
void reportWarning(int line, const char* format, ...);
int errorCount(void);
int warningCount(void);
void* msAlloc(unsigned long size);
char* msCopy(const char* text);

#endif
