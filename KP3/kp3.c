#include <math.h>
#include <stdio.h>

int main(){
    
    double x, el, polin, eps=1., a=0., b=1., iter=(b-a)/10.;
    
    long long n, k=1000000000;
    
    while (1. + eps > 1.) eps /= 2.;
    
    printf("Machine epsilon = %.20f\n", eps);
    
    printf("-------------------------------------------------------------------------\n");
    
    printf("|  x  |      Polin        |        sh(x)      |    sh(x) - Polin  |  n  |\n");
    
    printf("|-----|-------------------|-------------------|-------------------|-----|\n");
    
    for (x = a; x <= b; x += iter){
        
        polin = el = x;
        
        n = 1;
       
        while (fabs(el) > k*eps){
            
            el = el*x*x / ((2*n)*(2*n+1));
            
            polin += el;
            
            n += 1;
        }
        printf("| %.1f | %.15f | %.15f | %.15f | %3lld |\n", x, polin, sinh(x), fabs(sinh(x)-polin), n);
       
    }
    printf("-------------------------------------------------------------------------\n");
}
