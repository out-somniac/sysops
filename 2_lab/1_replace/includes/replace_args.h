#ifndef REPLACE_ARGS_H
#define REPLACE_ARGS_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    char to_replace, replaced_with;
    char *in_filename;
    char *out_filename;
} ReplaceArgs;

bool is_char(const char *string);
bool get_arguments(int argc, char** argv, ReplaceArgs *args);

#endif