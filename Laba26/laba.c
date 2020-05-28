#include"data.h"

listptr push_front(listptr *l, int value){
    listptr current = *l;
    listptr previous = NULL;
    
    while (current != NULL){
        previous = current;
        current = current->next;
    }
    current = malloc(sizeof(list));
    if (current == NULL) //снова никогда не произойдет, кек
        return NULL;
    current->value = value;
    current->next = NULL;
    current->prev = previous;
    if (previous == NULL)
        *l = current;
    else
        previous->next = current;
    return current;
}

listptr push_back(listptr *l, int value){
    listptr current = *l;
    listptr next = NULL;
    
    if (current != NULL){
        next = current;
        current = current->prev;
    }
    current = malloc(sizeof(list));
    if (current == NULL)
        return NULL;
    current->value = value;
    current->next = next;
    current->prev = NULL;
    if (next != NULL){
        next->prev = current;
        *l = current;
    }
    return current;
}

bool pop_front(listptr *l){
    listptr current = *l;
    listptr previous = NULL;
    
    if (current == NULL)
        return false;
    
    while (current->next != NULL){
        previous = current;
        current = current->next;
    }
    if (previous != NULL)
        previous->next = NULL;
    else
        *l = NULL;
    free(current);
    return true;
}

bool pop_back(listptr *l){
    listptr current = *l;
    
    if (current == NULL)
    return false;
    
    if (current->next == NULL)
        *l = NULL;
    else{
        (current->next)->prev = NULL;
        *l = current->next;
    }
    free(current);
    return true;
}

void print_list(listptr *l){
    listptr current = *l;
    
    if (current == NULL)
        printf("%s\n", "Sorry, list is empty");
    else
        while (current != NULL){
            printf("%d", current->value);
            if (current->next != NULL)
                printf("%s", "->");
            current = current->next;
        }
}

void print_menu(){
    printf ("%s\n", "\nWelcome!");
    printf ("%s\n", "Press af to add cell in front of list");
    printf ("%s\n", "Press ab to add cell in back of list");
    printf ("%s\n", "Press df to delete cell in front of list");
    printf ("%s\n", "Press db to delete cell in back of list");
    printf ("%s\n", "Press p to print list");
    printf ("%s\n", "Press m to see menu");
    printf ("%s\n", "Press e to exit");
    printf ("%s\n", "Press F to pay respect");
}

int main (){
    print_menu();
    listptr l = NULL;
    int value;
    bool flag;
    char argument;
    char second_argument;
    while (true){
        if (argument != '\n')
            printf("%s\n", "\nWhat do you want to do?");
        scanf("%c", &argument);
        if (argument == 'a'){
            scanf("%c", &second_argument);
            if (second_argument == 'f'){
                printf("%s", "Enter a number that u want to add: ");
                scanf("%d", &value);
                if (l == NULL)
                    l = push_front(&l, value);
                else
                    push_front(&l, value);
            }
            if (second_argument == 'b'){
                printf("%s", "Enter a number that u want to add: ");
                scanf("%d", &value);
                if (l == NULL)
                    l = push_back(&l, value);
                else
                    push_back(&l, value);
            }
        }
        else if (argument == 'd'){
            scanf("%c", &second_argument);
            if (second_argument == 'f'){
                flag = pop_front(&l);
                if (flag == false)
                    printf("%s\n", "Чтобы продать что-нибудь ненужное, нужно сначала купить что-нибудь ненужное, а у нас денег нет...");
            }
            if (second_argument == 'b'){
                 flag = pop_back(&l);
                if (flag == false)
                    printf("%s\n", "Чтобы продать что-нибудь ненужное, нужно сначала купить что-нибудь ненужное, а у нас денег нет...");
            }
        }
        else if (argument == 'p'){
            printf("\n");
            print_list(&l);
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

