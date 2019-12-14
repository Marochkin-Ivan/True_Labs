#include <stdio.h>

int fib(int n){
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF){
        printf("%d ", fib(n));
    }
    return 0;
}
