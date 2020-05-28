#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
} tree;

typedef tree* treeptr;

typedef struct depth {
    int max;
    int cell;
} depth;

typedef depth* depthptr;
