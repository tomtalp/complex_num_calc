#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "complex.h"


#define AVAILABLE_COMMANDS_COUNT  9
#define MAX_COMMAND_LEN          15
#define AVAILABLE_VARS_COUNT      6

#define MULTIPLE_NUMBER_ARGS      1
#define SINGLE_NUMBER_ARGS        2
#define SINGLE_COMP_ARGS          3
#define EMPTY_ARGS                4




int is_valid_command_name(char *command_name);
int is_valid_var(char var_name);
void trim_leading_whitespace(char *source);
void remove_whitespace(char *str);
void get_command_name(char *source, char *command_name);
void prep_raw_command_for_parsing(char *raw_command);
int get_command_args(char *raw_command, char **args_array);
int is_valid_num(char *num_as_str);
int get_command_legal_args(char *command_name);
int validate_command_args(char *command_name, char **args, int arg_size);
void parse_command_args(char *command_name, char *raw_command);

// struct {
//     char *command_name;
//     void (*command_func)();
//     char **command_legal_args;
// } COMMANDS[] = {
//     {"read_comp", read_comp, READ_COMP_LEGAL_ARGS},
//     {"print_comp", print_comp, PRINT_COMP_LEGAL_ARGS},
// };


struct {
    char *command_name;
    int command_legal_args;
} COMMANDS[] = {
    {"read_comp", MULTIPLE_NUMBER_ARGS},
    {"print_comp", EMPTY_ARGS},
    {"add_comp", SINGLE_COMP_ARGS},
    {"sub_comp", SINGLE_COMP_ARGS},
    {"mult_comp_real", SINGLE_NUMBER_ARGS},
    {"mult_comp_img", SINGLE_NUMBER_ARGS},
    {"mult_comp_comp", SINGLE_COMP_ARGS},
    {"abs_comp", EMPTY_ARGS},
    {"stop", EMPTY_ARGS}
};

char *VAR_NAMES[] = {
    "A", "B", "C", "D", "E", "F"
};

// char *COMMANDS[] = {
//     "read_comp",
//     "print_comp",
//     "add_comp",
//     "sub_comp",
//     "mult_comp_real",
//     "mult_comp_imp",
//     "mult_comp_comp",
//     "abs_comp",
//     "stop"
// };

/* 
    Validate a command name by checking if it has a trailing comma, or if it's
    in the list of known commands.
*/
int is_valid_command_name(char *command_name) {
    // printf("Evaluating command '%s'\n", command_name);
    int i;
    int is_known_command = 0;

    if (command_name[strlen(command_name)-1] == ',') {
        printf("Illegal comma\n");
        return 0;
    }

    for (i=0; i<AVAILABLE_COMMANDS_COUNT; i++) {
        if (strcmp(COMMANDS[i].command_name, command_name) == 0) {
            is_known_command = 1;
            break;
        }
    }

    if (is_known_command == 0) {
        printf("Undefined command name\n");
        return 0;
    }
    
    return 1;
}

int is_valid_var(char var_name) {
    int i;
    // if (strlen(var_name) != 1) {
    //     return -1;
    // }
    for (i=0; i < AVAILABLE_VARS_COUNT; i++) {
        // if (strcmp(var_name, VAR_NAMES[i]) == 0) {
        if (var_name == *VAR_NAMES[i]) {
            return 1;
        }
    }
    return -1;
}

void trim_leading_whitespace(char *source) {
    char * start = source;
    
    while (isspace(*start)) {
        start++;
    }

    while (*start != 0) {
        *source = *start;
        source++;
        start++;
    }   
    *source = '\0'; /* Terminate the string */
}

void remove_whitespace(char *str) {
    char *i = str;

    while (*i != 0) {
        *str = *i;
        i++;
        if (!isspace(*str)) {
            str++;
        }
    }
    *str = '\0';
}

void get_command_name(char *source, char *command_name) {
    char *sourceStart = source;
    // printf("Source right in the start - '%s'\n", source);

    /* Locate the command name */
    while (*sourceStart != 0 && !isspace(*sourceStart)) {
        *command_name = *sourceStart;
        command_name++;
        sourceStart++;
        // printf("Source in end of while - '%s'\n", source);        
    }
    // printf("Source at end of while - '%s'\n", source);        
    *command_name = '\0'; /* TODO - Do I need this? */
    // printf("Source after messing with command_name - '%s'\n", source);
    /* Remove the command name from source */
    // printf("Source before overwriting - %s, sourceStart - %s, command-14 - '%s'\n", source, sourceStart, command_name-14);
    while (*sourceStart != 0) {
        *source = *sourceStart;
        // printf("Found character %c in sourceStart, so now source has %c\n", *command_name, *sourceStart);
        source++;
        sourceStart++; 
    }
    *source = '\0';
    // printf("And in the end source before overwriting - %s, sourceStart - %s, command-14 - '%s'\n", source-14, sourceStart-14, command_name-14);
}

