#include <stdio.h>


long long tribonacci(int n);


int main() {
    printf("4th term of Tribonacci: %lld\n", tribonacci(4));
    printf("36th term of Tribonacci: %lld\n", tribonacci(36));

    return 0;
}


long long tribonacci(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1 || n == 2)
        return 1;
    
    long long first = 0, second = 1, third = 1;

    long long prev_third;

    for (int i = 4; i <= n; ++i) {
        prev_third = third;

        third = first + second + third;
        first = second;
        second = prev_third;
    }

    return third;
}