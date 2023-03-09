#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>

#include "wcbuffer.h"
#include "lib_loader.h"

#define MAX_COMMAND_SIZE 1024

// *
// Parsing
// *

typedef enum CommandType {
    INIT,
    COUNT,
    SHOW,
    DELETE,
    DESTROY,
    EXIT,
    NONE
} CommandType;

char *command_type_to_string(CommandType command_type) {
    switch(command_type) {
        case INIT:
            return "init";
        case COUNT:
            return "count";
        case SHOW:
            return "show";
        case DELETE:
            return "delete index";
        case DESTROY:
            return "destroy";
        case EXIT:
            return "exit";
        case NONE:
            return "none";
    }
    return "none"; // C is a terrible language
}

bool has_prefix(const char* command, const char* prefix) {
    size_t p_length = strlen(prefix);
    if (strlen(command) < p_length) {
        return false;
    }
    
    char *substring = calloc(p_length + 1, sizeof(char));
    memcpy(substring, &command[0], p_length);
    substring[p_length] = '\0';
    int result = strcmp(substring, prefix);
    free(substring);

    return (result == 0);
}

CommandType parse_command_type(char *command) {
    // Compare against every specified command
    CommandType all_alowed[6] = {INIT, COUNT, SHOW, DELETE, DESTROY, EXIT};
    for(unsigned int i=0;i<6;i++) {
        char *command_type_str = command_type_to_string(all_alowed[i]);
        if (has_prefix(command, command_type_str)) {
            return all_alowed[i];
        }
    }
    return NONE;
}

const char* get_args_str(const char *command, CommandType command_type) {
    size_t prefix_size = strlen(command_type_to_string(command_type));
    if (prefix_size >= strlen(command)) { return NULL; }
    
    return &command[prefix_size];
}

bool get_parsed_int(const char* command, CommandType command_type, int *parsed) {
    const char* args = get_args_str(command, command_type);
    if (args == NULL) { return false; }

    const int result = sscanf(args, "%d", parsed);
    return (result == 1);
}

// *
// Command execution functions
// *

void init(wcBuffer **buffer, int max_size) {
    if (max_size <= 0) {
        fprintf(stderr, "Faulty arguments given to function.\n");
        return;
    }
    if (*buffer != NULL) {
        fprintf(stderr, "Buffer already initialized\n");
        return;
    }
    if (!wcBuffer_initialize(max_size, buffer)) {
        fprintf(stderr, "Failed when initializing buffer\n");
    }
}

void count(wcBuffer *buffer, const char* command) {
    if (buffer == NULL) { 
        fprintf(stderr, "Buffer not yet initialized.\n");
        return;
    }
    const char* filepath = get_args_str(command, COUNT);
    if (!wcBuffer_add_block(buffer, filepath)) {
        printf("Failed while runnig wc on file %s.\n", filepath);
    }
}

void show(wcBuffer *buffer, int index) {
    if (buffer == NULL) { 
        fprintf(stderr, "Buffer not yet initialized.\n");
        return;
    }
    if (index >= buffer->current_blocks || index < 0) {
        fprintf(stderr, "Faulty arguments given to function. Index out of bounds.\n");
        return;
    }
    printf("%s\n", buffer->blocks[index]);
}

void delete(wcBuffer *buffer, int index) {
    if (buffer == NULL) { 
        fprintf(stderr, "Buffer not yet initialized.\n");
        return;
    }
    if (index >= buffer->max_blocks || index < 0) {
        fprintf(stderr, "Faulty arguments given to function. Index out of bounds.\n");
        return;
    }
    wcBuffer_remove_block(buffer, index);
}

void destroy(wcBuffer **buffer) {
    if ((*buffer) == NULL) { 
        fprintf(stderr, "Buffer not yet initialized.\n");
        return;
    }
    wcBuffer_free(buffer);
    (*buffer) = NULL;
}

// *
// Time measurements
// *

typedef struct {
    clock_t real_time;
    clock_t user_time;
    clock_t system_time;
} TimeMeasurement;

TimeMeasurement time_measurement(void) {
    TimeMeasurement tm;
    struct tms tms_time;
    tm.real_time = times(&tms_time);
    tm.user_time = tms_time.tms_utime;
    tm.system_time = tms_time.tms_stime;
    return tm;
}

void print_time_info(TimeMeasurement tm_start, TimeMeasurement tm_end) {
    double real_delta = (double) (tm_end.real_time - tm_start.real_time);
    double user_delta = (double) (tm_end.user_time - tm_start.user_time);
    double system_delta = (double) (tm_end.system_time - tm_start.system_time);
    printf("\tReal:   %10fs\n", 10000*real_delta   / CLOCKS_PER_SEC);
    printf("\tUser:   %10fs\n", 10000*user_delta   / CLOCKS_PER_SEC);
    printf("\tSystem: %10fs\n", 10000*system_delta / CLOCKS_PER_SEC);
}

int main(void) {
    load_shared("libwc.so");

    char command[MAX_COMMAND_SIZE];
    wcBuffer *buffer = NULL;

    TimeMeasurement time_start, time_end;
    while(true) {
        printf("repl> ");
        if(fgets(command, MAX_COMMAND_SIZE, stdin) == NULL) {
            printf("Failed while reading next line or reached end of stream.");
            continue;
        }

        time_start = time_measurement(); 
        command[strcspn(command, "\r\n")] = 0; // Removing the trailing \n or \r
        CommandType command_type = parse_command_type(command);

        if (command_type == EXIT) {
            break;
        }

        int parsed_arg = -1;
        if (command_type != COUNT && command_type != DESTROY &&
            !get_parsed_int(command, command_type, &parsed_arg))
        {
            fprintf(stderr, "Faulty arguments given to function\n");
            continue;
        }
        
        switch(command_type) {
            case INIT:
                init(&buffer, parsed_arg);
                break;
            case COUNT:
                count(buffer, command);
                break; // Previously handled
            case SHOW:
                show(buffer, parsed_arg);
                break;
            case DELETE:
                delete(buffer, parsed_arg);
                break;
            case DESTROY:
                destroy(&buffer);
                break;
            case EXIT:
                break; // Previously handled
            case NONE:
                fprintf(stderr, "Unknown command.\n");
                break;
        }

        time_end = time_measurement();
        print_time_info(time_start, time_end);
    }
    free(buffer);
    close_shared();
    return EXIT_SUCCESS;
}