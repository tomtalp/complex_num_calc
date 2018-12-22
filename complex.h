#ifndef COMPLEX_H
#define COMPLEX_H

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

void init_complex(Complex * c);
Variables init_variables();
void read_comp(Complex *c1, float realVal, float imaginaryVal);
void print_comp(Complex *comp);
void add_comp(Complex *c1, Complex *c2);
void mult_comp_real(Complex *c1, float r1);
void mult_comp_img(Complex *c1, float imaginaryMultiplier);
void mult_comp_comp(Complex *c1, Complex *c2);
void abs_comp(Complex *c1);

#endif