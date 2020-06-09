#include"data.h"

void addNode(tNode **list, int index, char value) { // добавить элемент в список
    tNode *following = *list;
    tNode *previous = NULL;
    tNode *node = NULL;
    
    node = (tNode*)malloc(sizeof(tNode)); // создаем новый элемент
    node->value = value;
    node->next = node;
    node->prev = node;
    if (*list == NULL) { // если список был пуст
        *list = node;
    } else {
        for (int i = 0; i < index; i++) // доходим до нужного элемента
            following = following->next;
        previous = following->prev;
        node->next = following;
        node->prev = previous;
        following->prev = node;
        previous->next = node;
    }
}

void deleteNode(tNode **list, int index) { // удалить элемент из списка
    tNode *current = *list;
    tNode *following = NULL;
    tNode *previous = NULL;
    
    if (current->next == current) { // последний элемент в списке
        current->next = NULL;
        current->prev = NULL;
        *list = NULL;
        free(current);
    } else {
        for (int i = 0; i < index; i++) // доходим до нужного элемента
            current = current->next;
        previous = current->prev;
        following = current->next;
        previous->next = following;
        following->prev = previous;
        free(current);
        current = previous;
    }
}

void deleteInRange(tNode **list, char a, char b) { // удаление элементов, значения которых удовлетворяют диапазону
    tNode *current = *list;
    tNode *previous = NULL;
    tNode *following = NULL;

    do {
        previous = current->prev;
        following = current->next;
        if (current->value >= a && current->value <= b) {
            previous->next = following;
            following->prev = previous;
            free(current);
            current = previous;
        }
        current = following;
    } while (current != *list);
}

void createList(tNode **list, int size) { // создать список со случайными значениями
    int element;
    srand(time(NULL));
    
    for (int i = 0; i < size; i++) {
        element = 'a' + rand() % 26;
        addNode(list, i, element);
    }
}

void printList(tNode *list) { // вывести на экран список
    tNode *current = list;
    
    do {
        printf("%c ", current->value);
        current = current->next;
    } while (current != list);
    printf("\n");
}

int lengthList(tNode *list) { // длина списка
    int count = 0; // счетчик
    tNode *current = list;
    
    do {
        count++;
        current = current->next;
    } while (current != list);
    return count;
}


int main() {
    tNode *list = NULL; // список
    int button = 7; // переключатель меню
    int index = 0; // индекс элемента
    char value; // значение элемента
    int size = 0; // размер списка
    char a, b; // диапазон для удаления (пункт 6)
    
    while (button != 0) {
        switch (button) {
        case 1: // Generate list
            if (list != NULL) { // список уже создан !!!
                printf("The list is already created!\n");
            } else {
                printf("Enter the length of a new list: ");
                scanf("%d", &size);
                createList(&list, size);
            }
            break;
        case 2: // Print list (стд)
            if (list == NULL) { // списко пуст !!!
                printf("List is empty!\n");
            } else {
                printList(list);
            }
            break;
        case 3: // Length of the list (стд)
            if (list == NULL) { // список пуст !!!
                printf("List is empty!\n");
            } else {
                printf("The length of the list is %d.\n", lengthList(list));
            }
            break;
        case 4: // Add a new element in the list (стд)
            printf("Enter the index and value for a new element: ");
            scanf("%d %c", &index, &value); // считывание индекса элемента списка
            if (list != NULL && (index > (lengthList(list)+1) || index <= 0)) { // индекс, к которому нельзя обратиться !!!
                printf("Can not add this element. Try different one.\n");
            } else if (list == NULL && index != 1) { // в пустой список добавляется не первый элемент !!!
                printf("Can not add this element. Try different one.\n");
            } else {
                addNode(&list, (index-1), value);
            }
            break;
        case 5: // Delete element from the list (стд)
            if (list == NULL) { // список пуст !!!
                printf("List is empty!\n");
            } else {
                printf("Enter the index of element you want to delete: ");
                scanf("%d", &index); // считывание индекса элемента списка
                if (list != NULL && (index > lengthList(list) || index <= 0)) { // индекс, к которому нельзя обратиться !!!
                    printf("Can not find this element. Try different one.\n");
                } else {
                    deleteNode(&list, (index-1));
                }
            }
            break;
        case 6: // Delete elements in the list in the range (нестд)
            if (list == NULL) {
                printf("List is empty!\n"); // если список пустой
            } else {
                printf("Enter the range: ");
                scanf("%c%*c %c%*c", &a, &b); // считываение диапазона значений
                deleteInRange(&list, a, b);
            }
            break;
        case 7: // Print menu
            printf("[1] Generate list\n[2] Print list\n[3] Length of the list\n[4] Add a new element in the list\n[5] Delete element from the list\n[6] Delete elements in the list in the range\n[7] Print menu\n[0] Exit\n");
            break;
        default:
            printf("No such number of action in the menu. Try again.\n");
            break;
        }
        printf("\nEnter the number of action: "); // считывание действия
        scanf("%d", &button);
    }
    return 0;
}
