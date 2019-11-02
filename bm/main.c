
/*
*       Brain Machine - The Ultra Powered Virtual Machine
*/

#include <scl.h>

#include "config.h"

#include "header.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [FILE]\n", (argc != 0) ? argv[0] : "bf");
        return EXIT_NORMAL;
    }

    FILE *file;

    file = safe_fopen(argv[1], "rb");
    check_error_info();

#if LONG_MAX > SIZE_MAX
    #error LONG_MAX is greater than SIZE_MAX.
#endif

    size_t file_size = get_file_size(file, &error);
    check_error_info();

    struct bm_header header;
    size_t read_number;

    read_number = safe_fread(&header, sizeof(struct bm_header), file);

    if (header.magic != BM_FILE_MAGIC_NUMBER)
    {
        printf_error("file magic number mismatch: %02llx", header.magic);
        return EXIT_ERROR;
    }

    if (error)
    {
        printf_error("invalid file header size: " SIZE_C, read_number);
        return EXIT_ERROR;
    }

#warning TODO: check header info

    unsigned char *buffer = malloc(BM_BUFFER_SIZE);
    if (!buffer)
    {
        printf_error("can't allocate %s byte memory.",
            format_human_size(BM_BUFFER_SIZE));
        return EXIT_ERROR;
    }

    read_number += fread(buffer, 1, file_size - read_number, file);
    if (read_number != file_size)
    {
        if (ferror(file))
        {
            printf_error("while reading '%s': %s", argv[1], strerror(errno));
            return EXIT_ERROR;
        }
        printf_error("invalid read number: " SIZE_C, read_number);
        return EXIT_ERROR;
    }

    // machine loop

    int32_t eax, ebx, ecx, edx;

    unsigned char *end = buffer + BM_BUFFER_SIZE;
    unsigned char *ip = buffer;

    while (ip != end)
    {
        switch (*ip)
        {
        default:
            printf_error("unknown instruction code: %02hhX", *ip);
            return EXIT_ERROR;
        }
    }
    return EXIT_NORMAL;
}
