#include"data.h"
#define new_size 1.5
#define min_size 4

stackptr create()
{
    stackptr c = NULL;
    c = malloc(sizeof(stack));
    if (c == NULL)
        exit(-1);
    c->size = min_s;
    c->data = malloc(c->size * (sizeof(int)));
    if (c->data == NULL)
    {
        free(c);
        exit(-1);
    }
    c->top = 0;
    return c;
}

void del_all(stackptr *s)
{
//    free((*s)->data);
    free(*s);
    *s = NULL;
}

void resize(stackptr *s)
{
    stackptr c = *s;
    c->size *= new_size;
    c->data = realloc(c->data, c->size * (sizeof(int)));
    if (c->data == NULL)
        exit(-3);
}

int s_pop(stackptr *s)
{
    stackptr c = *s;
    if (c->top == 0)
        exit(-2);
    c->top--;
    return c->data[c->top];
}

void s_push(stackptr s, int value)
{
    if (s->top >= s->size)
        resize(&s);
    s->data[s->top] = value;
    s->top++;
}

bool s_is_empty(stackptr s)
{
    if (s->top == 0)
        return true;
    return false;
}

void s_insert(stackptr s, int pos, int value)
{
    if ((s->top + 1) >= s->size)
        resize(&s);
    bool flag = false;
    int i = pos;
    if (s_is_empty(s))
    {
        s->data[s->top] = value;
        return;
    }
    s->data[i + 1] = value;
    while (!flag && i >= 0)
    {
        if (s->data[i] > value)
        {
            s->data[i + 1] = s->data[i];
            s->data[i] = value;
        }
        else
            flag = true;
        i--;
    }
//    s->top++; добавить в main
}

void s_sort(stackptr s)
{
    if (s_is_empty(s))
        return;
    for (int i = 1; i < s->top; i++)
        s_insert(s, i - 1, s->data[i]);
}

void print_stack(stackptr s)
{
    for (int i = 0; i < s->top; i++)
    {
        printf("%d", s->data[i]);
        if (i != s->top - 1)
            printf("%s", "->");
    }
    printf("\n");
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

