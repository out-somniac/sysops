#include <stdlib.h>
#include <stdbool.h>

#include "replace_args.h"

#ifdef USE_LIB
    #include "lib_replace.h"
#else
    #include "sys_replace.h"
#endif

int main(int argc, char **argv) {
    ReplaceArgs args;
    if ( !get_arguments(argc, argv, &args) )
        return EXIT_FAILURE;    
    
    #ifdef USE_LIB
    lib_replace(&args);
    #else
    sys_replace(&args);
    #endif
    return EXIT_SUCCESS;
}