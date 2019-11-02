
/*
*       Brain Machine
*/

#include <scl.h>

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

}
