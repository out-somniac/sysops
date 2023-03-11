#ifndef SYS_REPLACE_H
#define SYS_REPLACE_H

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> 

#include "replace_args.h"

size_t sys_file_size(int file_descriptor);
bool sys_replace(ReplaceArgs *args);

#endif