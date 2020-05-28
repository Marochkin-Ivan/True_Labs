#include<stdio.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdlib.h>

typedef struct list {
    int value;
    struct list *next;
    struct list *prev;
} list;

typedef list* listptr;
