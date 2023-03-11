#ifndef LIB_REPLACE_H
#define LIB_REPLACE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "replace_args.h"

size_t lib_file_size(FILE* file);
bool lib_replace(ReplaceArgs *args);

#endif