#include <stdio.h>

/*
    Task:
    Write a function `int is_prime(int n)` that returns 1 if n is prime,
    0 otherwise.

    In main():
      - Ask user for an integer n (>= 2)
      - If invalid, print an error
      - Otherwise, print all prime numbers up to n
*/

int is_prime(int n) {
    // TODO: check if n is prime using loop up to sqrt(n)
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i * i <= n; i = i + 1) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int n;

    printf("Enter an integer n (>= 2): ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input\n");
        return 1;
    }

    // TODO: validate input and print all primes up to n
    if (n < 2) {
        printf("Error: invalid number\n");
    } else {
        for (int i = 2; i <= n; i = i + 1) {
            if (is_prime(i) == 1) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}