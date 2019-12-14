#include<stdio.h>

int min(int a, int b){
    return a < b ? a : b;
}

int max(int a, int b){
    return a > b ? a : b;
}

int sign(int a){
    return a > 0 ? 1 :
    a < 0 ? -1 : 0;
}

int absi(int a){
    return a < 0 ? -a : a;
}

int mod(int a, int b){
    return a > 0 ? a - b*(a/b) :
    b > 0 ? a - b*(a/b - 1) : a - b*(a/b + 1);
}

int main(){
    int i=22, j=10, l=10, k=0;
    while(k < 51){
        ++k;
        
        i = min(mod(l, 5), mod(i*k, 5)) + j + k/3;
        j = max(-3*i, 2*j)/5 - absi(j - l);
        l = j + mod(l, 7) + mod(k*sign(i), 10);
        
        if ((i >= 5) && (i <= 15) && (j <= -5) && (j >= -15)) break;
    }
    
    k>50 ? printf("Нет попадания в заданную область за 50 шагов\n") :
    printf("Есть попадание в заданную область на %d шаге\nКоординаты точки: i=%d, j=%d\nЗначение динамического параметра движения: l=%d\n", k,i,j,l);
}
