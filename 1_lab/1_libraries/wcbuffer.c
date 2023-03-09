#include "wcbuffer.h"

// Helper functions
bool run_wc(const char *filepath, const char *destination) {
    // the string "wc > " is 5 characters chence the +5
    unsigned int command_length = strlen(destination) + strlen(filepath) + 6 + 1;
    char *command = calloc(command_length, sizeof(char));
    snprintf(command, command_length, "wc %s > %s", filepath, destination);
    if (system(command) == -1) {
         return false;
    }
    return true;
}

bool read_from_file(char **block, const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) { return false; }
    
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
    if (file_size <= 0) { goto fail; }

    *block = calloc((file_size + 1), sizeof(char));
    fread(*block, sizeof(char), file_size, file);
    fclose(file);
    return true;

    fail:
        fclose(file);
        return false;
}

// wcBuffer functions
bool wcBuffer_initialize(unsigned int max_blocks, wcBuffer **buffer) {
    char **blocks = calloc(max_blocks, sizeof(char*));
    if(blocks == NULL) { return false; }

    (*buffer) = malloc(sizeof(wcBuffer));
    if (*buffer == NULL ) { return false; }
    
    (*buffer)->max_blocks = max_blocks;
    (*buffer)->current_blocks = 0;
    (*buffer)->blocks = blocks;
    return true;
}

void wcBuffer_free(wcBuffer **buffer) {
    for(unsigned int i=0;i<(*buffer)->current_blocks;i++) {
        wcBuffer_remove_block(*buffer, i);
    }
    free((*buffer)->blocks);
    free(*buffer);
}

bool wcBuffer_add_block(wcBuffer *buffer, const char *filepath) {
    if (buffer->max_blocks <= buffer->current_blocks) { return false; }
    
    char temp_name[] = "/tmp/wc-XXXXXX";
    int temp_file_descriptor= mkstemp(temp_name);
    if (temp_file_descriptor == -1) { return false; }
    unlink(temp_name);

    if (!run_wc(filepath, temp_name)) {
        return false;
    }

    if (!read_from_file(&buffer->blocks[buffer->current_blocks], temp_name)) {
        return false;
    }
    buffer->current_blocks += 1;
    remove(temp_name);
    return true;
}

char* wcBuffer_get_block(wcBuffer *buffer, unsigned int index) {
    return buffer->blocks[index]; 
}

void wcBuffer_remove_block(wcBuffer *buffer, unsigned int index) {
    // Note that NULL is a correct parameter for free
    // so this works even if the block's already been freed
    free(buffer->blocks[index]);
}