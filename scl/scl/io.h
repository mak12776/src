
static inline
FILE *safe_fopen(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);
    if (file == NULL)
    {
        error = ERROR_FOPEN;
        error_info.file_name = name;
    }
    return file;
}

static inline
int safe_fseek(FILE *file, long offset, int whence)
{
    int result;

    if (result = fseek(file, offset, whence))
    {
        error = ERROR_FSEEK;
    }
    return result;
}

static inline
long safe_ftell(FILE *file)
{
    long file_size;

    if ((file_size = ftell(file)) == -1)
    {
        error = ERROR_FTELL;
    }
    return file_size;
}

static inline
size_t safe_fwrite(void *pntr, size_t size, FILE *file)
{
    if (fwrite(pntr, 1, size, file) != size)
    {
        error = ERROR_IO;
        return 0;
    }
    return size;
}

static inline
size_t fwrite_index(char *pntr, size_t start, size_t end, FILE *file)
{
    return fwrite(pntr, 1, end - start, file);
}

static inline
size_t fwrite_length(char *pntr, size_t length, FILE *file)
{
    return fwrite(pntr, 1, length, file);
}


static inline
long get_file_size(FILE *file, int *error)
{
    long file_size;
    if (fseek(file, 0, SEEK_END) == -1)
    {
        *error = ERROR_FSEEK;
        return 0;
    }

    file_size = ftell(file);
    if (file_size == -1)
    {
        *error = ERROR_FTELL;
        return 0;
    }

    if (fseek(file, 0, SEEK_SET) == -1)
    {
        *error = ERROR_FSEEK;
        return 0;
    }

    return file_size;
}

static inline
void read_file(FILE *file, char **buffer, size_t *size, int *error)
{
    long file_size;
    size_t read_number;

    file_size = get_file_size(file, error);
    if ((*error) != NO_ERROR)
    {
        return;
    }

    if (file_size == 0)
    {
        *error = ERROR_ZERO_FILE_SIZE;
        return;
    }

    #if LONG_MAX > SIZE_MAX
        #error LONG_MAX is greater than SIZE_MAX.
    #endif

    *buffer = (char *)malloc(file_size);
    if (!(*buffer))
    {
        *error = ERROR_NO_MEMORY;
        return;
    }
    *size = file_size;

    read_number = fread(*buffer, 1, file_size, file);
    if (read_number != (size_t)file_size)
    {
        *error = ERROR_IO;
        free(*buffer);
        return;
    }
}

static inline
void read_file_name(char *name, char **buffer, size_t *size, int *error)
{
    FILE *file;

    file = fopen(name, "rb");
    if (file == NULL)
    {
        *error = ERROR_FOPEN;
        return;
    }

    read_file(file, buffer, size, error);
    fclose(file);
}

#if 0

static inline
void split_lines(char *buffer, size_t size, size_t **lines, size_t *total,
    int *error)
{
    size_t index;
    size_t lines_total;
    size_t lines_size;

    if (size == 0)
    {
        *error = ERROR_BAD_ARGUMENTS;
        return;
    }

    index = 0;

#define CH  (buffer[index])
#define END (index == size)

    while (1)
    {
        if (CH == '\n')
        {
            lines_total += 1;

            index += 1;
            if (END)
                break;
        }
        else if (CH == '\r')
        {
            lines_total += 1;

            index += 1;
            if (END)
                break;

            if (CH == '\n')
            {
                index += 1;
                if (END)
                    break;
            }
        }
        else
        {
            index += 1;
            if (END)
            {
                lines_total += 1;
                break;
            }
        }
    }

#undef CH
#undef END

    if (__builtin_mul_overflow(lines_total, sizeof(size_t) * 2, &lines_size))
    {
        *error = ERROR_INT_OVERFLOW;
        return;
    }

    *lines = (size_t *)malloc(lines_size);
    if ((*lines) == NULL)
    {
        *error = ERROR_NO_MEMORY;
        return;
    }
    *total = total;

    while (1)
    {

    }

#warning incomplete

}

#endif // #if 0
