#include <stdio.h>
typedef struct Complex {
    float realNum;
    float imaginaryNum;
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
    c->realNum = 0;
    c->imaginaryNum = 0;
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
    c->realNum = realVal;
    c->imaginaryNum = imaginaryVal;
}

void print_comp(Complex *c) {
    printf("%0.2f", c->realNum);
    if(c->imaginaryNum >= 0) {
        printf(" + (%0.2f)i", c->imaginaryNum);
    } else {
        printf(" - (%0.2f)i ", c->imaginaryNum*-1);
    }
    printf("\n");
}

void add_comp(Complex *c1, Complex *c2) {
    Complex result;
    float realSum = c1->realNum + c2->realNum;
    float imaginarySum = c1->imaginaryNum + c2->imaginaryNum;
    read_comp(&result, realSum, imaginarySum);
    print_comp(&result);
}

void sub_comp(Complex *c1, Complex *c2) {
    Complex result;
    float realSum = c1->realNum - c2->realNum;
    float imaginarySum = c1->imaginaryNum - c2->imaginaryNum;
    read_comp(&result, realSum, imaginarySum);
    print_comp(&result);
}

void mult_comp_real(Complex *c1, float r1) {
    Complex result;

    float realVal = r1 * c1->realNum;
    float imaginaryVal = r1 * c1->imaginaryNum;

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void mult_comp_imaginary(Complex *c1, float imaginaryMultiplier) {
    Complex result;

    float realVal = (-1) * imaginaryMultiplier * c1->imaginaryNum;
    float imaginaryVal = imaginaryMultiplier * c1->realNum;

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

void mult_comp_comp(Complex *c1, Complex *c2) {
    Complex result;

    float realVal = (c1->realNum * c2->realNum) - (c1->imaginaryNum * c2->imaginaryNum);
    float imaginaryVal = (c1->realNum * c2->imaginaryNum) + (c1->imaginaryNum * c2->realNum);

    read_comp(&result, realVal, imaginaryVal);
    print_comp(&result);
}

int main() {
    printf("Hello\n");

    Variables v1;

    v1 = init_variables();

    // Set A - 
    Complex * A = access_variable(&v1, 'A');
    read_comp(A, 3.1, 5.3);

    // Set B - 
    Complex * B = access_variable(&v1, 'B');
    read_comp(B, 18.2, 20);

    printf("A = ");
    print_comp(A);
    printf("B = ");
    print_comp(B);
    printf("\n\n");

    printf("A+B = ");
    add_comp(A, B);
    printf("\n");

    printf("A-B = ");
    sub_comp(A, B);
    printf("\n");

    printf("A * 3 = ");
    mult_comp_real(A, 3);
    printf("\n");

    printf("A * 5i = ");
    mult_comp_imaginary(A, 5);
    printf("\n");

    printf("A * B = ");
    mult_comp_comp(A, B);
    printf("\n");
    
    return 0;
}