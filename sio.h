
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

static inline
void read_file()

#endif // SIO_H
