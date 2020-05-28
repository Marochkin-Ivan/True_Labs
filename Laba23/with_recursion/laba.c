#include "data.h"

treeptr find_parent(treeptr t, int value){
    treeptr parent;
    while (t != NULL && value != t->value){
        parent = t;
        if (value > t->value)
            t = t->right;
        else
            t = t->left;
    }
    if (t == NULL)
        parent = NULL;
    return parent;
}

bool add_cell(treeptr *t, int value){
    treeptr cur = *t;
    treeptr cur_parent;
    bool right = false;
    bool left = false;
    
    if (cur == NULL){ // создаем корень дерева
        cur = malloc(sizeof(tree));
        if (cur == NULL)
            return false;
        cur->value = value;
        cur->right = NULL;
        cur->left = NULL;
        *t = cur;
        return true;
    }
    if (value > cur->value){ // идем вправо
        if (cur->right == NULL){
            cur_parent = cur;
            cur = cur->right;
            right = true;
        }
        else
            return add_cell(&cur->right, value);
    }
    else if (value < cur->value){ // идем влево
        if (cur->left == NULL){
            cur_parent = cur;
            cur = cur->left;
            left = true;
        }
        else
            return add_cell(&cur->left, value);
    }
    if (cur == NULL){
        cur = malloc(sizeof(tree));
        if (cur == NULL)
            return false;
        cur->value = value;
        cur->right = NULL;
        cur->left = NULL;
        if (right == true)
            cur_parent->right = cur;
        if (left == true)
            cur_parent->left = cur;
        return true;
    }
    else
        return false; // такое значение уже есть в дереве
}

bool delete_cell(treeptr *t, int value){
    treeptr root = *t;
    
    if (root == NULL) // дерево пустое
        return false;
    // удаляем корень:
    if (root->value == value){
        if (root->right == NULL && root->left == NULL){ // корень-лист
            *t = NULL;
            return true;
        }
        if (root->right != NULL && root->left == NULL){ // у корня есть только правый сын
            *t = root->right;
            free(root);
            return true;
        }
        if (root->right == NULL && root->left != NULL){ // у корня есть только левый сын
            *t = root->left;
            free(root);
            return true;
        }
        if (root->right != NULL && root->left != NULL){ // у корня есть оба сына
            if (root->left->right == NULL){ // не идем в цикл
                *t = root->left;
                root->left->right = root->right;
                free(root);
                return true;
            }
            else{ // идем в цикл
                treeptr rep = root->left;
                treeptr rep_parent;
                while (rep->right != NULL){
                    rep_parent = rep;
                    rep = rep->right;
                }
                rep_parent->right = rep->left;
                rep->right = root->right;
                rep->left = root->left;
                *t = rep;
                free(root);
                return true;
            }
        }
    }
    // удаляем НЕ корень:
    treeptr parent = find_parent(root, value);
    treeptr to_delete = NULL;
    if (parent != NULL){
        if (parent->right != NULL){
            if (value == parent->right->value)
                to_delete = parent->right;
        }
        if (parent->left != NULL){
            if (value == parent->left->value)
                to_delete = parent->left;
        }
    }
    else // в дереве нет такого значения
        return false;
    if (to_delete->right == NULL && to_delete->left == NULL){ // лист
        if (to_delete == parent->right)
            parent->right = NULL;
        else
            parent->left = NULL;
        free(to_delete);
        return true;
    }
    if (to_delete->right != NULL && to_delete->left == NULL){ // есть только правый сын
        if (to_delete == parent->right)
            parent->right = to_delete->right;
        else
            parent->left = to_delete->right;
        free(to_delete);
        return true;
    }
    if (to_delete->right == NULL && to_delete->left != NULL){ // есть только левый сын
        if (to_delete == parent->right)
            parent->right = to_delete->left;
        else
            parent->left = to_delete->left;
        free(to_delete);
        return true;
    }
    if (to_delete->right != NULL && to_delete->left != NULL){ // есть оба сына
        if (to_delete->left->right == NULL){ // не идем в цикл
            if (to_delete == parent->right){
                parent->right = to_delete->left;
                to_delete->left->right = to_delete->right;
            }
            else{
                parent->left = to_delete->left;
                to_delete->left->right = to_delete->right;
            }
            free(to_delete);
            return true;
        }
        else{ // идем в цикл
            treeptr rep = to_delete->left;
            treeptr rep_parent;
            while (rep->right != NULL){
                rep_parent = rep;
                rep = rep->right;
            }
            rep_parent->right = rep->left;
            rep->right = to_delete->right;
            rep->left = to_delete->left;
            if (to_delete == parent->right)
                parent->right = rep;
            else
                parent->left = rep;
            free(to_delete);
            return true;
        }
    }
    return true;
}

depthptr find_max_depth(treeptr t, int cur_depth, int prev, depthptr d){
    //printf("%d %d %d\n", t->value, cur_depth, d->max);
    if (cur_depth > d->max){
        d->max = cur_depth;
        d->cell = prev;
    }
    prev = t->value;
    if (t->left != NULL)
        d = find_max_depth(t->left, cur_depth + 1, prev, d);
    if (t->right != NULL)
        d = find_max_depth(t->right, cur_depth + 1, prev, d);
    return d;
}

void print_tree(treeptr t, int space){
    if (t == NULL){
        printf("%s\n", "Дерево пустое...");
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
    printf ("%s\n", "\nЗдравствуйте!");
    printf ("%s\n", "Нажмите a чтобы добавить значение в дерево");
    printf ("%s\n", "Нажмите d чтобы удалить значение из дерева");
    printf ("%s\n", "Нажмите p чтобы отобразить дерево");
    printf ("%s\n", "Нажмите f чтобы посчитать функцию");
    printf ("%s\n", "Нажмите m чтобы увидеть меню");
    printf ("%s\n", "Нажмите e чтобы выйти");
    printf ("%s\n", "Press F to pay curpect");
}

int main (){
    print_menu();
    treeptr t = NULL;
    depthptr d = malloc(sizeof(depth));
    d->max = 0;
    d->cell = 0;
    int val;
    bool flag;
    char arg;
    while (true){
        if (arg != '\n')
            printf("%s\n", "\nЧто хотите сделать?");
        scanf("%c", &arg);
        if (arg == 'a'){
            printf("%s", "Введите добавляемое значение: ");
            scanf("%d", &val);
            flag = add_cell(&t, val);
            if (flag == false)
                printf("%s\n", "Кажется, такое значение уже есть в дереве, проверьте");
            else
                print_tree(t, 0);
        }
        else if (arg == 'd'){
            printf("%s", "Введите удаляемое значение: ");
            scanf("%d", &val);
            flag = delete_cell(&t, val);
            if (flag == false)
                printf("%s\n", "Чтобы продать что-нибудь ненужное, нужно сначала купить что-нибудь ненужное, а у нас денег нет...");
            else
                print_tree(t, 0);
            
        }
        else if (arg == 'p'){
            printf("\n");
            print_tree(t, 0);
        }
        else if (arg == 'f'){
            if (t != NULL){
                d = find_max_depth(t, 0, 0, d);
                val = d->cell;
                if (val == 0)
                    printf("%s\n", "В дереве нет нетерминальных вершин");
                else
                    printf("Результат: %d\n", val);
            }
            else
                printf("%s\n", "Дерево пустое...");
            d->max = 0;
            d->cell = 0;
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
                printf("%s\n", "Такого ключа нет, попробуйте другой!");
        }
    }
}
