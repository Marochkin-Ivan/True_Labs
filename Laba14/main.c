#include <stdio.h>
#define size 64
#define write printf("%d ", m.a[i])

struct matrica{
    int a[size];
    int n;
};

int get_matrica(struct matrica* a){
    if (scanf("%d", &a->n) == EOF)
        return 0;
    int real_size = a->n * a->n;
    for (int i = 0; i < real_size; ++i)
        scanf("%d", &a->a[i]);
    return 1;
}

int main() {
    struct matrica m;
    int i;
    while (get_matrica(&m)){
        i = m.n - 1;
        while (i != 0){
            write;
            i += m.n;
            while (i >= m.n){
                write;
                i -= m.n + 1;
            }
            if (i == 0) break;
            write;
            --i;
            while (i % m.n != m.n - 1){
                if (i == 0) break;
                write;
                i += m.n + 1;
            }
        }
        if (m.n % 2 == 0){
            write;
            i += m.n;
        }
        int d = m.n * (m.n - 1);
        while (i != d){
            while (i < d){
                write;
                i += m.n + 1;
            }
            write;
            --i;
            while (i % m.n != 0){
                write;
                i -= m.n + 1;
            }
            write;
            i += m.n;
        }
        write;
        printf("\n");
    }
}
