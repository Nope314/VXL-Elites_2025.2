#include <stdio.h>

void foo(int x) {
    printf("%d \n", x);
};

void foo_alternative(float x) {
    printf("%f \n", x);
}

void foo_ptr(int *ptr) {
    printf("%d\n", *ptr);
}

int foo_return_int() {
    return 10;
}

int* foo_return_local() {
    int x = 10;
    return &x;
}

int main() {
    
    //Test case 1 : Standard
    int tc1_i = 1; 
    printf("%s","Test Case 1: ");
    foo(tc1_i);

    //Test case 2 : Using pointer as input.
    int tc2_i = 3;
    int *tc2_ptr = &tc2_i;
    printf("%s","Test Case 2: ");
    foo_ptr(tc2_ptr);

    //Test case 3 : Return variable
    int tc3_i;
    printf("%s","Test Case 3: ");
    tc3_i = foo_return_int();
    printf("%d \n", tc3_i);

    //Test case 4 : Pass float into function that expects integer.
    float tc4_f = 3.5;
    printf("%s","Test Case 4: ");
    foo(tc4_f);

    //Test case 5 : Pass int into function that expects float.
    int tc5_i = 1;
    printf("%s","Test Case 5: ");
    foo_alternative(tc5_i);

    //Test case 6 : Return local variable.
    int *tc6_ptr;
    printf("%s","Test Case 6: ");
    tc6_ptr = foo_return_local();
    printf("%d \n", *tc6_ptr);

    return 0;
}