#include <stdio.h>

int main() {
    
    int  mark=1, Fsimbol=1, RightWords=0, Count=0;
    
    char n, Lsimbol;
 
    while( (n=getchar()) != EOF){
        
        Count = Count + 1;
        
        Lsimbol = n;
        
        if (n == ' ' || n == '\n'){
            
            RightWords = RightWords + mark;
            
            Fsimbol=1;
            
            mark=1;
            
            continue;
        }
        
        if(mark == 0) continue;
        
        if (Fsimbol == 1){
            
            if ((n >= 'A' && n<= 'Z') ||
                (n >= 'a' && n<= 'z') ||
                (n=='_')){
                
                Fsimbol=0; continue;
                
            } else {
                mark=0;
                Fsimbol=0;
                continue;
            }
            
        }
        
        if ( !((n >= 'A' && n<= 'Z') ||
            (n >= 'a' && n<= 'z') ||
            (n=='_') ||
            (n >= '0' && n<= '9')) )
            mark=0;
        
    }
    
    if (Lsimbol != ' ' && Lsimbol != '\n') RightWords = RightWords + mark;
        
    if (Count == 0) RightWords=0;
        
    printf("Ansver: %d\n", RightWords);
    
}
