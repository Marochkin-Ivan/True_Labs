#include <stdio.h>
#define size 64

int main(){
    int matrix[size];
    int n;
    while (scanf("%d", &n) != EOF){
        int min = 0, last_column;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j){
                scanf("%d", &matrix[i*n + j]);
                if (min == 0 || matrix[i*n + j] <= min){
                    min = matrix[i*n + j];
                    last_column = j;
                }
            }
        int mark = 0;
        int column[8];
        int sum_column[8];
        for (int i = 0; i < n; ++i)
            sum_column[i] = 0;
        for (int j = 0; j < n; ++j){
            for (int i = 0; i < n; ++i){
                column[i] = matrix[i*n + j];
                if (matrix[i*n + j] == min)
                    mark = 1;
            }
            if (mark == 1)
                for (int i = 0; i < n; ++i)
                    sum_column[i] += column[i];
            mark = 0;
        }
        for (int i = 0; i < n; ++i)
            matrix[i*n + last_column] = sum_column[i];
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j)
                printf("%d  ", matrix[i*n + j]);
            printf("\n");
        }
        printf("\n");
    }
}
