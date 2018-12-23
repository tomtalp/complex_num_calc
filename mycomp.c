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
    Validate a command name by checking if it has a trailing comma, or if it's in the list of known commands.

    @param command_name (*char) representing the command we're evaluating
    @return (int) representing if command is valid or not (1 = valid, -1 = invalid)
*/
int is_valid_command_name(char *command_name) {
    int i;
    int is_known_command = 0;

    if (command_name[strlen(command_name)-1] == ',') {
        printf("Illegal comma\n");
        return -1;
    }

    for (i=0; i<AVAILABLE_COMMANDS_COUNT; i++) {
        if (strcmp(COMMANDS[i].command_name, command_name) == 0) {
            is_known_command = 1;
            break;
        }
    }

    if (is_known_command == 0) {
        printf("Undefined command name\n");
        return -1;
    }
    
    return 1;
}

/*
    Validate the variable name - check if it's in our variables list (A,B,C,D,E,F)

    @param var_name (char) - The variable name we're evaluating
    @return (int) - A flag that represents if var is variable or not (1 = valid, -1 = invalid)
*/
int is_valid_var(char var_name) {
    int i;

    for (i=0; i < AVAILABLE_VARS_COUNT; i++) {
        if (var_name == *VAR_NAMES[i]) {
            return 1;
        }
    }
    return -1;
}

/*
    Trim all leading whitespaces in the received source string. This function modifies the original string!

    @param source (*char) - The string to be trimmed
*/
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

/*
    Extract the command name from the raw command received from the user.

    @param raw_command (*char) - The raw command we got from the user. This value will lose the command name once we're done!
    @param command_name (*char) - The string that'll receive the command name we just extracted
*/
void get_command_name(char *raw_command, char *command_name) {
    char *raw_command_star = raw_command;

    /* Locate the command name */
    while (*raw_command_star != 0 && !isspace(*raw_command_star)) {
        *command_name = *raw_command_star;
        command_name++;
        raw_command_star++;
    }
    *command_name = '\0';
    
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

    @param raw_command (*char) - The raw command we got from the user.
*/
void prep_raw_command_for_parsing(char *raw_command) {
    strtok(raw_command, "\n");
    trim_leading_whitespace(raw_command);
}

/*
    Check if a string represents a valid float number. We're this on our own and not using `atof` since
    there are certain permutations that aren't detected and parsed properly, so we want to be sure it's 
    actually a float with the current `atof` (also, no `strtof` allowed...)

    @param num_as_str (*char) - A string representing the string we're evaluating.
    @return (int) - A flag representing if our string represents an actual float (1 = true, -1 = false)
*/
/*int is_valid_num(char *num_as_str) {
    char *err_ptr;
    strtof(num_as_str, &err_ptr);
    if (*err_ptr != '\0') {
        return -1;
    }
    return 1;
}*/

int is_valid_num(char *num_as_str) {
    int dot_flag_count = 0;
    if (*num_as_str == '-') {
        num_as_str++;
    }

    while (num_as_str != 0 && strlen(num_as_str) > 0) {
        if (*num_as_str == '.') { /* Allow only one dot in our number */
            if (dot_flag_count > 0) {
                return -1;
            } else {
                dot_flag_count++;
            }
        } else if (!isdigit(*num_as_str)) {
            return -1;
        }

        num_as_str++;
    }
    return 1;
}

/*
    Get the type of legal args for the given command name.

    @param command_name (*char) - The command name we're getting the legal args for
    @return (int) - An int representing the type of legal args for the command
*/
int get_command_legal_args(char *command_name) {
     int i;
     for (i=0; i<AVAILABLE_COMMANDS_COUNT; i++) {
        if (strcmp(COMMANDS[i].command_name, command_name) == 0) {
            return COMMANDS[i].command_legal_args;
        }
    }
    return -1;
}

/*
    Execute a command with multiple number args

    @param vars (*Variables) - A pointer to the variables object, containing all the complex variables in our app
    @param command_name (*char) - The command we're going to execute
    @param var_name (char) - The complex variable name to execute the command with
    @param f1 (float) - The first number in our command
    @param f2 (float) - The second number in our command
*/
void exec_multi_number_args_command(Variables *vars, char *command_name, char var_name, float f1, float f2) {
    Complex *c;
    c = access_variable(vars, var_name);
    if (strcmp(command_name, "read_comp") == 0) {
        read_comp(c, f1, f2);
    }
}

/*
    Execute a command without any args

    @param vars (*Variables) - A pointer to the variables object, containing all the complex variables in our app
    @param command_name (*char) - The command we're going to execute
    @param var_name (char) - The complex variable name to execute the command with
*/
void exec_empty_args_command(Variables *vars, char *command_name, char var_name) {
    Complex *c;
    c = access_variable(vars, var_name);
    if (strcmp(command_name, "print_comp") == 0) {
        print_comp(c);
    } else if (strcmp(command_name, "abs_comp") == 0) {
        abs_comp(c);
    }
}

/*
    Execute a command with a single Complex variable arg

    @param vars (*Variables) - A pointer to the variables object, containing all the complex variables in our app
    @param command_name (*char) - The command we're going to execute
    @param var_name (char) - The complex variable name to execute the command with
    @param var_name_2 (char) - The second complex variable name to use in our command
*/
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

/*
    Execute a command with a single number arg

    @param vars (*Variables) - A pointer to the variables object, containing all the complex variables in our app
    @param command_name (*char) - The command we're going to execute
    @param var_name (char) - The complex variable name to execute the command with
    @param f1 (char) - The number value to use in our command
*/
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
        1. All commands except "stop" must begin with a legal var name (which won't reach this function anyway)
        2. Depending on the command, we evaluate the type of the next args (num, varname etc)
        3. After validating that the command is valid & extracting the command args, we execute it
    
    @param command_name (*char) - The command we're going to execute
    @param raw_command (*char) - The raw command (w/o the command name, which is only the command arguments)
    @param vars (*Variables) - A pointer to the variables object, containing all the complex variables in our app
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
    char command_name[MAX_RAW_COMMAND_LEN] = "";
    
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

        if (is_valid_command_name(command_name) == -1) {
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

