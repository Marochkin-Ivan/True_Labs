// №40 Выяснить, имеются ли в школе однофамильцы.
#include "data.h"

int main(int argc, char *argv[]) {
	FILE *input_file, *input_file2, *output_file;
	int count = 0;
	
	if (argc == 1) { // 0 аргументов
		if ( (input_file = fopen("BASE.dat", "rb")) == NULL ) {
			printf("Can not open input file BASE.dat\n");
			return 11;
		}
		if ( (input_file2 = fopen("BASE.dat", "rb")) == NULL ) {
			printf("Can not open input file BASE.dat\n");
			return 110;
		}
		if ( (output_file = fopen("out_task.txt", "w")) == NULL ) {
			printf("Can not open output file out_task.txt\n");
			return 101;
		}
	} else if (argc == 2) { // 1 аргумент
		if (!strcmp(argv[1], "--help")) { // ./cp6_task --help
            printf("Usage: ./cp6_task [input.dat] [output.txt]\n");
            printf("If the arguments are not entered, then program sets default ones:\n");
            printf("BASE.dat - input nontext file\n");
            printf("out_task.txt - output text file\n");
            _Exit(0);
        }
		if ( (input_file = fopen(argv[1], "rb")) == NULL ) {
			printf("Can not open input file %s\n", argv[1]);
			return 22;
		}
		if ( (input_file2 = fopen(argv[1], "rb")) == NULL ) {
			printf("Can not open input file %s\n", argv[1]);
			return 220;
		}
		if ( (output_file = fopen("out_task.txt", "w")) == NULL ) {
			printf("Can not open output file out_task.txt\n");
			return 101;
		}
	} else { // 2 и больше аргументов
		if ( (input_file = fopen(argv[1], "rb")) == NULL ) {
			printf("Can not open input file %s\n", argv[1]);
			return 22;
		}
		if ( (input_file2 = fopen(argv[1], "rb")) == NULL ) {
			printf("Can not open input file %s\n", argv[1]);
			return 220;
		}
		if ( (output_file = fopen(argv[2], "w")) == NULL ) {
			printf("Can not open output file %s\n", argv[2]);
			return 202;
		}
	}
	while (!feof(input_file)) {
    	previous_graduate = current_graduate;
    	fread(&current_graduate, sizeof(current_graduate), 1, input_file);
    	if (strcmp(current_graduate.surname, previous_graduate.surname) && strcmp(current_graduate.initials,previous_graduate.initials)) {
    		rewind(input_file2);
    		while (!feof(input_file2)) {
		    	previous_graduate2 = current_graduate2;
		    	fread(&current_graduate2, sizeof(current_graduate2), 1, input_file2);
		    	if (strcmp(current_graduate2.surname, previous_graduate2.surname) && strcmp(current_graduate2.initials, previous_graduate2.initials)) {
		    		if (strcmp(current_graduate.initials, current_graduate2.initials)) {
			    	    if (strlen(current_graduate2.surname) >= strlen(current_graduate.surname)) {
			    	    	if (strncmp(current_graduate2.surname, current_graduate.surname, strlen(current_graduate.surname)) == 0)
			    	    		count++;
			    	    } else if (strlen(current_graduate2.surname) < strlen(current_graduate.surname)) {
			    	    	if (strncmp(current_graduate2.surname, current_graduate.surname, strlen(current_graduate2.surname)) == 0)
			    	    		count++;
			    	    }
			    	}
		    	}
	    	}
    	}
    }
	if (count > 0) {
		printf("There are students with the same surname\n");
		fputs("There are students with the same surname", output_file);
	} else {
		printf("There are NO students with the same surname\n");
		fputs("There are NO students with the same surname", output_file);
	}
	fclose(input_file);
	fclose(input_file2);
	fclose(output_file);
	return 0;
}
