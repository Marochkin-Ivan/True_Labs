#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graduate_data {
	char surname[20]; // фамилия
	char initials[3]; // инициалы
	char gender; // пол
	int class_number; // номер класса
	char class_letter; // буква класса
	char university[10]; // в каком ВУЗе учится
	char work[10]; // где работает
	char military[20]; // в каком полку служит
} current_graduate, previous_graduate, current_graduate2, previous_graduate2;

