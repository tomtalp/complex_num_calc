#include <math.h> 
#include <stdio.h>
#include <string.h>

// #include "foo.h"
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
int is_valid_command(char *command);

int is_valid_command(char *command) {
    for (int i=0; i<AVAILABLE_COMMANDS_COUNT; i++) {
        if (strcmp(COMMANDS[i], command) == 0) {
            return 1;
        }
    }
    return 0;
}

Variables init_variables() {
    Variables v1;
    Complex c1, c2, c3, c4, c5, c6;

    v1.A = c1;
    init_complex(&v1.A);

    v1.B = c2;
    init_complex(&v1.B);

    v1.C = c3;
    init_complex(&v1.C);

    v1.D = c4;
    init_complex(&v1.D);

    v1.E = c5;
    init_complex(&v1.E);

    v1.F = c6;
    init_complex(&v1.F);

    return v1;
}

void init_complex(Complex * c) {
    c->realVal = 0;
    c->imaginaryVal = 0;
}

Complex * access_variable(Variables * v, char varName) {
    switch(varName) {
        case 'A': return &v->A;
        case 'B': return &v->B;
        case 'C': return &v->C;
        case 'D': return &v->D;
        case 'E': return &v->E;
        case 'F': return &v->F;
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
    float absVal = sqrt(pow(c1->realVal, 2) + pow(c1->imaginaryVal, 2));
    printf("%0.2f", absVal);
}

int main() {
    char rawCommand[100000];
    char *p_command, *command;
    
    while (1) {
        // TODO - Do I need this??
        memset(rawCommand, 0, sizeof(rawCommand));
        p_command = NULL;
        command = NULL;

        printf("-> ");
        p_command = fgets(rawCommand, 100000, stdin);
        // fgets(rawCommand, 100000, stdin);
        
        // TODO - THIS WON'T WORK WITH rawCommand == NULL, and I need the additional pointer. WHY?!
        // if (p_command == NULL) {
        if (p_command == NULL) { 
            printf("Improper exit... leaving\n");
            return 0;
        } else if (rawCommand == "STOP") {
            printf("Stopping!\n");
            break;
        } else {
            printf("\nReceived %s\n", rawCommand);
            command = strtok(rawCommand, " "); // Get the first token, which is expected to be the command
            if (!is_valid_command(command)) {
                printf("Undefined command name\n");
                continue;
            }

            printf("Received the command %s\n", command);

            p_command = strtok(NULL, ",");
            printf("Next token is - '%s'\n", p_command);
        }
    }


}

int main2() {
    char rawCommand[100000];
    // char command[MAX_COMMAND_LEN];
    // char tokens[];
    char *token, *command;
    printf("Hey!\n");

    int c;
    int z = 0;
    while (1) {
        c = getchar();

        if (c == EOF) {
            printf("Leaving...\n");
            return 0;
        }

        if (c == '\n') {
            command = strtok(rawCommand, " "); // Get the first token, which is expected to be the command
            printf("Please enter a valid command\n");
            break;
        }
        rawCommand[z] = c;
        z++;
    }

    if (!is_valid_command(command)) {
        printf("Undefined command name\n");
    }
    // printf("command=%s\n", command);
    // command = strtok(NULL, " ");
    // printf("command=%s\n", command);
    // while (token != NULL) {
    //     printf("token=%s\n", token);

    //     int r = is_valid_command(token);
    //     if (r == 0 ) {
    //         
    //         break;
    //     }
    //     token = strtok(NULL, " ");
        
    //     printf("token = %s, command=%s\n", token, rawCommand);
    //     // printf("Token %s validity result - %d\n", command, r);

    // }

    printf("DONE\n");
    return 0;
}

// int main() {
//     printf("Hello\n");

//     Variables v1;

//     v1 = init_variables();

//     // Set A - 
//     Complex * A = access_variable(&v1, 'A');
//     read_comp(A, 3.1, 5.3);

//     // Set B - 
//     Complex * B = access_variable(&v1, 'B');
//     read_comp(B, 18.2, 20);

//     printf("A = ");
//     print_comp(A);
//     printf("B = ");
//     print_comp(B);
//     printf("\n\n");

//     printf("A+B = ");
//     add_comp(A, B);
//     printf("\n");

//     printf("A-B = ");
//     sub_comp(A, B);
//     printf("\n");

//     printf("A * 3 = ");
//     mult_comp_real(A, 3);
//     printf("\n");

//     printf("A * 5i = ");
//     mult_comp_img(A, 5);
//     printf("\n");

//     printf("A * B = ");
//     mult_comp_comp(A, B);
//     printf("\n");

//     printf("|A| = ");
//     abs_comp(A);
//     printf("\n");
    
//     return 0;
// }

