#ifndef SHARED_LOADER_H
#define SHARED_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>

#include "wcbuffer.h"

void *_handle = NULL;

#ifdef USE_DYNAMIC

bool load_shared(const char* filepath) {
    _handle = dlopen(filepath, RTLD_LAZY);
    if ( _handle == NULL ) {
        fprintf(stderr, "Failed to load symbols from a library\n");
        return false;
    }

    *(void **) (&wcBuffer_initialize) = dlsym(_handle, "wcBuffer_initialize");
    *(void **) (&wcBuffer_free) = dlsym(_handle, "wcBuffer_free");
    *(void **) (&wcBuffer_add_block) = dlsym(_handle, "wcBuffer_add_block");
    *(void **) (&wcBuffer_get_block) = dlsym(_handle, "wcBuffer_get_block");
    *(void **) (&wcBuffer_remove_block) = dlsym(_handle, "wcBuffer_remove_block");

    return true;
}

void close_shared(void) {
    dlclose(_handle);
}

#else

bool load_shared(const char* filepath) { return false;}
void close_shared(void) {}

#endif

#endif