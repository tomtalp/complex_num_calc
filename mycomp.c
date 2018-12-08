#include <stdio.h>
typedef struct Complex {
    int realNum;
    int imaginaryNum;
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
void read_comp(Complex *c1, int realVal, int imaginaryVal);
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

void read_comp(Complex *c, int realVal, int imaginaryVal) {
    c->realNum = realVal;
    c->imaginaryNum = imaginaryVal;
}

void print_comp(Complex *c) {
    printf("%d", c->realNum);
    if(c->imaginaryNum >= 0) {
        printf(" + (%d)i", c->imaginaryNum);
    } else {
        printf(" - (%d)i ", c->imaginaryNum*-1);
    }
    printf("\n");
}

int main() {
    printf("Hello\n");

    Variables v1;

    v1 = init_variables();

    // Set A - 
    Complex * A = access_variable(&v1, 'A');
    read_comp(A, 3, 5);

    // Set B - 
    Complex * B = access_variable(&v1, 'B');
    read_comp(B, 18, 20);

    printf("A = ");
    print_comp(A);
    printf("B = ");
    print_comp(B);

    return 0;
}