#include<stdio.h>
#include<math.h>
#define eps 0.0001

double f(double x){
    return (x + cos(pow(x, 0.52) + 2));
}

double absi(double a){
    return a < 0 ? -a : a;
}

int main(){
    double a = 0.5, b = 1.0, x, previous_x;
    x = (a + b)/2;
    while(absi(x - previous_x) >= eps){
        previous_x = x;
        x = x - f(x);
    }
    printf("%.4f ", x);
}
