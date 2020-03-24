#include<stdio.h>
#include<math.h>
#define eps 0.000001

double f(double x){
    return (x + cos(pow(x, 0.52) + 2));
}

double dx(double x){
    return (f(x + eps) - f(x))/eps;
}

double absi(double a){
    return a < 0 ? -a : a;
}

double dichotomy(){
    double mid, a = 0.5, b = 1.0;
    while (absi(a - b) > eps){
        mid = (a + b)/2;
        if (f(a) * f(mid) < 0){
            b = mid;
        } else{
            a = mid;
        }
    }
    return mid;
}

double iteration(){
    double x, previous_x = 0, a = 0.5, b = 1.0;
    x = (a + b)/2;
    while(absi(x - previous_x) >= eps){
        previous_x = x;
        x = x - f(x);
    }
    return x;
}

double newton(){
    double x, previous_x = 0, a = 0.5, b = 1.0;
    x = (a + b)/2;
    while(absi(x - previous_x) >= eps){
        previous_x = x;
        x = x - f(x)/dx(x);
    }
    return x;
}


int main(){
    printf("----------------------------------------\n");
    printf("|Дихотомия|Метод итераций|Метод Ньютона|\n");
    printf("|---------|--------------|-------------|\n");
    printf("|  %.4f |    %.4f    |    %.4f   |\n", dichotomy(), iteration(), newton());
    printf("----------------------------------------\n");
}
