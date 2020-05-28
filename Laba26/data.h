#include<stdio.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdlib.h>

typedef struct list {
    int *data;
    int size;
    int top;
} list;

typedef list* listptr;
