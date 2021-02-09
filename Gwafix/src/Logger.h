//defines a Logger for Gwafix

#ifndef Logger_h
#define Logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define LogMessage(message) printf("%s\n", message);

#ifdef GWAFIX_RELEASE

#define LogWarning(code, message)
#define LogError(code, message)
#define LogFatalError(code, message) printf("Gwafix Fatal Error: %s || %s\n", code, message); getchar(); exit(1);

#define LogData(formate, ...)
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); getchar(); exit(1);

#endif

#ifdef GWAFIX_DIST

#define LogWarning(code, message)
#define LogError(code, message)
#define LogFatalError(code, message) exit(1);

#define LogData(formate, ...)
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); exit(1);

#endif

#ifdef GWAFIX_DEBUG

#define LogWarning(code, message) printf("Gwafix Warning : %s || %s\n", code, message);
#define LogError(code, message) printf("Gwafix Error : %s || %s\n", code, message);
#define LogFatalError(code, message) printf("Gwafix Fatal Error: %s || %s\n", code, message); getchar(); exit(1);

#define LogData(formate, ...) printf(formate, __VA_ARGS__);
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); getchar(); exit(1);

#endif

#endif