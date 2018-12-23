#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "complex.h"

#define AVAILABLE_COMMANDS_COUNT  9
#define MAX_COMMAND_NAME_LEN     15
#define AVAILABLE_VARS_COUNT      6
#define MAX_RAW_COMMAND_LEN      80
#define MULTIPLE_NUMBER_ARGS      1
#define SINGLE_NUMBER_ARGS        2
#define SINGLE_COMP_ARGS          3
#define EMPTY_ARGS                4

int is_valid_command_name(char *command_name);
int is_valid_var(char var_name);
void trim_leading_whitespace(char *source);
void get_command_name(char *raw_command, char *command_name);
void prep_raw_command_for_parsing(char *raw_command);
int is_valid_num(char *num_as_str);
int get_command_legal_args(char *command_name);
void parse_command_args(char *command_name, char *raw_command, Variables *vars);

// struct {
//     char *command_name;
//     void (*command_func)(void);
//     int command_legal_args;
// } COMMANDS[] = {
//     {"read_comp", read_comp, MULTIPLE_NUMBER_ARGS},
//     {"print_comp", print_comp, EMPTY_ARGS},
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

/* 
    Validate a command name by checking if it has a trailing comma, or if it's
    in the list of known commands.
*/
int is_valid_command_name(char *command_name) {
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

    for (i=0; i < AVAILABLE_VARS_COUNT; i++) {
        if (var_name == *VAR_NAMES[i]) {
            return 1;
        }
    }
    return -1;
}

