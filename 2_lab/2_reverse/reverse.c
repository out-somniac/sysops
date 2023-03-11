#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/times.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

size_t file_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return (size_t) size;
}

void swap(char *left, char *right) {
    char temp = *left;
    *left = *right;
    *right = temp;
}

void reverse(char *buffer, size_t size) {
    for(int i = 0; i< size / 2; ++i) {
        swap(&buffer[i], &buffer[size-i-1]);
    }
}

bool reverse_into(const char* in_filename, const char* out_filename) {
    FILE *in_file = fopen(in_filename, "r");
    if ( !in_file ) {
        fprintf(stderr, "Failed to open input file.\n");
        return false;
    }
    FILE *out_file = fopen(out_filename, "w");
    if ( !out_file ) {
        fprintf(stderr, "Failed to open output file.\n");
        fclose(in_file);
        return false;
    }

    size_t in_file_size = file_size(in_file);
    char *buffer = calloc(in_file_size, sizeof(char));

    size_t index = 0;
    while( !feof(in_file) ) {
        index = fread(&buffer[index], sizeof(char), BUFFER_SIZE, in_file);
    }
    reverse(buffer, in_file_size);
    fwrite(buffer, sizeof(char), in_file_size, out_file);

    free(buffer);
    fclose(in_file);
    fclose(out_file);
    return true;
}

int main(int argc, char **argv) {
    if ( argc != 3 ) {
        fprintf(stderr, "Wrong number of arguments. Expected two.\n");
        return EXIT_FAILURE;
    }
    struct timespec time_start, time_end;
    clock_gettime(CLOCK_REALTIME, &time_start);

    if ( !reverse_into(argv[1], argv[2]) ) {
        return EXIT_FAILURE;
    }
    
    clock_gettime(CLOCK_REALTIME, &time_end);
    printf("%d %10f\n", BUFFER_SIZE, (double)(time_end.tv_nsec - time_start.tv_nsec) / 1000000000 );
    return EXIT_SUCCESS;
}