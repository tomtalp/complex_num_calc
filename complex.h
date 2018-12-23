#ifndef COMPLEX_H
#define COMPLEX_H

/*
A type representing a complex variable
*/
typedef struct Complex {
    float realVal;
    float imaginaryVal;
} Complex;

/*
A type representing the complex variables in our program - 6 Complex variables
*/
typedef struct Variables {
    Complex A;
    Complex B;
    Complex C;
    Complex D;
    Complex E;
    Complex F;
} Variables;

/*
    Initialize a complex number with zero values

    @param (*Complex) - A pointer to the complex number we're going to initialize
*/ 
void init_complex(Complex * c);

/*
    Initialize a Variables object with all the 6 variables in our program (A, B, C, D, E, F) all set to zero.

    @return (Variables) - A Variables object, after the initialization
*/
Variables init_variables();

/*
    Access the complex variable in our Variables object

    @param (*Variables) - The variables object to retrieve the variable from
    @param (char) - The name of the variable to retrieve
    @return (*Complex) - A pointer to the complex variable in our Variables ojbect
*/
Complex *access_variable(Variables * v, char varName);

/*
    Read values into a complex variable

    @param (*Complex) - A pointer to the complex variable we want to insert values into
    @param realVal (float) - The `real` value of the complex number
    @param imaginaryVal (float) - The `imaginary` value of the complex number
*/
void read_comp(Complex *c1, float realVal, float imaginaryVal);

/*
    Print a complex variable, in the following format - `5.00 + (3.00)i`

    @param (*Complex) - A pointer to the complex variable we want to print
*/
void print_comp(Complex *comp);

/*
    Add two complex variables, and print the result

    @param (*Complex) - A pointer to the first complex variable we want to add
    @param (*Complex) - A pointer to the second complex variable we want to add
*/
void add_comp(Complex *c1, Complex *c2);

/*
    Subtract two complex variables, and print the result (Subtract c2 from c1, that is `c1 - c2`)

    @param (*Complex) - A pointer to the first complex variable we want to subtract
    @param (*Complex) - A pointer to the second complex variable we want to subtract
*/
void sub_comp(Complex *c1, Complex *c2);

/*
    Multiply a complex variable with a real number, and print the result

    @param (*Complex) - A pointer to the complex variable we want to multiply
    @param (float) - A float representing the real number we'll be using to multiply
*/
void mult_comp_real(Complex *c1, float realMultiplier);

/*
    Multiply a complex variable with an imaginary number, and print the result

    @param (*Complex) - A pointer to the complex variable we want to multiply
    @param (float) - A float representing the imaginary number we'll be using to multiply
*/
void mult_comp_img(Complex *c1, float imaginaryMultiplier);

/*
    Multiply a complex variable with another complex number, and print the result

    @param (*Complex) - A pointer to the complex variable we want to multiply
    @param (*Complex) - A pointer to the second complex variable we want to multiply
*/
void mult_comp_comp(Complex *c1, Complex *c2);

/*
    Print the absolute value of a complex number

    @param (*Complex) - A pointer to the complex variable we want to print
*/
void abs_comp(Complex *c1);

#endif