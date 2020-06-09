#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    char value;
    struct Node *next;
    struct Node *prev;
} tNode;
