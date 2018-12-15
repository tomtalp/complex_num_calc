#include <math.h> 
#include <stdio.h>
#include "foo.h"


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
void init_complex(Complex * c);

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