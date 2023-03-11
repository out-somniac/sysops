#include "replace_args.h"

bool is_char(const char *string) {
    return (strlen(string) == 1);
}

bool get_arguments(int argc, char** argv, ReplaceArgs *args) {
    if (argc != 4 + 1) {
        fprintf(stderr, "Wrong number of arguments. Expected four arguments.\n");
        return false;
    }
    if ( !is_char(argv[1]) || !is_char(argv[2])) {
        fprintf(stderr, "First two arguments must be a char.\n");
        return false;
    }
    args->to_replace = argv[1][0];
    args->replaced_with = argv[2][0];
    args->in_filename = argv[3];
    args->out_filename = argv[4];
    if ( access(args->in_filename, F_OK) != 0 ) {
        fprintf(stderr, "Input file doesn't exist.\n");
        return false;
    }
    return true;
}