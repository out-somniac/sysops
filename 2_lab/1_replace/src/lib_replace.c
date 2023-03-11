#include "lib_replace.h"

size_t lib_file_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return (size_t) size;
}

bool lib_replace(ReplaceArgs *args) {
    FILE* in_file = fopen(args->in_filename, "r");
    if ( !in_file ) {
        fprintf(stderr, "Failed to open input file.\n");
        return false;
    } 
    FILE* out_file = fopen(args->out_filename, "w");
    
    if ( !out_file ) {
        fprintf(stderr, "Failed to open output file.\n");
        fclose(in_file);
        return false;
    }

    size_t in_size = lib_file_size(in_file);
    char *buffer = calloc(in_size, sizeof(char));
    fread(buffer, sizeof(char), in_size, in_file);
    for(size_t i=0;i<in_size;i++) {
        if ( buffer[i] == args->to_replace ) {
            buffer[i] = args->replaced_with;
        }
    }
    fwrite(buffer, sizeof(char), in_size, out_file);

    free(buffer);
    fclose(in_file);
    fclose(out_file);
    return true;
}