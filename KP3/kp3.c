#include <math.h>
#include <stdio.h>

const double begin = 0, end = 1;

double epsilon(){
    double eps = 1;
    while (1 + eps > 1) eps /= 2;
    return eps;
}

int main(){
    double x, el, pn, iter = (end-begin)/10, eps, dif;
    long long n, k = 1000000000;
    eps = epsilon();
    printf("Machine epsilon = %.20f\n", eps);
    printf("-------------------------------------------------------------------------\n");
    printf("|  x  |      Polin        |        sh(x)      |    sh(x) - Polin  |  n  |\n");
    printf("|-----|-------------------|-------------------|-------------------|-----|\n");
    
    for (x = begin; x <= end; x += iter){
        pn = el = x;
        n = 1;
        while (fabs(el) > k*eps){
            el = el*x*x / ((2*n)*(2*n+1));
            pn += el;
            ++n;
        }
        dif = sinh(x) - pn;
        printf("| %.1f | %.15f | %.15f | %.15f | %3lld |\n", x, pn, sinh(x), dif, n);
    }
    printf("-------------------------------------------------------------------------\n");
}
