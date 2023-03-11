#include <stdlib.h>
#include <stdio.h>
#include <ftw.h>

#define MAX_DESCRIPTORS 1
#define FTW_CONTINUE 0

static off_t total = 0;

int print_size(const char* filepath, const struct stat *info, int flag) {
    switch (flag) {
        case FTW_D:
        case FTW_DNR:
        case FTW_NS:
            return FTW_CONTINUE;
        case FTW_F:
            break;
    }

    printf("%-15jd %s\n", info->st_size, filepath);
    total += info->st_size;
    return FTW_CONTINUE;
}

int main(int argc, char **argv) {
    if ( argc != 2 ) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return EXIT_FAILURE;
    }
    const char *directory_name = argv[1];
    if ( ftw(directory_name, print_size, MAX_DESCRIPTORS) == -1 ) {
        perror("ftw failed: ");
        return EXIT_FAILURE;
    }
    printf("%jd total\n", total);
    return EXIT_SUCCESS;
}