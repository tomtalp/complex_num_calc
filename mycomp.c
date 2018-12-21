#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define AVAILABLE_COMMANDS_COUNT 9
#define MAX_COMMAND_LEN 14

typedef struct Complex {
    float realVal;
    float imaginaryVal;
} Complex;

typedef struct Variables {
    Complex A;
    Complex B;
    Complex C;
    Complex D;
    Complex E;
    Complex F;
} Variables;

Variables init_variables();
void read_comp(Complex *c1, float realVal, float imaginaryVal);
void print_comp(Complex *comp);
void add_comp(Complex *c1, Complex *c2);
void mult_comp_real(Complex *c1, float r1);
void mult_comp_img(Complex *c1, float imaginaryMultiplier);
void mult_comp_comp(Complex *c1, Complex *c2);
void abs_comp(Complex *c1);
void init_complex(Complex * c);
int is_valid_command_name(char *command_name);

char *READ_COMP_LEGAL_ARGS[3] = {"VAR", "NUM", "NUM"};
char *PRINT_COMP_LEGAL_ARGS[1] = {"VAR"};

// struct {
//     char *command_name;
//     void (*command_func)();
//     char **command_legal_args;
// } COMMANDS[] = {
//     {"read_comp", read_comp, READ_COMP_LEGAL_ARGS},
//     {"print_comp", print_comp, PRINT_COMP_LEGAL_ARGS},
// };

