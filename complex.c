#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "complex.h"

void init_complex(Complex * c) {
    c->realVal = 0;
    c->imaginaryVal = 0;
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