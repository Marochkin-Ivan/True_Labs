#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char data[14][87]; // массив с ключами и строками
short isSorted = 0; // статус отсортированности

void binarySort(int c) { // сортировка двоичной вставкой
    char tmp[86];
    int left, right, average;

    for (int i = 0; i < c; i++) {
        strcpy(tmp, data[i]); // запоминаем итерируемое значение
        left = 0; // левая граница
        right = i; // правая граница
        while (left < right) {
            average = (left + right) / 2;
            if (strncmp(data[average], tmp, 6) < 0)
                left = average + 1;
            else
                right = average;
        }
        for (int j = i; j > right; j--)
            strcpy(data[j], data[j-1]);
        strcpy(data[right], tmp);
    }
    isSorted = 1; // ставим статус отсортированности
    printf("Binary sort completed!\n");
}

void binarySearch(int c) { // двоичный поиск
    char keySEARCH[6];
    int left, right, average;
    short isFound = 0; // статус поиска

    left = 0; // левая граница поиска
    right = c-1; // правая граница поиска
    printf("Enter the key: ");
    scanf("%s", &*keySEARCH); // считываем значение для поиска
    while (left <= right) {
        average = (left + right) / 2;
        if (strncmp(data[average-1], keySEARCH, 6) == 0) { // значение найдено
            isFound = 1; // меняем статус
            break;
        } else if (strncmp(data[average-1], keySEARCH, 6) < 0) { // значение левее
            left = average + 1;
        } else { // правее
            right = average - 1;
        }
    }
    if (isFound == 1) {
        char stringTMP[80];
        strcpy(stringTMP, &data[average-1][7]); // записываем значение
        printf("Line with key \"%s\" is \"%s\"\n", keySEARCH, stringTMP);
    } else {
        printf("Line with key \"%s\" is not found.\n", keySEARCH);
    }
}

void printTable(int c) { // вывод таблицы в терминал
    char keyTMP[6], stringTMP[80];
    printf("=============================================================================================\n");
    printf("| KEY    | DATA                                                                             |\n");
    printf("|-------------------------------------------------------------------------------------------|\n");
    
    for (int i = 0; i < c; i++) { // пробегаем по всему массиву и выводим содержание на экран
        strncpy(keyTMP, data[i], 6); // записываем ключ
        strcpy(stringTMP, &data[i][7]); // записываем значение

        printf("| %6s | %-80s |\n", keyTMP, stringTMP); // выводим значения
    }
    printf("=============================================================================================\n");

}

void reverseTable(int c) { // переставить строки в обратном порядке
    char dataTMP[86]; // временный массив для строки

    for (int i = 0; i < c/2; i++) {
        strcpy(dataTMP, data[i]); // меняем местами строки
        strcpy(data[i], data[c-i-1]);
        strcpy(data[c-i-1], dataTMP);
    }
    isSorted = 0; // ставим статус неотсортированности
    printf("Reverse completed!\n");
}

void shuffleTable(int c) { // переставить строки в случайном порядке
    char dataTMP[86]; // временный массив для строки
    int r; // заменяемый индекс

    srand(time(NULL));
    for (int i = 0; i < c; i++) {
        r = rand() % c; // генерируем индекс
        if (i == r) {// если индексы равны
            i--;
            continue;
        }
        strcpy(dataTMP, data[i]); // меняем местами строки
        strcpy(data[i], data[r]);
        strcpy(data[r], dataTMP);
    }
    isSorted = 0; // ставим статус неотсортированности
    printf("Shuffle completed!\n");
}

int main(int argc, char *argv[]) {
    int button = 6; // переключатель меню
    int c = 0; // кол-во считанных строк
    FILE *input_file = NULL; // указатель на входной файл

    if (argc == 1) { // 0 аргументов
    	if ( (input_file = fopen("in.txt", "r")) == NULL ) { // открываем выходной файл
    		printf("Can not open input file in.txt\n");
    		return 11;
    	}
    } else if (argc == 2) { // 1 аргумент
    	if ( !strcmp(argv[1],"--help") ) { // ./cp9 --help
    		printf("Usage: ./cp9 [input.txt]\n");
    		printf("If the argument is not entered, then program sets default one:\n"); // справка по программе
            printf("in.txt - input text file.\n");
            printf("The size of the key is 6 bytes.\n");
            printf("Max number of characters in one line is 80.\n");
            printf("Max number of lines is 14.\n");
            return 0;
    	}
    	if ( (input_file = fopen(argv[1], "r")) == NULL ) { // открываем выходной файл
    		printf("Can not open input file %s\n", argv[1]);
    		return 101;
    	}
    }
    while ( !feof(input_file) ) { // считываем строки из файла
    	fscanf(input_file, "%[^\n]%*c", &*data[c]);
    	c++;
    }
    fclose(input_file); // закрываем файл
    while (button != 0) { // меню
    	switch (button) {
    		case 1: // упорядочить строки
    			if (isSorted == 1)
    				printf("Lines are already sorted!\n");
    			else
    				binarySort(c);
    			break;
    		case 2: // переставить строки в обратном порядке
    			reverseTable(c);
    			break;
    		case 3: // переставить строки в случайном порядке
    			shuffleTable(c);
    			break;	
    		case 4: // вывести результат в терминал
    			printTable(c);
    			break;
    		case 5: // бинарный поиск
    			if (isSorted == 0)
    				printf("You must sort lines first!\n");
    			else
    				binarySearch(c);
    			break;
    		case 6: // вывести меню
    			printf("[1] Sort line order\n[2] Reverse line order\n[3] Shuffle line order\n[4] Print lines\n[5] Search line by key\n[6] Print menu\n[0] Exit\n");
    			break;
    		default: // !!!
    			printf("No such number of action in the menu. Try again.\n");
    			break;
    	}
    	printf("Enter the number of action: "); // считывание действия
    	scanf("%d", &button);
    }
    return 0;
}