char *COMMANDS[] = {
    "read_comp",
    "print_comp",
    "add_comp",
    "sub_comp",
    "mult_comp_real",
    "mult_comp_imp",
    "mult_comp_comp",
    "abs_comp",
    "stop"
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
        if (strcmp(COMMANDS[i], command_name) == 0) {
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

int is_valid_var(char *command) {
    return strlen(command) == 1;
}

Variables init_variables() {
    Variables v1;
    Complex c1, c2, c3, c4, c5, c6;

    init_complex(&c1);
    v1.A = c1;
    
    init_complex(&c2);
    v1.B = c2;

    init_complex(&c3);
    v1.C = c3;

    init_complex(&c4);
    v1.D = c4;

    init_complex(&c5);
    v1.E = c5;

    init_complex(&c6);
    v1.F = c6;

    return v1;
}

void init_complex(Complex * c) {
    c->realVal = 0;
    c->imaginaryVal = 0;
}

Complex *access_variable(Variables * v, char *varName) {
    if (strcmp(varName, "A") == 0) {
        return &v->A;
    } else if (strcmp(varName, "B") == 0) {
        return &v->B;
    } else if (strcmp(varName, "C") == 0) {
        return &v->C;
    } else if (strcmp(varName, "D") == 0) {
        return &v->D;
    } else if (strcmp(varName, "E") == 0) {
        return &v->E;
    } else if (strcmp(varName, "F") == 0) {
        return &v->F;
    }
    return NULL;
}

void read_comp(Complex *c, float realVal, float imaginaryVal) {
    c->realVal = realVal;
    c->imaginaryVal = imaginaryVal;
}

void print_comp(Complex *c) {
    printf("%0.2f", c->realVal);
    if(c->imaginaryVal >= 0) {
        printf(" + (%0.2f)i", c->imaginaryVal);
    } else {
        printf(" - (%0.2f)i ", c->imaginaryVal*-1);
    }
    printf("\n");
}

void add_comp(Complex *c1, Complex *c2) {
    Complex result;
    float realVal = c1->realVal + c2->realVal;
    float imaginaryVal = c1->imaginaryVal + c2->imaginaryVal;
    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void sub_comp(Complex *c1, Complex *c2) {
    Complex result;
    float realVal = c1->realVal - c2->realVal;
    float imaginaryVal = c1->imaginaryVal - c2->imaginaryVal;
    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void mult_comp_real(Complex *c1, float r1) {
    Complex result;

    float realVal = r1 * c1->realVal;
    float imaginaryVal = r1 * c1->imaginaryVal;

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void mult_comp_img(Complex *c1, float imaginaryMultiplier) {
    Complex result;

    float realVal = (-1) * imaginaryMultiplier * c1->imaginaryVal;
    float imaginaryVal = imaginaryMultiplier * c1->realVal;

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void mult_comp_comp(Complex *c1, Complex *c2) {
    Complex result;

    float realVal = (c1->realVal * c2->realVal) - (c1->imaginaryVal * c2->imaginaryVal);
    float imaginaryVal = (c1->realVal * c2->imaginaryVal) + (c1->imaginaryVal * c2->realVal);

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void abs_comp(Complex *c1) {
    // float absVal = sqrt(pow(c1->realVal, 2) + pow(c1->imaginaryVal, 2));
    // printf("%0.2f", absVal);
    printf("TODO\n");
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

    /* Locate the command name */
    while (*sourceStart != 0 && !isspace(*sourceStart)) {
        *command_name = *sourceStart;
        command_name++;
        sourceStart++;        
    }
    *command_name = '\0'; /* TODO - Do I need this? */

    /* Remove the command name from source */
    while (*sourceStart != 0) {
        *source = *sourceStart;
        source++;
        sourceStart++; 
    }
    *source = '\0';
}

// int validate_command_args(char *command_name, char **args_array) {
//     printf("Validating the command %s\n", command_name);
//     Complex result;
//     float realVal = 100;
//     float imaginaryVal = 150;
//     read_comp(&result, realVal, imaginaryVal);
//     print_comp(&result);
//     COMMANDS[1].command_func(&result);
// }

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

void exec_command(char *command_name, char **args, Variables *vars) {
    if (strcmp(command_name, "read_comp") == 0) {
        char *varName = args[0];
        float f1 = atof(args[1]);
        float f2 = atof(args[2]);
        Complex *c1 = access_variable(vars, varName);
        read_comp(c1, f1, f2);
    } else if (strcmp(command_name, "print_comp") == 0) {
        char *varName = args[0];
        Complex *c1 = access_variable(vars, varName);
        print_comp(c1);
    } else if (strcmp(command_name, "add_comp") == 0) {
        char *varName1 = args[0];
        char *varName2 = args[0];
        Complex *c1 = access_variable(vars, varName1);
        Complex *c2 = access_variable(vars, varName2);
        add_comp(c1, c2);
    } else if (strcmp(command_name, "sub_comp") == 0) {
        char *varName1 = args[0];
        char *varName2 = args[0];
        Complex *c1 = access_variable(vars, varName1);
        Complex *c2 = access_variable(vars, varName2);
        sub_comp(c1, c2);
    } else if (strcmp(command_name, "mult_comp_real") == 0) {
        char *varName1 = args[0];
        float f1 = atof(args[1]);
        Complex *c1 = access_variable(vars, varName1);
        mult_comp_real(c1, f1);        
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        char *varName1 = args[0];
        float f1 = atof(args[1]);
        Complex *c1 = access_variable(vars, varName1);
        mult_comp_img(c1, f1);        
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        char *varName1 = args[0];
        char *varName2 = args[0];
        Complex *c1 = access_variable(vars, varName1);
        Complex *c2 = access_variable(vars, varName2);
        mult_comp_comp(c1, c2);
    } else if (strcmp(command_name, "abs_comp") == 0) {
        char *varName = args[0];
        Complex *c1 = access_variable(vars, varName);
        abs_comp(c1);
    }
}


int main() {
    // char raw_command[1000] = "  read_comp A, B,   2      s   ";
    char raw_command[1000];
    char command_name[100] = "";
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

        // printf("raw_command after prep_for_parsing = '%s'\n", raw_command);

        get_command_name(raw_command, command_name);

        // Remove any leftover whitespaces between command name & args
        trim_leading_whitespace(raw_command);
        // printf("Command name = '%s', command_size = %ld, remaining command = '%s'\n", command_name, strlen(command_name),raw_command);

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

        arg_size = get_command_args(raw_command, command_args);
        // printf("Received %d args!\n", arg_size);
        // for (int i=0; i < arg_size; i++) {
        //     printf("Arg #%d = '%s'\n", i, command_args[i]);
        // }

        exec_command(command_name, command_args, &vars);

    }
    return 0;
}

