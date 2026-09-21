#include <stdio.h>

/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
    // TODO: implement sum with a for loop
    int sum = 0;
    for (int i = 1; i <= n; i = i + 1) {
        sum = sum + i;
    }
    return sum;
}

int main(void) {
    int n;

    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input\n");
        return 1;
    }

    // TODO: validate input, call function, and print result
    if (n < 1) {
        printf("Error: number is less than 1\n");
    } else {
        printf("%d\n", sum_to_n(n));
    }

    return 0;
}