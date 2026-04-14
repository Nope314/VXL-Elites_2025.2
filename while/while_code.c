#include <stdio.h>

int main() {

    int index_1 = 0;
    int index_2 = 100;
    int index_3 = 0;
    int test_do = -1;
    int index_4 = 0;
    int test_infinite = 1;

    //Test case 1: Standard
    while(index_1 < 5) {
        printf("%d ", index_1);
        index_1 = index_1 + 1;
    }
    printf("\n");

    //Test case 2: always 0 condition
    while(0) {
        printf("%d \n", index_2);
    }

    while(index_2) {
        printf("%d \n", index_2);
    }

    //Test case 3: while vs do-while
    do {
        printf("%d ", index_3);
        index_3 = index_3 + 1;
    } while(index_3 < 5);
    printf("\n");

    do {
        printf("%d ",test_do);
    } while(0);
    printf("\n");

    //Test case 4: Infinite loop
/*
    while(1) {
        index_4 = index_4 + 1;
        //printf("$d ", index_4);
    }
    printf("\n");
*/
    while(test_infinite) {
        index_4 = index_4 + 1;
        //printf("$d ", index_4);
    }
    return 0;
}