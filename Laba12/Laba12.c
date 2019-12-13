#include <stdio.h>

int sign(long long x){
    
    return x>=0 ? 1 : -1;
    
}


long long cc2(long long x, long long* supernumber,long long* kolvo){
    
    long long y=0, count_y=1; *supernumber=0;
    
    *kolvo = 0;
    
    if (x<0) x=-x;
    
    while(x > 0){
        
        y = (x%2)*count_y + y;
        
        count_y *= 10;
        
        x = x/2;
        
        *supernumber = *supernumber*10 + 1;
        
        ++(*kolvo);
    }
    
    return y;
}


int main() {
    
    long long x, a, b, c;

    scanf("%lld", &x);
    
    if (sign(x)==1){
        
        a = cc2(x, &b, &c);
        
        printf("0,");
        
        for(int i = 0; i < c/8 * 8 + 7 - c; ++i){
            printf("0");
        }
        printf("%lld\n",a);
        
    } else {
        
        a = cc2(x, &b, &c);
        
        printf("1,");
        
        for(int i = 0; i < c/8 * 8 + 8 - c; ++i){
            printf("0");
        }
        printf("%lld\n",b-a);
        
    }
    
}