void trim_leading_whitespace(char *source) {
    char *start = source;
    
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

void get_command_name(char *raw_command, char *command_name) {
    char *raw_command_star = raw_command;

    /* Locate the command name */
    while (*raw_command_star != 0 && !isspace(*raw_command_star)) {
        *command_name = *raw_command_star;
        command_name++;
        raw_command_star++;
    }
    *command_name = '\0'; /* TODO - Do I need this? */
    
    /* Remove the command name from raw_command */
    
    while (*raw_command_star != 0) {
        *raw_command = *raw_command_star;
        raw_command++;
        raw_command_star++; 
    }
    *raw_command = '\0';
}

/*
    Prepare the raw command for parsing - remove leading whitespace & trailing '\n'
*/
void prep_raw_command_for_parsing(char *raw_command) {
    strtok(raw_command, "\n");
    trim_leading_whitespace(raw_command);
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

void exec_multi_number_args_command(Variables *vars, char *command_name, char var_name, float f1, float f2) {
    Complex *c;
    c = access_variable(vars, var_name);
    if (strcmp(command_name, "read_comp") == 0) {
        read_comp(c, f1, f2);
    }
}

void exec_empty_args_command(Variables *vars, char *command_name, char var_name) {
    Complex *c;
    c = access_variable(vars, var_name);
    if (strcmp(command_name, "print_comp") == 0) {
        print_comp(c);
    } else if (strcmp(command_name, "abs_comp") == 0) {
        abs_comp(c);
    }
}

void exec_single_comp_args_command(Variables *vars, char *command_name, char var_name, char var_name_2) {
    Complex *c1, *c2;
    c1 = access_variable(vars, var_name);
    c2 = access_variable(vars, var_name_2);

    if (strcmp(command_name, "add_comp") == 0) {
        add_comp(c1, c2);
    } else if (strcmp(command_name, "sub_comp") == 0) {
        sub_comp(c1, c2);
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        mult_comp_comp(c1, c2);
    }
}

void exec_single_number_args_command(Variables *vars, char *command_name, char var_name, float f1) {
    Complex *c;
    c = access_variable(vars, var_name);
    if (strcmp(command_name, "mult_comp_img") == 0) {
        mult_comp_img(c, f1);
    } else if (strcmp(command_name, "mult_comp_real") == 0) {
        mult_comp_real(c, f1);
    }
}

/*
    Parse the command args, with the following rules - 
        1. All commands except "stop" must begin with a legal var name
        2. Depending on the command, we evaluate the type of the next args (num, varname etc)
*/
void parse_command_args(char *command_name, char *raw_command, Variables *vars) {
    char var_name, second_var_name;
    int i = 0, j = 0, legal_args;
    char first_num_str[MAX_RAW_COMMAND_LEN], second_num_str[MAX_RAW_COMMAND_LEN];
    float first_num, second_num;

    /* First character we encounter must be the var name */
    var_name = *raw_command;
    raw_command++;

    if (var_name == ',') {
        printf("Illegal comma\n");
        return;
    } else if (is_valid_var(var_name) == -1) {
        printf("Undefined complex variable (%c doesn't exist)\n", var_name);
        return;
    } 

    if (!isspace(*raw_command) && (isalpha(*raw_command) || isdigit(*raw_command))) {
        printf("Undefined complex variable (var can only be 1 character...)\n");
        return;
    }

    trim_leading_whitespace(raw_command);

    legal_args = get_command_legal_args(command_name);

    switch (legal_args) {
        case EMPTY_ARGS:
            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }
            exec_empty_args_command(vars, command_name, var_name);
            break;

        case SINGLE_NUMBER_ARGS:
            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }

            raw_command++; /* Skip comma we just detected */
            trim_leading_whitespace(raw_command);

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            while (!isspace(*raw_command) && *raw_command != ',' && strlen(raw_command) > 0) {
                first_num_str[i++] = *raw_command;
                raw_command++;
            }

            first_num_str[i] = '\0';
            if (is_valid_num(first_num_str) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            first_num = atof(first_num_str);

            trim_leading_whitespace(raw_command);

            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }

            exec_single_number_args_command(vars, command_name, var_name, first_num);
            break;
        
        case SINGLE_COMP_ARGS:
            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; /* Skip comma we just detected */

            trim_leading_whitespace(raw_command);

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            second_var_name = raw_command[0];
            raw_command++;
            if (is_valid_var(second_var_name) == -1) {
                printf("Undefined complex variable as second parameter\n");
                return;
            }

            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }
            exec_single_comp_args_command(vars, command_name, var_name, second_var_name);
            break;
        
        case MULTIPLE_NUMBER_ARGS:
            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }

            raw_command++; /* Skip comma we just detected */
            
            trim_leading_whitespace(raw_command);

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }
            
            while (!isspace(*raw_command) && *raw_command != ',') {
                first_num_str[i++] = *raw_command;
                raw_command++;
            }

            first_num_str[i] = '\0';
            if (is_valid_num(first_num_str) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            
            first_num = atof(first_num_str);

            trim_leading_whitespace(raw_command);

            if (*raw_command != ',') {
                printf("Missing comma\n");
                return;
            }
            raw_command++; /* Skip comma we just detected */

            trim_leading_whitespace(raw_command);

            if (*raw_command ==  ',') {
                printf("Multiple consecutive commas\n");
                return;
            }

            while (!isspace(*raw_command) && *raw_command != ',' && strlen(raw_command) > 0) {
                second_num_str[j++] = *raw_command;
                raw_command++;
            }

            second_num_str[j] = '\0';
            if (is_valid_num(second_num_str) == -1) {
                printf("Invalid parameter - not a number\n");
                return;
            }
            second_num = atof(second_num_str);

            trim_leading_whitespace(raw_command);

            if (strlen(raw_command) > 0) {
                printf("Extraneous text after command\n");
                return;
            }

            exec_multi_number_args_command(vars, command_name, var_name, first_num, second_num);
            break;
    }
}

int main() {
    char raw_command[MAX_RAW_COMMAND_LEN];
    char command_name[MAX_COMMAND_NAME_LEN] = "";
    
    char *p_command;

    Variables vars;
    vars = init_variables();

    while (1) {
        printf(">>> ");

        p_command = fgets(raw_command, 100000, stdin);
        if (p_command == NULL) { 
            printf("Improper exit... leaving\n");
            return 0;
        }

        prep_raw_command_for_parsing(raw_command);
        printf("%s\n", raw_command);

        get_command_name(raw_command, command_name);
        
        trim_leading_whitespace(raw_command);

        if (!is_valid_command_name(command_name)) {
            continue;
        }

        if (strcmp(command_name, "stop") == 0) {
            if (strlen(raw_command) != 0) {
                printf("Extraneous text after end of command\n");
                continue;
            }
            return 0;
        } else if (strlen(raw_command) == 0) {
            printf("Missing parameter\n");
            continue;
        }

        parse_command_args(command_name, raw_command, &vars);
        continue;

    }
    return 0;
}

