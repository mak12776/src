
#ifndef SIO_H
#define SIO_H 1

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    char *pntr;
    size_t size;
} buffer_t;

typedef struct
{
    size_t start;
    size_t end;
} buffer_view_t;

typedef struct
{
    buffer_view_t *pntr;
    size_t total;
} lines_t;

typedef struct
{
    buffer_t buffer;
    lines_t lines;
} buffer_lines_t;

#endif // SIO_H
