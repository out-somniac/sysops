#ifndef WCB_LIB
#define WCB_LIB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    unsigned int max_blocks, current_blocks;
    char **blocks;  
} wcBuffer;

#ifdef USE_SHARED

    bool  (*wcBuffer_initialize) (unsigned int, wcBuffer**);
    void  (*wcBuffer_free) (wcBuffer**);
    bool  (*wcBuffer_add_block) (wcBuffer*, const char*);
    char* (*wcBuffer_get_block) (wcBuffer*, unsigned int);
    void  (*wcBuffer_remove_block) (wcBuffer*, unsigned int);

#else

    bool wcBuffer_initialize(unsigned int max_blocks, wcBuffer **buffer);
    void wcBuffer_free(wcBuffer **buffer);
    bool wcBuffer_add_block(wcBuffer *buffer, const char *filepath);
    char* wcBuffer_get_block(wcBuffer *buffer, unsigned int index);
    void wcBuffer_remove_block(wcBuffer *buffer, unsigned int index);

#endif
#endif