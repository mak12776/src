
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTERS (LOWERCASE UPPERCASE)
#define DIGITS "0123456789"

#define STRLEN(string) (sizeof(string) - 1)

#define string_cmp(string, pntr) memcmp(pntr, string, STRLEN(string))

static inline
bool chr_in(char ch, const char *string)
{
    while (*string)
    {
        if (ch == (*string))
        {
            return true;
        }
        string++;
    }
    return false;
}

// find index

static inline
size_t find_test_index(char *pntr, size_t start, size_t end,
    int (*test) (int ch))
{
    size_t index = start;
    while (index < end)
    {
        if (test(pntr[index]))
        {
            return index;
        }
        index += 1;
    }
    return end;
}

static inline
size_t find_chr_index(char *pntr, size_t start, size_t end,
    const char *string)
{
    size_t index = start;
    while (index < end)
    {
        if (chr_in(pntr[index], string))
        {
            return index;
        }
        index += 1;
    }
    return end;
}

static inline
size_t find_chr_not_index(char *pntr, size_t start, size_t end,
    const char *string)
{
    size_t index = start;
    while (index < end)
    {
        if (!chr_in(pntr[index], string))
        {
            return index;
        }
        index += 1;
    }
    return end;
}

// find length

static inline
size_t find_test_length(char *pntr, size_t length, int (*test) (int ch))
{
    return find_test_index(pntr, 0, length, test);
}

static inline
size_t find_chr_length(char *pntr, size_t length, const char *string)
{
    return find_chr_index(pntr, 0, length, string);
}

static inline
size_t find_chr_not_length(char *pntr, size_t length, const char *string)
{
    return find_chr_not_index(pntr, 0, length, string);
}

// rfind index

static inline
size_t rfind_test_index(char *pntr, size_t start, size_t end,
    int (*test) (int ch))
{
    size_t index = end;
    while (index > start)
    {
        index -= 1;
        if (test(pntr[index]))
        {
            return index;
        }
    }
    return end;
}

static inline
size_t rfind_chr_index(char *pntr, size_t start, size_t end,
    const char *string)
{
    size_t index = end;
    while (index > start)
    {
        index -= 1;
        if (chr_in(pntr[index], string))
        {
            return index;
        }
    }
    return end;
}

static inline
size_t rfind_chr_not_index(char *pntr, size_t start, size_t end,
    const char *string)
{
    size_t index = end;
    while (index > start)
    {
        index -= 1;
        if (!chr_in(pntr[index], string))
        {
            return index;
        }
    }
    return end;
}

// strip

static inline
size_t lstrip_chr(char *pntr, size_t *start, size_t *end, const char *string)
{
    *start = find_chr_not_index(pntr, *start, *end, string);
    return (*end) - (*start);
}

static inline
size_t rstrip_chr(char *pntr, size_t *start, size_t *end, const char *string)
{
    size_t index;

    index = rfind_chr_not_index(pntr, *start, *end, string);
    *end = (index == (*end)) ? (*start) : index;

    return (*end) - (*start);
}
