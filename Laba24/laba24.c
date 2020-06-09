#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef struct tree {
	char key;
	struct tree *left;
	struct tree *right;
} node;

int prior(char c) {
	switch (c) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^': return 3;
	}
	return 10;
};

node *maketree(char expr[], int first, int last) {
	int minpr, i, k, prt, sk = 0;
	node *t = NULL;
	t = (node*)malloc(sizeof(node));
	if (first == last) {
		t->key = expr[first];
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	minpr = 10;
	for (i = first; i <= last; i++) {
		if (expr[i] == '(') { sk++; continue; }
		if (expr[i] == ')') { sk--; continue; }
		if (sk > 0) continue;
		prt = prior(expr[i]);
		if (prt <= minpr) {
			minpr = prt;
			k = i;
		}
	}
	if (minpr == 10 && expr[first] == '('&&expr[last] == ')') {
		free(t);
		return maketree(expr, first + 1, last - 1);
	}
	t->key = expr[k];
	t->left = maketree(expr, first, k - 1);
	t->right = maketree(expr, k + 1, last);
	return t;
}

void print_tree(node *root, int h) {
	if (root != NULL) {
		print_tree(root->right, h + 3);
		printf("-%*c%c\n", h, ' ', root->key);
		print_tree(root->left, h + 3);
	}
}

void print_expression(node *root) {
	int p;
	if (!root) return;
	p = 0; if (root->left != NULL && prior(root->key) > prior(root->left->key)) {
		p = 1; printf("(");
	}
	print_expression(root->left); if (p == 1) printf(")");
	printf("%c", root->key);
	p = 0; if (root->right != NULL && (prior(root->key) > prior(root->right->key) || (prior(root->key) == prior(root->right->key) && root->key == '/'))) {
		p = 1; printf("(");
	}
	print_expression(root->right); if (p == 1) printf(")");
}

void task(node *root) {
	node *tmp = NULL;
    char letter;
    int coeff;

    if (root->left != NULL && root->left->left != NULL && root->left->right != NULL)
        task(root->left);
    if (root->right != NULL && root->right->left != NULL && root->right->right != NULL)
        task(root->right);
    
    if (root->key == '+' && root->right->key == '*' && root->left->key == '*'){
        if (root->left->right->key == root->right->right->key){
            letter = root->left->right->key;
            coeff = (root->left->left->key - 48) + (root->right->left->key - 48);
            root->left->left = NULL;
            root->left->right = NULL;
            root->right->left = NULL;
            root->right->right = NULL;
            free(root->left->left);
            free(root->left->right);
            free(root->right->left);
            free(root->right->right);
            root->left->key = coeff + 48;
            root->right->key = letter;
            root->key = '*';
        }
    }
    if (root->key == '-' && root->right->key == '*' && root->left->key == '*'){
        if (root->left->right->key == root->right->right->key){
            letter = root->left->right->key;
            if (root->left->left->key > root->right->left->key){
                coeff = (root->left->left->key - 48) - (root->right->left->key - 48);
            }
            else{
                printf("%s\n", "Сорри, но отрицательные числа я не умею считать(((");
                return;
            }
            root->left->left = NULL;
            root->left->right = NULL;
            root->right->left = NULL;
            root->right->right = NULL;
            free(root->left->left);
            free(root->left->right);
            free(root->right->left);
            free(root->right->right);
            root->left->key = coeff + 48;
            root->right->key = letter;
            root->key = '*';
        }
    }
    if (root->key == '+' && root->left->key == '*' && root->right->key >= 'a' && root->right->key <= 'z'){
        if (root->left->right->key == root->right->key){
            coeff = (root->left->left->key - 48) + 1;
            root->left->left = NULL;
            root->left->right = NULL;
            free(root->left->left);
            free(root->left->right);
            root->left->key = coeff + 48;
            root->key = '*';
        }
    }
    if (root->key == '+' && root->right->key == '*' && root->left->key >= 'a' && root->left->key <= 'z'){
        if (root->right->right->key == root->left->key){
            letter = root->left->key;
            coeff = (root->right->left->key - 48) + 1;
            root->right->left = NULL;
            root->right->right = NULL;
            free(root->right->left);
            free(root->right->right);
            root->right->key = letter;
            root->left->key = coeff + 48;
            root->key = '*';
        }
    }
    if (root->key == '-' && root->left->key == '*' && root->right->key >= 'a' && root->right->key <= 'z'){
        if (root->left->right->key == root->right->key){
            letter = root->right->key;
            coeff = (root->left->left->key - 48) - 1;
            if (coeff > 1){
                root->left->left = NULL;
                root->left->right = NULL;
                free(root->left->left);
                free(root->left->right);
                root->left->key = coeff + 48;
                root->key = '*';
            }
            else{
                root->left->left = NULL;
                root->left->right = NULL;
                free(root->left->left);
                free(root->left->right);
                root->left = NULL;
                root->right = NULL;
                free(root->left);
                free(root->right);
                root->key = letter;
            }
        }
    }
    if (root->key == '-' && root->right->key == '*' && root->left->key >= 'a' && root->left->key <= 'z'){
        if (root->right->right->key == root->left->key){
            printf("%s\n", "Сорри, но отрицательные числа я не умею считать(((");
            return;
        }
    }
    if (root->key == '+' && root->left->key >= 'a' && root->left->key <= 'z' && root->right->key >= 'a' && root->right->key <= 'z'){
        if (root->left->key == root->right->key){
            root->left->key = 50;
            root->key = '*';
        }
    }
    if (root->key == '-' && root->left->key >= 'a' && root->left->key <= 'z' && root->right->key >= 'a' && root->right->key <= 'z'){
        if (root->left->key == root->right->key){
            root->left = NULL;
            root->right = NULL;
            free(root->left);
            free(root->right);
            root = NULL;
            free(root);
        }
    }
    if (root->key == '+' && root->right->key == '*' && root->left->key == '+' && root->left->right->key == '*'){
        if (root->left->right->right->key == root->right->right->key){
            coeff = (root->left->right->left->key - 48) + (root->right->left->key - 48);
            root->left->right->left = NULL;
            root->left->right->right = NULL;
            free(root->left->right->left);
            free(root->left->right->right);
            root->left->right = NULL;
            free(root->left->right);
            root->left = root->left->left;
            root->right->left->key = coeff + 48;
        }
    }
    if (root->key == '+' && root->right->key == '*' && root->left->key == '-' && root->left->right->key == '*'){
        if (root->left->right->right->key == root->right->right->key){
            if (root->right->left->key < root->left->right->left->key){
                printf("%s\n", "Сорри, но отрицательные числа я не умею считать(((");
                return;
            }
            else {
                coeff = (root->right->left->key - 48) - (root->left->right->left->key - 48);
                root->left->right->left = NULL;
                root->left->right->right = NULL;
                free(root->left->right->left);
                free(root->left->right->right);
                root->left->right = NULL;
                free(root->left->right);
                root->left = root->left->left;
                root->right->left->key = coeff + 48;
            }
        }
    }
    if (root->key == '+' && root->right->key >= 'a' && root->right->key <= 'z' && root->left->key == '+' && root->left->right->key == '*'){
        if (root->left->right->right->key == root->right->key){
            coeff = (root->left->right->left->key - 48) + 1;
            root->right = NULL;
            free(root->right);
            root = root->left;
            root->right->left->key = coeff + 48;
        }
    }
    if (root->key == '+' && root->right->key == '*' && root->left->key == '+' && root->left->right->key >= 'a' && root->left->right->key <= 'z'){
        if (root->left->right->key == root->right->right->key){
            coeff = (root->right->left->key - 48) + 1;
            root->left->right = NULL;
            free(root->left->right);
            root->left = root->left->left;
            root->right->left->key = coeff + 48;
        }
    }
    if (root->key == '+' && root->right->key >= 'a' && root->right->key <= 'z' && root->left->key == '-' && root->left->right->key == '*'){
        if (root->left->right->right->key == root->right->key){
            printf("%s\n", "Сорри, но отрицательные числа я не умею считать(((");
            return;
        }
    }
    if (root->key == '+' && root->right->key == '*' && root->left->key == '-' && root->left->right->key >= 'a' && root->left->right->key <= 'z'){
        if (root->left->right->key == root->right->right->key){
            letter = root->right->right->key;
            coeff = (root->right->left->key - 48) - 1;
            if (coeff > 1){
                root->left->right = NULL;
                free(root->left->right);
                root->left = root->left->left;
                root->right->left->key = coeff + 48;
            }
            else {
                root->left->right = NULL;
                free(root->left->right);
                root->right->right = NULL;
                root->right->left = NULL;
                free(root->right->right);
                free(root->right->left);
                root->left = root->left->left;
                root->right->left->key = coeff + 48;
                root->right->key = letter;
            }
        }
    }

}

void menu() {
	printf("=============================\n");
	printf("||   1-Enter expression    ||\n");
	printf("||   2-Print expression    ||\n");
	printf("||   3-Print tree          ||\n");
	printf("||   4-Curry to task       ||\n");
	printf("||   0-End                 ||\n");
	printf("=============================\n");
	printf("\n");
}

int main() {
	node *t = NULL;
	int ch = 10, k, x = 0, l = 0;
	char data[100];
	menu();
	while (ch != 0) {
		printf("=> ");
		scanf("%d", &ch);
		switch (ch) {
		case 1:
                printf("Enter expression: ");
                scanf("%s", data);
                k = strlen(data);
                t = maketree(data, 0, k - 1);
                break;
		case 2:
                if (t != NULL && t->key != '-') {
                print_expression(t);
                printf("\n");
                }
				else
                    printf("Expression not enter\n");
                break;
		case 3:
                if (t != NULL && t->key != '-')
                    print_tree(t, 0);
				else
                    printf("Expression not enter\n");
                break;
		case 4:
                task(t);
                print_expression(t);
                printf("\n");
                break;
		}
	}
	return 0;
}
