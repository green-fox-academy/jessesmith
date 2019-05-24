#include <stdio.h>

int same(int val1, int val2);

int main() {
    // Create a program which asks for two integers and stores them separatly
    // Create a function which takes two numbers as parameters and
    // returns 1 if they are equal and returns 0 otherwise

    int val1, val2;
    scanf("%d %d", &val1, &val2);

    printf("%d\n", same(val1, val2));

    return 0;
}

int same(int val1, int val2) {
    return (val1 == val2 ? 1 : 0);
}