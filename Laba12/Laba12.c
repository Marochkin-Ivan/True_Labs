#include <stdio.h>

int sign(long long x){
    return x >= 0 ? 1 : -1;
}

long long cc2(long long x, long long* all_1,long long* count){
    long long y = 0, count_y = 1; *all_1 = 0;
    *count = 0;
    if (x < 0) x = -x;
    while(x > 0){
        y = (x%2)*count_y + y;
        count_y *= 10;
        x = x/2;
        *all_1 = *all_1*10 + 1;
        ++(*count);
    }
    return y;
}

int main() {
    long long x, revers, all_1, count, d;
    scanf("%lld", &x);
    if (sign(x) == 1){
        revers = cc2(x, &all_1, &count);
        printf("0,");
        d = count/8 * 8 + 7 - count;
        for(int i = 0; i < d; ++i){
            printf("0");
        }
        printf("%lld\n",revers);
    } else {
        revers = cc2(x, &all_1, &count);
        printf("1,");
        d = count/8 * 8 + 7 - count;
        for(int i = 0; i < d; ++i){
            printf("0");
        }
        printf("%lld\n",all_1 - revers);
    }
}
