#include"data.h"
#define new_size 1.5
#define min_size 4
#define out_of_memory -1
#define underflow -2
#define overflow -3

listptr create(){
    listptr l = NULL;
    l = malloc(sizeof(list));
    if (l == NULL)
        exit(out_of_memory);
    l->size = min_size;
    l->data = malloc(l->size * (sizeof(int)));
    if (l->data == NULL)
    {
        free(l);
        exit(out_of_memory);
    }
    l->top = 0;
    return l;
}

void resize(listptr *l){
    listptr lptr = *l;
    lptr->size *= new_size;
    lptr->data = realloc(lptr->data, lptr->size * (sizeof(int)));
    if (lptr->data == NULL)
        exit(overflow);
}

void pop_back(listptr l){
    if (l->top == 0)
        exit(underflow);
    l->top--;
}

void pop_front(listptr l){
    if (l->top == 0)
        exit(underflow);
    for (int i = 1; i < l->top; i++){
        l->data[i - 1] = l->data[i];
    }
    l->top--;
}

void push_back(listptr l, int value){
    if (l->top >= l->size)
        resize(&l);
    l->data[l->top] = value;
    l->top++;
}

void push_front(listptr l, int value){
    if (l->top >= l->size)
        resize(&l);
    if (l->top == 0){
        l->data[0] = value;
        l->top++;
        return;
    }
    for (int i = l->top - 1; i >= 0; i--){
        l->data[i + 1] = l->data[i];
    }
    l->data[0] = value;
    l->top++;
}

bool list_is_empty(listptr l){
    if (l->top == 0)
        return true;
    return false;
}

void list_insert(listptr l, int pos, int value){
    if ((l->top + 1) >= l->size)
        resize(&l);
    bool flag = false;
    int i = pos;
    if (list_is_empty(l)){
        l->data[l->top] = value;
        return;
    }
    l->data[i + 1] = value;
    while (flag == false && i >= 0){
        if (l->data[i] > value){
            l->data[i + 1] = l->data[i];
            l->data[i] = value;
        }
        else
            flag = true;
        i--;
    }
}

void list_sort(listptr l){
    if (list_is_empty(l))
        return;
    for (int i = 1; i < l->top; i++)
        list_insert(l, i - 1, l->data[i]);
}

void print_list(listptr l){
    if (list_is_empty(l) == true)
        return;
    for (int i = 0; i < l->top; i++)
    {
        printf("%d", l->data[i]);
        if (i != l->top - 1)
            printf("%s", "->");
    }
    printf("\n");
}


void print_menu(){
    printf ("%s\n", "\nWelcome!");
    printf ("%s\n", "Нажмите af чтобы добавить элемент в начало списка");
    printf ("%s\n", "Нажмите ab чтобы добавить элемент в конец списка");
    printf ("%s\n", "Нажмите df чтобы удалить элемент из начала списка");
    printf ("%s\n", "Нажмите db чтобы удалить элемент из конца списка");
    printf ("%s\n", "Нажмите s чтобы отсортировать список");
    printf ("%s\n", "Нажмите p чтобы вывести список");
    printf ("%s\n", "Нажмите m чтобы увидеть меню");
    printf ("%s\n", "Нажмите e чтобы выйти");
    printf ("%s\n", "Нажмите F to pay respect");
}

int main (){
    print_menu();
    listptr l = create();
    int value;
    char argument = '\0';
    char second_argument;
    while (true){
        if (argument != '\n')
            printf("%s\n", "\nЧто вы хотите сделать?");
        scanf("%c", &argument);
        if (argument == 'a'){
            scanf("%c", &second_argument);
            if (second_argument == 'f'){
                printf("%s", "Введите элемент, который хотите добавить: ");
                scanf("%d", &value);
                push_front(l, value);
                print_list(l);
            }
            if (second_argument == 'b'){
                printf("%s", "Введите элемент, который хотите добавить: ");
                scanf("%d", &value);
                push_back(l, value);
                print_list(l);
            }
        }
        else if (argument == 'd'){
            if (list_is_empty(l) == true){
                printf("%s\n", "Чтобы продать что-нибудь ненужное, нужно сначала купить что-нибудь ненужное, а у нас денег нет...");
            }
            else
                scanf("%c", &second_argument);
                if (second_argument == 'f'){
                    pop_front(l);
                    print_list(l);
                }
                if (second_argument == 'b'){
                    pop_back(l);
                    print_list(l);
                }
        }
        else if (argument == 's'){
            list_sort(l);
            print_list(l);
        }
        else if (argument == 'p'){
            printf("\n");
            print_list(l);
        }
        else if (argument == 'm'){
                print_menu();
        }
        else if (argument == 'e'){
                break;
        }
        else if (argument == 'F'){
                printf("%s\n", "OH MY, Thanks for pay respect!");
        }
        else if (argument != '\n'){
                printf("%s\n", "No such argument, try another one!");
        }
    }
}

