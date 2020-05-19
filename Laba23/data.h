#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} tree;

typedef tree* treeptr;
