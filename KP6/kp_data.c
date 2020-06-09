/* №40
 Общая информация о выпускниках школы студента: фамилия, инициалы,
пол, номер класса, буква класса, в каком ВУЗе учится, где работает, 
в каком полку служит и т. п.
*/
#include "data.h"

int main(int argc, char *argv[]) {
	FILE *input_file, *output_file;

	if (argc == 1) { // 0 аргументов
		if ( (input_file = fopen("in.txt", "r")) == NULL ) { // открываем входной
			printf("Can not open input file in.txt\n");
			return 11;
		}
		if ( (output_file = fopen("BASE.dat", "wb")) == NULL ) { // открываем выходной
			printf("Can not open output file BASE.dat\n");
			return 101;
		}
	} else if (argc == 2) { // 1 аргумент
		if (!strcmp(argv[1], "--help")) { // ./cp6_data --help
            printf("Usage: ./cp6_data [input.txt] [output.dat] [out.txt]\n"); // справка о проге
            printf("If the arguments are not entered, then program sets default ones:\n");
            printf("in.txt - input text file\n");
            printf("BASE.dat - output nontext file\n");
            printf("out.txt - output text file\n");
            _Exit(0);
        }
		if ( (input_file = fopen(argv[1], "r")) == NULL ) { // открываем входной
			printf("Can not open input file %s\n", argv[1]);
			return 22;
		}
		if ( (output_file = fopen("BASE.dat", "wb")) == NULL ) { // открываем выходной
			printf("Can not open output file BASE.dat\n");
			return 101;
		}
	} else { // 2 и больше аргументов
		if ( (input_file = fopen(argv[1], "r")) == NULL ) { // открываем входной
			printf("Can not open input file %s\n", argv[1]);
			return 22;
		}
		if ( (output_file = fopen(argv[2], "wb")) == NULL ) { // открываем выходной
			printf("Can not open output file %s\n", argv[2]);
			return 202;
		}
	}
	while(!feof(input_file)) {
		fscanf(input_file, "%s %s %c %d %c %s %s %s", current_graduate.surname, current_graduate.initials, &current_graduate.gender, &current_graduate.class_number, &current_graduate.class_letter, current_graduate.university, current_graduate.work, current_graduate.military); // считываем значения из тхт
		fwrite(&current_graduate, sizeof(current_graduate), 1, output_file); // записываем в .дат
	}
	fclose(input_file); // закрываем входной файл
	fclose(output_file); // закрываем выходной файл

	if (argc == 1 || argc == 2) { // задан 1 аргумент или не заданы
		if ( (input_file = fopen("BASE.dat", "rb")) == NULL ) { // открываем входной
			printf("Can not read input file BASE.dat\n");
			return 33;
		}
		if ( (output_file = fopen("out.txt", "w")) == NULL ) { // открываем выходной
			printf("Can not open output file out.txt\n");
			return 303;
		}
	} else if (argc == 3) { // заданы 2 аргумента
		if ( (input_file = fopen(argv[2], "rb")) == NULL ) { // открываем входной
			printf("Can not read input file %s\n", argv[2]);
			return 44;
		}
		if ( (output_file = fopen("out.txt", "w")) == NULL ) { // открываем выходной
			printf("Can not open output file out.txt\n");
			return 303;
		}
	} else { // заданы 3 аргумента
		if ( (input_file = fopen(argv[2], "rb")) == NULL ) { // открываем входной
			printf("Can not read input file %s\n", argv[2]);
			return 44;
		}
		if ( (output_file = fopen(argv[3], "w")) == NULL ) { // открываем выходной
			printf("Can not open output file %s\n", argv[3]);
			return 404;
		}
	}

	printf("========================================================================================================\n");
    printf("| Surname              | IN | GENDER | CLASS | LETTER | UNIVERSIRY | WORK       | MILITARY             |\n");
    printf("|----------------------|----|--------|-------|--------|------------|------------|----------------------|\n");

    while (!feof(input_file)) {
    	previous_graduate = current_graduate; // запоминаем прошлого
    	fread(&current_graduate, sizeof(current_graduate), 1, input_file); // считываем структуру

    	if (strcmp(current_graduate.surname, previous_graduate.surname) && strcmp(current_graduate.initials,previous_graduate.initials)) { // защита от повторений
    		fprintf(output_file, "surname=%s, initials=%s, gender=%c, class_number=%d, class_letter=%c, university=%s, work=%s, military=%s\n", current_graduate.surname, current_graduate.initials, current_graduate.gender, current_graduate.class_number, current_graduate.class_letter, current_graduate.university, current_graduate.work, current_graduate.military); // заносим в файл
    	    printf("| %-20s | %-2s | %-6c | %-5d | %-6c | %-10s | %-10s | %-20s |\n", current_graduate.surname, current_graduate.initials, current_graduate.gender, current_graduate.class_number, current_graduate.class_letter, current_graduate.university, current_graduate.work, current_graduate.military); // печатаем в терминал
    	}
    }
    printf("========================================================================================================\n");
    
	fclose(input_file); // закрываем входной файл
	fclose(output_file); // закрываем выходной файл
	return 0;
}