/*
    Prepare the raw command for parsing - remove leading whitespace & trailing '\n'
*/
void prep_raw_command_for_parsing(char *raw_command) {
    strtok(raw_command, "\n");
    trim_leading_whitespace(raw_command);
}

/*
    Parse the command args from the raw command, and return the amount of detected args.
*/
int get_command_args(char *raw_command, char **args_array) {
    char *command_arg_token;
    int detected_args = 0;
    command_arg_token = strtok(raw_command, ",");

    while (command_arg_token != NULL) {
        remove_whitespace(command_arg_token);
        args_array[detected_args++] = command_arg_token;
        command_arg_token = strtok(NULL, ",");
    }

    return detected_args;
}

int is_valid_num(char *num_as_str) {
    char *err_ptr;
    strtof(num_as_str, &err_ptr);
    if (*err_ptr != '\0') {
        return -1;
    }
    return 1;
}

int get_command_legal_args(char *command_name) {
     int i;
     for (i=0; i<AVAILABLE_COMMANDS_COUNT; i++) {
        if (strcmp(COMMANDS[i].command_name, command_name) == 0) {
            return COMMANDS[i].command_legal_args;
        }
    }
    return -1;
}

// void exec_command(char *command_name, char **args, int arg_size, Variables *vars) {
//     if (arg_size == 0) {
//         printf("Missing parameter\n");
//         return;
//     }
//     char *main_var_name = args[0];
//     Complex *main_comp = access_variable(vars, main_var_name);

//     if (main_comp == NULL) {
//         printf("Undefined complex variable\n");
//         return;
//     }

//     if (strcmp(command_name, "read_comp") == 0) {
//         float f1 = atof(args[1]);
//         float f2 = atof(args[2]);

//         read_comp(main_comp, f1, f2);
        
//     } else if (strcmp(command_name, "print_comp") == 0) {
//         print_comp(main_comp);
//     } else if (strcmp(command_name, "add_comp") == 0) {
//         char *varName2 = args[0];
//         Complex *c2 = access_variable(vars, varName2);
//         add_comp(main_comp, c2);
//     } else if (strcmp(command_name, "sub_comp") == 0) {
//         char *varName2 = args[0];
//         Complex *c2 = access_variable(vars, varName2);
//         sub_comp(main_comp, c2);
//     } else if (strcmp(command_name, "mult_comp_real") == 0) {
//         float f1 = atof(args[1]);
//         mult_comp_real(main_comp, f1);        
//     } else if (strcmp(command_name, "mult_comp_img") == 0) {
//         float f1 = atof(args[1]);
//         mult_comp_img(main_comp, f1);        
//     } else if (strcmp(command_name, "mult_comp_comp") == 0) {
//         char *varName2 = args[0];
//         Complex *c2 = access_variable(vars, varName2);
//         mult_comp_comp(main_comp, c2);
//     } else if (strcmp(command_name, "abs_comp") == 0) {
//         abs_comp(main_comp);
//     } else {
//         printf("Undefined command name\n"); // TODO Do I need this? Never supposed to reach this anyway
//     }
// }

