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

Variables init_variables();
void read_comp(Complex *c1, float realVal, float imaginaryVal);
void print_comp(Complex *comp);
void init_complex(Complex * c);
int is_valid_command_name(char *command_name);

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

Complex * access_variable(Variables * v, char *varName) {
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
/*
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
    float absVal = sqrt(pow(c1->realVal, 2) + pow(c1->imaginaryVal, 2));
    printf("%0.2f", absVal);
}
*/
void RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    /**i = *(j++);*/
    *i = *j;
    /* i = j */
    j++;
    if(!isspace(*i))
      i++;
  }
  *i = 0;
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

/* void string_parser(char *source, char **tokens) { */
int string_parser(char *source) {    
    char command_name[100] = "";

    printf("Original command - '%s'\n", source);
    trim_leading_whitespace(source);

    get_command_name(source, command_name);
    printf("Command name = '%s', command_size = %ld, remaining command = '%s'\n", command_name, strlen(command_name),source);
    trim_leading_whitespace(source);
    printf("Remaining command after second trim= '%s'\n", source);

    if (!is_valid_command_name(command_name)) {
        return 0;
    }

    if (strcmp(command_name, "stop") == 0) {
        if (strlen(source) != 0) {
            printf("Extraneous text after end of command\n");
            return 0;
        }
        return -1;
    }

    char *token;
    char *tokensArray[10];
    int tokenNum = 0;

    token = strtok(source, ",");

    while (token != NULL) {
        printf( "raw token = '%s'\n", token );
        tokensArray[tokenNum++] = token;

        token = strtok(NULL, ",");
    }
    printf("Done tokenizing\n");
    for(int i=0; i < tokenNum; i++) {
        printf("Token #%d = %s\n", i+1, tokensArray[i]);
    }

    return 0;

}



int main() {
    char rawCommand[1000];
    // char rawCommand[1000] = "read_comp A, B, 2";
    char *p_command;
    int exit_status_code = 0;

    Variables vars;
    vars = init_variables();

    while (1) {
        /* TODO - Do I need this?? */
        // memset(rawCommand, 0, sizeof(rawCommand));
        printf(">>> ");

        p_command = fgets(rawCommand, 100000, stdin);
        /* TODO - THIS WON'T WORK WITH rawCommand == NULL, and I need the additional pointer. WHY?! */
        if (p_command == NULL) { 
            printf("Improper exit... leaving\n");
            return 0;
        }

        strtok(rawCommand, "\n"); // Remove \n from our command
        printf("\nReceived '%s'\n", rawCommand);
        exit_status_code = string_parser(rawCommand);

        if (exit_status_code == -1) {
            return 0;
        }

    }
    return 0;
}

