#include "data.h"

treeptr find_cell(treeptr t, int value){
    while (t != NULL && value != t->value){
        if (value > t->value)
            t = t->right;
        else
            t = t->left;
    }
    return t;
}

treeptr add_cell(treeptr *t, int value){
    treeptr prev = NULL;
    treeptr cur = *t;
    
    while (cur != NULL && value != cur->value){
        prev = cur;
        if (value > cur->value)
            cur = cur->right;
        else
            cur = cur->left;
    }
    
    if (cur != NULL){
        printf("%s\n", "This value already been in tree, write another one");
        return cur;
    }
    else{
        cur = malloc(sizeof(tree));
        if (cur == NULL)
            return NULL; //никогда не произойдет, кек
        cur->value = value;
        cur->left = NULL;
        cur->right = NULL;
        cur->parent = prev;
        if (prev == NULL)
            *t = cur;
        else if (cur->value > prev->value)
            prev->right = cur;
        else
            prev->left = cur;
        return cur;
    }
}

bool new_delete(treeptr *t, int value){
    treeptr cur;
    treeptr to_delete = find_cell(*t, value);
    if (to_delete == NULL)
        return false;
    
    if (to_delete->left == NULL){
        if (to_delete->right != NULL){
            if (to_delete->parent != NULL){
                (to_delete->right)->parent = to_delete->parent;
                if (to_delete == (to_delete->parent)->right)
                    (to_delete->parent)->right = to_delete->right;
                else
                    (to_delete->parent)->left = to_delete->right;
            }
            else{
                *t = to_delete->right;
                to_delete->right->parent = NULL;
            }
        }
        else{
            if (to_delete->parent != NULL){
                if (to_delete->value > (to_delete->parent)->value)
                    (to_delete->parent)->right = NULL;
                else
                    (to_delete->parent)->left = NULL;
            }
            else
                *t = NULL;
        }
    }
    else{
        bool flag = false;
        cur = to_delete->left;
        while (cur->right != NULL){
            cur = cur->right;
            flag = true;
        }
        if (flag == true){
            if (cur->left != NULL){
                (cur->left)->parent = cur->parent;
                (cur->parent)->right = cur->left;
            }
            else
                (cur->parent)->right = NULL;
        }
        cur->right = to_delete->right;
        if (to_delete->left == cur)
            cur->left = (to_delete->left)->left;
        else
            cur->left = to_delete->left;
        if (to_delete->right != NULL)
            (to_delete->right)->parent = cur;
        if (to_delete->left != NULL)
            (to_delete->left)->parent = cur;
        if (to_delete->parent != NULL){
            cur->parent = to_delete->parent;
            if (to_delete == (to_delete->parent)->left)
                (to_delete->parent)->left = cur;
            else
                (to_delete->parent)->right = cur;
        }
        else{
            *t = cur;
            cur->parent = NULL;
        }
    }
    free(to_delete);
    return true;
}

int function(treeptr t){ // определение значения нетерминальной вершины двоичного дерева с максимальной глубиной
    int max_long = 0;
    int current_long = 0;
    treeptr max;
    treeptr prev = NULL;
    while(t){
        if (t->parent == prev){
            prev = t;
            if (t->left != NULL){
                t = t->left;
                current_long++;
            }
            else if (t->right != NULL){
                t = t->right;
                current_long++;
            }
            else{
                t = t->parent;
                current_long--;
                if (max_long < current_long){
                    max_long = current_long;
                    max = t;
                }
            }
        }
        else if (prev == t->left){
            prev = t;
            if (t->right != NULL){
                t = t->right;
                current_long++;
            }
            else{
                t = t->parent;
                current_long--;
            }
        }
        else if (prev == t->right){
            prev = t;
            t = t->parent;
            current_long--;
        }
    }
    int res = max->value;
    return res;
}

void print_tree(treeptr t, int space){
    if (t == NULL){
        printf("%s\n", "Tree is empty");
        return ;
    }
    int i = space;
    if (t->right != NULL)
        print_tree(t->right, space + 1);
    for (; i > 0; i--)
        printf("%s", "  ");
    printf("%d\n", t->value);
    if (t->left != NULL)
        print_tree(t->left, space + 1);
}

void print_menu(){
    printf ("%s\n", "\nWelcome!");
    printf ("%s\n", "Press a to add cell");
    printf ("%s\n", "Press d to delete cell");
    printf ("%s\n", "Press p to print tree");
    printf ("%s\n", "Press c to get function");
    printf ("%s\n", "Press m to see menu");
    printf ("%s\n", "Press e to exit");
    printf ("%s\n", "Press F to pay respect");
}

int main (){
    print_menu();
    treeptr t = NULL;
    int val;
    bool flag;
    char arg;
    while (true){
        if (arg != '\n')
            printf("%s\n", "\nWhat do you want to do?");
        scanf("%c", &arg);
        if (arg == 'a'){
                printf("%s", "Enter a char that u want to add: ");
                scanf("%d", &val);
                if (t == NULL)
                    t = add_cell(&t, val);
                else
                    add_cell(&t, val);
        }
        else if (arg == 'd'){
                printf("%s", "Enter a char that u want to delete: ");
                scanf("%d", &val);
                flag = new_delete(&t, val);
                if (flag == false)
                    printf("%s\n", "Чтобы продать что-нибудь ненужное, нужно сначала купить что-нибудь ненужное, а у нас денег нет...");
        }
        else if (arg == 'p'){
                print_tree(t, 0);
        }
        else if (arg == 'c'){
            if (t != NULL){
                val = function(t);
                printf("Result is: %d\n", val);
            }
            else
                printf("%s\n", "Sorry, tree is empty...");
        }
        else if (arg == 'm'){
                print_menu();
        }
        else if (arg == 'e'){
                break;
        }
        else if (arg == 'F'){
                printf("%s\n", "OH MY, Thanks for pay respect!");
        }
        else if (arg != '\n'){
                printf("%s\n", "No such argument, try another one!");
        }
    }
}
