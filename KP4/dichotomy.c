#include<stdio.h>
#include<math.h>

double f(double x){
    return (x + cos(pow(x, 0.52) + 2));
}

double absi(double a){
    return a < 0 ? -a : a;
}
int main(){
    const double eps = 0.0001;
    double a = 0.5, b = 1.0, mid;
    while (absi(a - b) > eps){
        mid = (a + b)/2;
        if (f(a) * f(mid) < 0){
            b = mid;
        } else{
            a = mid;
        }
    }
    printf("%.4f ", mid);
}