/*
    Parse the command args, with the following rules - 
        1. All commands except "stop" must begin with a legal var name
        2. Depending on the command, we evaluate the type of the next args (num, varname etc)
*/
void parse_command_args(char *command_name, char *raw_command) {
    // printf("raw_command = '%s'\n", raw_command);
    char *p_command = raw_command;
    char *delim_ptr;
    // char var_name[80];
    char var_name;
    int delim_loc = 0;
    int i;

    while (isspace(*raw_command)) {
        raw_command++;
    }

    // printf("raw_command after initial WS trim = '%s'\n", raw_command);

    var_name = *raw_command;
    raw_command++;
    if (var_name == ',') {
        printf("Illegal comma\n");
        return;
    } else if (is_valid_var(var_name) == -1) {
        printf("Undefined complex variable (%c doesn't exist)\n", var_name);
        return;
    } 
    
    // else if (!isspace(*raw_command) && *raw_command != ',') { // Anything after the first character can only be whitespace or comma
    //     printf("Undefined complex variable (var can only be 1 character...)\n");
    //     return;
    // }

    // Move to the first character after the varname that isn't a whitespace
    // while (isspace(*raw_command)) {
    //     raw_command++;
    // }

    // printf("Detected var_name = '%c', remaining command = '%s'\n", var_name, raw_command); 


    if (!isspace(*raw_command) && (isalpha(*raw_command) || isdigit(*raw_command))) {
        printf("Undefined complex variable (var can only be 1 character...)\n");
        return;
    }
    while (isspace(*raw_command)) {
        raw_command++;
    }

    // if (*raw_command != ',') {
    //     printf("Missing comma\n");
    //     return;
    // }
    // raw_command++; // Skip the comma we just found.
    // printf("What's left after raw_command after detecting the first comma - '%s'\n", raw_command);

    // // Move to the first character after the first comma that isn't a whitespace
    // while (isspace(*raw_command)) {
    //     raw_command++;
    // } 
    // printf("What's left after raw_command after detecting the first comma AND skipping WS- '%s'\n", raw_command);
    int legal_args = get_command_legal_args(command_name);

    switch (legal_args) {
        case EMPTY_ARGS:
            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }
            printf("EMPTY ARGS COMMAND WORKED!\n");
            break;

        case SINGLE_NUMBER_ARGS:
            printf("IN SINGLE_NUMBER_ARGS\n");
            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; // Skip comma we just detected
            while (isspace(*raw_command)) {
                raw_command++;
            }

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            char *first_num = raw_command;
            if (is_valid_num(first_num) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            printf("SINGLE_NUMBER_ARGS COMMAND WORKED! first_num = %s\n", first_num);
            break;
        
        case SINGLE_COMP_ARGS:
            printf("IN SINGLE_COMP_ARGS\n");

            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; // Skip comma we just detected

            while (isspace(*raw_command)) {
                raw_command++;
            }

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            char second_var_name = raw_command[0];
            raw_command++;
            if (is_valid_var(second_var_name) == -1) {
                printf("Undefined complex variable as second parameter\n");
                return;
            }

            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }
            printf("SINGLE_COMP_ARGS COMMAND WORKED! second_varname = '%c'\n", second_var_name);
            break;
        
        case MULTIPLE_NUMBER_ARGS:
            printf("IN MULTIPLE_NUMBER_ARGS\n");
            // printf("raw_command = '%s'\n", raw_command);

            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; // Skip comma we just detected
            while (isspace(*raw_command)) {
                raw_command++;
            }

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            // printf("And now we have - '%s'\n", raw_command);
            
            char first_num1[80];
            int i = 0;
            while (!isspace(*raw_command) && *raw_command != ',') {
                first_num1[i++] = *raw_command;
                raw_command++;
            }

            first_num1[i] = '\0';
            if (is_valid_num(first_num1) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            // printf("First num = '%s', remaining from raw_command = '%s'\n", first_num1, raw_command);

            while (isspace(*raw_command)) {
                raw_command++;
            }

            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; // Skip comma we just detected

            while (isspace(*raw_command)) {
                raw_command++;
            }

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            // printf("Remaining from raw_command = '%s'\n", raw_command);

            char second_num1[80];
            int j = 0;
            while (!isspace(*raw_command) && *raw_command != ',' && strlen(raw_command) > 0) {
                second_num1[j++] = *raw_command;
                raw_command++;
            }

            second_num1[i] = '\0';
            if (is_valid_num(second_num1) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            // printf("Second num = '%s', remaining from raw_command = '%s'\n", second_num1, raw_command);
            printf("MULTIPLE_NUMBER_ARGS COMMAND WORKED! \n");
            break;

            
            
            return;
    }
}

int main() {
    // char raw_command[1000] = "  read_comp A, B,   2      s   ";
    // char raw_command[1000] = "print_comp";
    char raw_command[80], raw_command_bkup[80];
    // char raw_command_bkup[80], raw_command[80] = "read_comp A , 2 , 3";
    char command_name[MAX_COMMAND_LEN] = "";
    char *command_args[10];
    int arg_size;
    
    char *p_command;
    int exit_status_code = 0;

    Variables vars;
    vars = init_variables();

    while (1) {
        /* TODO - Do I need this?? */
        // memset(raw_command, 0, sizeof(raw_command));
        printf(">>> ");

        p_command = fgets(raw_command, 100000, stdin);
        /* TODO - THIS WON'T WORK WITH raw_command == NULL, and I need the additional pointer. WHY?! */
        if (p_command == NULL) { 
            printf("Improper exit... leaving\n");
            return 0;
        }

        prep_raw_command_for_parsing(raw_command);
        printf("%s\n", raw_command);
        strcpy(raw_command_bkup, raw_command);
        // printf("raw_command after prep_for_parsing = '%s'\n", raw_command);

        get_command_name(raw_command, command_name);
        // printf("Command name detected = '%s'\n", command_name);
        // Remove any leftover whitespaces between command name & args
        // trim_leading_whitespace(raw_command);
        // printf("Command name = '%s', command_size = %ld, remaining command = '%s'\n", command_name, strlen(command_name),raw_command);
        
        // if (raw_command[strlen(raw_command)-1] == ',') {
        //     printf("Extraneous text after end of command\n");
        //     continue;
        // }

        if (!is_valid_command_name(command_name)) {
            continue;
        }

        if (strcmp(command_name, "stop") == 0) {
            if (strlen(raw_command) != 0) {
                printf("Extraneous text after end of command\n");
                continue;
            }
            return 0;
        }

        parse_command_args(command_name, raw_command);
        continue;

    }
    return 0;
}

