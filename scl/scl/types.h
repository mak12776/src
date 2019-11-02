
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

// function declarations

static inline
void buffer_read_file(buffer_t *buffer, FILE *file);

static inline
void buffer_read_file_name(buffer_t *buffer, char *name);

static inline
size_t buffer_count_lines(buffer_t *buffer);

static inline
void buffer_split_lines(buffer_t *buffer, lines_t *lines);

static inline
size_t buffer_write_view(buffer *buffer, buffer_view_t *view);

static inline
void lines_initialize_total(lines_t *lines, size_t total);

// function definitions

static inline
void buffer_read_file(buffer_t *buffer, FILE *file)
{
    read_file(file, &(buffer->pntr), &(buffer->size), &error);
}

static inline
void buffer_read_file_name(buffer_t *buffer, char *name)
{
    read_file_name(name, &(buffer->pntr), &(buffer->size), &error);
}

static inline
size_t buffer_count_lines(buffer_t *buffer)
{
    size_t index;
    size_t total;

    if (buffer->size == 0)
    {
        error = ERROR_BAD_ARGUMENTS;
        return 0;
    }

#define CH (buffer->pntr[index])
#define END (index == (buffer->size))

        index = 0;
        total = 0;

        while (1)
        {
            if (CH == '\r')
            {
                total += 1;

                index += 1;
                if (END) break;

                if (CH == '\n')
                {
                    index += 1;
                    if (END) break;
                }
            }
            else if (CH == '\n')
            {
                total += 1;

                index += 1;
                if (END) break;
            }
            else
            {
                index += 1;
                if (END)
                {
                    total += 1;
                    break;
                }
            }
        }

#undef CH
#undef END

    return total;
}

static inline
void buffer_split_lines(buffer_t *buffer, lines_t *lines)
{
    size_t index;
    size_t lnum;
    size_t total;

    total = buffer_count_lines(buffer);
    if (error) return;

    lines_initialize_total(lines, total);
    if (error) return;

#define CH (buffer->pntr[index])
#define END (index == buffer->size)
#define LINE (lines->pntr[lnum])

    index = 0;
    lnum = 0;

loop:
    LINE.start = index;

    while (1)
    {
        if (CH == '\n')
        {
            index += 1;
            LINE.end = index;

            if (END) break;

            lnum += 1;
            goto loop;
        }
        else if (CH == '\r')
        {
            CH = '\n';

            index += 1;
            LINE.end = index;

            if (END) break;

            if (CH == '\n')
            {
                index += 1;
                if (END) break;
            }

            lnum += 1;
            goto loop;
        }
        else
        {
            index += 1;
            if (END)
            {
                LINE.end = index;
                break;
            }
        }
    }

#undef CH
#undef END
#undef LINE

}

static inline
size_t buffer_write_view(buffer *buffer, buffer_view_t *view)
{
    
}

static inline
void lines_initialize_total(lines_t *lines, size_t total)
{
    size_t lines_size;

    lines_size = check_overflow(mul, total, sizeof(buffer_view_t));
    if (error) return;

    lines->pntr = (buffer_view_t *)malloc(lines_size);
    if (lines->pntr == NULL)
    {
        error = ERROR_NO_MEMORY;
        return;
    }
    lines->total = total;
}
