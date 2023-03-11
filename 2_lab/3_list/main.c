#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    DIR *directory = opendir(".");
    if ( directory == NULL ) {
        fprintf(stderr, "Failed to open current directory.\n");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct stat info;
    off_t total = 0;
    while( (entry = readdir(directory)) != NULL ) {
        if ( stat(entry->d_name, &info) != 0 ) {
            fprintf(stderr, "Can't get info about file: %s\n", entry->d_name);
            continue;
        }

        if( !S_ISDIR(info.st_mode) ) {
            printf("%-15jd %s\n", info.st_size, entry->d_name);
            total += info.st_size;
        }
    }
    printf("total %jd\n", total);
    closedir(directory);
    return EXIT_SUCCESS;
}