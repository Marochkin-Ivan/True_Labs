#include<stdio.h>
#include<math.h>
#define eps 0.0001

double f(double x){
    return (x + cos(pow(x, 0.52) + 2));
}

double dx(double x){
    return (f(x + eps) - f(x))/eps;
}

double absi(double a){
    return a < 0 ? -a : a;
}

int main(){
    double a = 0.5, b = 1.0, x, copy_x;
    x = (a + b)/2;
    while(absi(x - copy_x) >= eps){
        copy_x = x;
        x = x - f(x)/dx(x);
    }
    printf("%.4f ", x);
}
