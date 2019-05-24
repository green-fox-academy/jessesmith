#include <stdio.h>
#include <math.h>

int is_prime(int test);

int main() {
    int test_number;
    scanf("%d", &test_number);

    printf("%s\n", is_prime(test_number) ? "Is prime!" : "Is not prime.");
    return 0;
}

int is_prime(int test) {
    int max = sqrt(test);
    for(int i = 2; i <= max; i++){
        int mod = test % i;
        if(mod == 0){
            return 0;
        }
    }
    return 1;
}