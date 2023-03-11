#include "sys_replace.h"

size_t sys_file_size(int file_descriptor) {
    size_t size = (size_t) lseek(file_descriptor, 0L, SEEK_END);
    lseek(file_descriptor, 0L, SEEK_SET);
    return size;
}

bool sys_replace(ReplaceArgs *args) {
    int in_file_descriptor = open(args->in_filename, O_RDONLY);
    if ( in_file_descriptor == -1) {
        fprintf(stderr, "Failed to open input file.\n");
        return false;
    }

    int out_file_descriptor = open(args->out_filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (out_file_descriptor == -1) {
        fprintf(stderr, "Failed to open output file.\n");
        close(in_file_descriptor);
        return false;
    }

    size_t in_size = sys_file_size(in_file_descriptor);
    char *buffer = calloc(in_size, sizeof(char));
    read(in_file_descriptor, buffer, in_size * sizeof(char));
    for(size_t i=0;i<in_size;i++) {
        if ( buffer[i] == args->to_replace ) {
            buffer[i] = args->replaced_with;
        }
    }
    write(out_file_descriptor, buffer, in_size * sizeof(char));

    close(in_file_descriptor);
    close(out_file_descriptor);
    free(buffer);
    return true;
}