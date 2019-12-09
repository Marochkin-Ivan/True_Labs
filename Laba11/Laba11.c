#include <stdio.h>

int main() {
    
    int  mark=1, Fsimbol=1, RightWords=0, Count=0;
    
    char n;
 
    while((n=getchar())!=EOF){
        
        Count=Count+1;
        
        if (n==' '){
            
            RightWords=RightWords+mark;
            
            Fsimbol=1;
            
            mark=1;
            
            continue;
        }
        
        if (Fsimbol==1){
            
            if ((n >= 'A' && n<= 'Z') ||
                (n >= 'a' && n<= 'z') ||
                (n=='_')){
                
                Fsimbol=0;
                
            } else {
                mark=0;
                Fsimbol=0;
                
                
            }
        }
        
        
        
        if ((n >= 'A' && n<= 'Z') ||
            (n >= 'a' && n<= 'z') ||
            (n=='_') ||
            (n >= '0' && n<= '9')){
        
        } else {mark=0;}
        
    } 
    
    
    RightWords=RightWords+mark;
    
    if (Count==0){
        
        RightWords=0;
        
    }
    
    printf("Ansver: %d\n", RightWords);
    
}
