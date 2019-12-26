#include<stdio.h>

int is_sep(int a){
    return (a == ' ' || a == '\n' || a == '\t' || a == ',' || a == '.' || a == EOF);
}

int number_of_bytes(int first){
    for (int n = 1; n < 8; n++)
        if ( first >> (7-n) == ((1 << (n+1)) - 2))
            return n;
    return -1;
}

int read_code_point(){
    int first = getchar();
    if (first < 128)
        return first;
    int n = number_of_bytes(first);
    int res = first & ((1 << (8-n)) - 1);
    for (int i = 1; i < n; i++){
        int next = getchar();
        res = res << 6 | (next & 0x3F);
    }
    return res;
}

int to_code_point(char s[]){
    unsigned int first = (unsigned char)s[0];
    if (first < 128)
        return first;
    int n = number_of_bytes(first);
    unsigned int res = first & ((1 << (8-n)) - 1);
    for (int i = 1; i < n; i++){
        unsigned int next = (unsigned char)s[i];
        res = res << 6 | (next & 0x3F);
    }
    return res;
}

int is_in_set(int cd, unsigned long long set){
    if (cd == to_code_point("Ë")){
        return (set & (1llu << (to_code_point("ё") - to_code_point("а")))) != 0;
    }
    if (to_code_point("А") <= cd && cd <= to_code_point("Я")){
        return (set & (1llu << (cd - to_code_point("А")))) != 0;
    }
    return (set & (1llu << (cd - to_code_point("а")))) != 0;
}

int is_in_set2(int cd, unsigned long long set){
    if (cd == to_code_point("ё"))
        return (set & (1llu << (to_code_point("ё") - to_code_point("а")))) != 0;
    
    if (cd == to_code_point("е"))
        return (set & (1llu << (to_code_point("е") - to_code_point("а")))) != 0;
    
    if (cd == to_code_point("ю"))
        return (set & (1llu << (to_code_point("ю") - to_code_point("а")))) != 0;
    
    if (cd == to_code_point("я"))
        return (set & (1llu << (to_code_point("я") - to_code_point("а")))) != 0;
    
    if (cd == to_code_point("Е"))
        return (set & (1llu << (to_code_point("Е") - to_code_point("А")))) != 0;
    
    if (cd == to_code_point("Ю"))
        return (set & (1llu << (to_code_point("Ю") - to_code_point("А")))) != 0;
    
    if (cd == to_code_point("Я"))
        return (set & (1llu << (to_code_point("Я") - to_code_point("А")))) != 0;
    
    if (cd == to_code_point("Ё"))
        return (set & (1llu << (to_code_point("ё") - to_code_point("а")))) != 0;
    
    return 0;

}

int main(){
    int mark = 0, state = 0, code_p;
    unsigned long long vowels, correct_vowels;
    char letters1[10][2] = {"а","е","и","о","у","ы","э","ю","я","ё"};
    char letters2[4][2] = {"е","ю","я","ё"};
    for (int i = 0; i < 10; i++){
        vowels = vowels | 1llu << ( to_code_point(letters1[i]) - to_code_point("а") );
    }
    for (int i = 0; i < 4; i++){
        correct_vowels = correct_vowels | 1llu << ( to_code_point(letters2[i]) - to_code_point("а") );
    }
    while (code_p != EOF){
        code_p = read_code_point();
        switch (state){
            case 0:
                if (is_sep(code_p))
                    state = 0;
                if (is_in_set(code_p,vowels))
                    state = 2;
                if (!(is_sep(code_p)))
                    state = 1;
            case 1:
                if (is_in_set(code_p,vowels))
                    state = 2;
                if (is_sep(code_p))
                    state = 0;
                if (!(is_in_set(code_p,vowels))){
                    state = 1;
                    break;
                }
            case 2:
                if (is_in_set2(code_p,correct_vowels)){
                    state = 1;
                    mark = 1;
                    break;
                } else {
                    state = 3;
                    mark = 0;
                  }
            case 3:
                if (!(is_sep(code_p)))
                    state = 3;
                if (is_sep(code_p))
                    state = 0;
        }
        if (is_sep(code_p) && mark == 1)
            break;
    }
    mark == 1 ? printf("Есть слова, содержащие гласные только 2-го рода\n") :
                printf("Нет слов, содержащих гласные только 2-го рода\n");
}
