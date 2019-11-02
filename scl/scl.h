
#ifndef SCL_H
#define SCL_H 1

/*
*       Simple C Library
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*
*   useful macros:
*       SCL_SAFE
*       SCL_CHECK_LIMITS
*
*       SCL_NO_TYPES
*/

#ifndef SCL_SAFE
#define SCL_SAFE 1
#endif

#ifdef COMPILE_SCL
#define SCL_DLL_EXPORT __declspec(dllexport)
#else
#define SCL_DLL_EXPORT __declspec(dllimport)
#endif

#if SIZE_MAX == ULLONG_MAX
#define SIZE_C "%I64u"
#elif SIZE_MAX == ULONG_MAX
#define SIZE_C "%I32u"
#else
#error unknown SIZE_MAX
#endif

#if SIZE_MAX == 0xFF
#define SIZE_WIDTH 1
#elif SIZE_MAX == 0xFFFF
#define SIZE_WIDTH 2
#elif SIZE_MAX == 0xFFFFFFFF
#define SIZE_WIDTH 4
#elif SIZE_MAX == 0xFFFFFFFFFFFFFFFF
#define SIZE_WIDTH 8
#else
#error unknown SIZE_MAX
#endif

#ifdef SCL_CHECK_LIMITS
#include <limits.h>

#if UCHAR_MAX != (0xFF)
#error unsigned char is not 1 byte.
#endif

#if USHRT_MAX != (0xFFFF)
#error unsigned short is not 2 byte.
#endif

#if UINT_MAX != (0xFFFFFFFF)
#error unsigned int is not 4 byte.
#endif

#if ULLONG_MAX != (0xFFFFFFFFFFFFFFFF)
#error unsigned long long is not 8 byte.
#endif

#endif

#define EXIT_ERROR 1
#define EXIT_ARGUMENT_ERROR 2
#define EXIT_NORMAL 0

#include "scl/printf.h"
#include "scl/error.h"
#include "scl/math.h"
#include "scl/random.h"

#ifdef SCL_USE_UNSIGNED_CHAR
#define CHAR unsigned char
#else
#define CHAR char
#endif

#include "scl/io.h"
#include "scl/str.h"

#ifndef SCL_NO_TYPES
#include "scl/types.h"
#endif

#undef CHAR

#undef SCL_DLL_EXPORT

#endif // SCL_H
