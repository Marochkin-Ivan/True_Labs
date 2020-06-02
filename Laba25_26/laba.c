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

void delete(listptr *l) {
    free(*l);
    *l = NULL;
}

bool list_is_empty(listptr l){
    if (l->top == 0)
        return true;
    return false;
}

void push_back(listptr l, int value){
    if (l->top >= l->size)
        resize(&l);
    l->data[l->top] = value;
    l->top++;
}

int pop_back(listptr l){
    if (l->top == 0)
        exit(underflow);
    l->top--;
    return l->data[l->top];
}

int pop_front(listptr l){
    listptr revers_list = create();
    int el;
    
    while (list_is_empty(l) == false)
        push_back(revers_list, pop_back(l));
    el = pop_back(revers_list);
    while (list_is_empty(revers_list) == false)
        push_back(l, pop_back(revers_list));
    return el;
}

void push_front(listptr l, int value){
    listptr revers_list = create();
    
    while (list_is_empty(l) == false)
        push_back(revers_list, pop_back(l));
    push_back(revers_list, value);
    if (revers_list->top >= l->size)
        resize(&l);
    while (list_is_empty(revers_list) == false)
        push_back(l, pop_back(revers_list));
}

void list_insert(listptr l, int value){
    bool flag = false;
    int el;
    listptr new_list = create();
    
    if (list_is_empty(l) == true){
        push_back(l, value);
        return;
    }
    while (list_is_empty(l) == false){
        el = pop_front(l);
        if (value < el && flag == false){
            push_back(new_list, value);
            flag = true;
        }
        push_back(new_list, el);
    }
    if (flag == false)
        push_back(new_list, value);
    while (list_is_empty(new_list) == false)
        push_back(l, pop_front(new_list));
    delete(&new_list);
}

void list_sort(listptr l){
    listptr sort_list = create();
    
    while (list_is_empty(l) == false)
        list_insert(sort_list, pop_front(l));
    while (list_is_empty(sort_list) == false)
        push_back(l, pop_front(sort_list));
    delete(&sort_list);
}

void print_list(listptr l){
    while (list_is_empty(l) == false)
        printf("%d->", pop_front(l));
    printf("%s\n", "NULL");
    printf("\n");
}

int main (){
    listptr l = create();
    int el;
    
    printf("%s\n", "Введите значения через пробел. Для обозначения конца ввода введите любую букву");
    while (scanf("%d", &el) == 1){
            push_back(l, el);
        }
    printf("\n");
    printf("%s","Отсортированный список: ");
    list_sort(l);
    print_list(l);
    printf("%s\n", "Дотвидания!");
    delete(&l);
    return 0;
}

