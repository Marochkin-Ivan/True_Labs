#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int elementsCounter(int n, int k, int *index) { // кол-во элементов в векторе
    int count = 0, vector_size = 0;

    for (int q = 0; q < k; q++) { // считывание количеств переходов на новую строку
        if (index[q]/(n+1)+1 != count) {
            count = index[q]/n+1;
            vector_size += 2;
        }
    }
    return 2*k+vector_size+2;
}

void toOneVector(int *elements, int *index, int k, int n, int *vector, int vector_size) { // перевод во внутренний вид
    int ind = -1, q = 0, in = 0, dex = 0;

    for (int i = 0; i < vector_size; i+=2) {
        if (index[q]%n == 0)
            dex = index[q]/n;
        else
            dex = index[q]/n+1;
        if (q >= k) {
            vector[i] = 0;
            vector[i+1] = 0;
        } else if (ind != dex) {
            vector[i] = 0;
            vector[i+1] = dex;
            ind = dex;
        } else {
            in = index[q]%n;
            if (index[q]%n == 0)
                in = n;
            vector[i] = in;
            vector[i+1] = elements[q];
            ind = dex;
            q++;
        }
    }
}

void toNatural(int *vector, int vector_size, int m, int n) { // перевод матрицы в естественный вид

    int matrix[m][n];
    int i = 0, j = 0;

    for (i = 0; i < m; i++) // заполняем матрицу нулями
        for (j = 0; j < n; j++)
            matrix[i][j] = 0;
    for (int q = 0; q < vector_size; q+=2) { // заполняем матрицу ненулевыми элементами
        if (vector[q] == 0 && vector[q+1] != 0) {
            i = vector[q+1]-1;
        } else if (vector[q] != 0) {
            j = vector[q]-1;
            matrix[i][j] = vector[q+1];
        }
    }
    for (int i = 0; i < m; i++) { // выводим матрицу
        printf("\n");
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
    }
    printf("\n");
}

void sumMatrix(int *vector1, int *vector2, int size1, int size2, int *vectorR, int sizeR) { // сумма двух разреженных матриц
    int q = 0;

    for (int i = 0, j = 0; j < size2; i+=2, j+=2) {
        if (vector1[i] == 0 && vector2[j] == 0 && vector1[i+1] == 0 && vector2[j+1] == 0) { // окончание записи вектора
            vectorR[q] = 0;
            vectorR[q+1] = 0;
            break;
        } else if (vector1[i] == 0 && vector2[j] == 0 && vector1[i+1] == vector2[j+1]) { // строки равны
            vectorR[q] = vector1[i];
            vectorR[q+1] = vector1[i+1];
            q += 2;
        } else if (vector1[i] == 0 && vector2[j] == 0 && vector1[i+1] != vector2[j+1]) { // строки не равны
            if (vector1[i+1] < vector2[j+1]) { // записываем сначала первый вектор
                do {
                    vectorR[q] = vector1[i];
                    vectorR[q+1] = vector1[i+1];
                    q += 2;
                    i += 2;
                } while (vector1[i] != 0);
                i -= 2;
                do {
                    vectorR[q] = vector2[j];
                    vectorR[q+1] = vector2[j+1];
                    q += 2;
                    j += 2;
                } while (vector2[j] != 0);
                j -= 2;
            } else if (vector1[i+1] > vector2[j+1]) { // записываем сначала второй вектор
                do {
                    vectorR[q] = vector2[j];
                    vectorR[q+1] = vector2[j+1];
                    q += 2;
                    j += 2;
                } while (vector2[j] != 0);
                j -= 2;
                do {
                    vectorR[q] = vector1[i];
                    vectorR[q+1] = vector1[i+1];
                    q += 2;
                    i += 2;
                } while (vector1[i] != 0);
                i -= 2;
            }
        } else if (vector1[i] != 0 && vector2[j] != 0) { // записываем элементы из одной строки
            while (vector1[i] != 0 && vector2[j] != 0) {
                if (vector1[i] == vector2[j]) { // сложение элементов
                    vectorR[q] = vector1[i];
                    vectorR[q+1] = vector1[i+1] + vector2[j+1];
                    q += 2;
                    i += 2;
                    j += 2;
                } else if (vector1[i] < vector2[j]) { // записываем сначала первый вектор
                    vectorR[q] = vector1[i];
                    vectorR[q+1] = vector1[i+1];
                    vectorR[q+2] = vector2[j];
                    vectorR[q+3] = vector2[j+1];
                    q += 4;
                    i += 2;
                    j += 2;
                } else if (vector1[i] > vector2[j]) { // записываем сначала второй вектор
                    vectorR[q] = vector2[j];
                    vectorR[q+1] = vector2[j+1];
                    vectorR[q+2] = vector1[i];
                    vectorR[q+3] = vector1[i+1];
                    q += 4;
                    i += 2;
                    j += 2;
                }
            }
            while (vector1[i] != 0) { // дописываем первый вектор
                vectorR[q] = vector1[i];
                vectorR[q+1] = vector1[i+1];
                q += 2;
                i += 2;
            }
            while (vector2[j] != 0) { // дописываем второй вектор
                vectorR[q] = vector2[j];
                vectorR[q+1] = vector2[j+1];
                q += 2;
                j += 2;
            }
            i -= 2;
            j -= 2;
        }
    }
}

void CheckSymmetry(int *vector, int vector_size, int m, int n) { // проверка симметричности матрицы
    int matrix[m][n];
    int tmatrix[m][n];
    int i = 0, j = 0;
    int flag = 0;

    for (i = 0; i < m; i++) // заполняем матрицу нулями
        for (j = 0; j < n; j++)
            matrix[i][j] = 0;
    for (int q = 0; q < vector_size; q+=2) { // заполняем матрицу ненулевыми элементами
        if (vector[q] == 0 && vector[q+1] != 0) {
            i = vector[q+1]-1;
        } else if (vector[q] != 0) {
            j = vector[q]-1;
            matrix[i][j] = vector[q+1];
        }
    }
    for (i = 0; i < m; i++) // транспонируем матрицу
        for (j = 0; j < n; j++)
            tmatrix[i][j] = matrix[j][i];
    for (i = 0; i < m; i++) // если зеркальные элементы не равны, то меняем значение "флага"
        for (j = 0; j < n; j++) {
            if (i != m  && matrix[i][j] != tmatrix[i][j])
                flag = 1;
        }
    if (flag == 1) // вывод результата
        printf("Sum matrix is NOT symmetrical\n");
    else
        printf("Sum matrix is symmetrical\n");
}

int main(int argc, char *argv[]) {

    FILE *input_file;
    
    if (argc == 1) { // 0 аргументов
        if ( (input_file = fopen("in.txt", "rt")) == NULL ) {
            printf("Can not open in.txt file.\n"); // ошибка открытия файла !!!
            return 101;
        }
    } else { // 1 аргумент
        if (!strcmp(argv[1], "--help")) { // вызов справочной информации
            printf("Usage: ./cp7 [input.txt]\n");
            printf("If the arguments are not entered, then program sets default ones:\nin.txt - input text file\n");
            printf("In your input file you should enter values of:\nheight & width of matrices, numbers of nonzero elements, elements of matrices.\n");
            _Exit(0);
        }
        if ( (input_file = fopen(argv[1], "rt")) == NULL ) {
            printf("Can not open %s file.\n", argv[1]); // ошибка открытия файла !!!
            return 201;
        }
    }

    int m, n, k1, k2;

    fscanf(input_file, "%d", &m); // считывание высоты матриц
    fscanf(input_file, "%d", &n); // считывание ширины матриц

    fscanf(input_file, "%d", &k1); // считывание ненулевых элементов 1 матрицы
    fscanf(input_file, "%d", &k2); // считывание ненулевых элементов 2 матрицы

    int elements1[k1], elements2[k2], index1[k1], index2[k2];

    // ввод первой матрицы в строку
    for (int i = 0; i < k1; i++) {
        fscanf(input_file, "%d", &elements1[i]); // элемент матрицы
        fscanf(input_file, "%d", &index1[i]); // индекс элемента матрицы
        if (i > 0 && index1[i] <= index1[i-1]) {
            printf("You should enter elements in ascending order.\n"); // Неверный формат ввода матрицы !!!
            _Exit(0);
        }
        if (index1[i] > n*m || index1[i] <= 0) {
            printf("In this matrix only %d elements!\n", m*n); // Выход за границы матрицы !!!
            _Exit(0);
        }
    }
    // ввод второй матрицы в строку
    for (int i = 0; i < k2; i++) {
        fscanf(input_file, "%d", &elements2[i]); // элемент матрицы
        fscanf(input_file, "%d", &index2[i]); // индекс элемента матрицы
        if (i > 0 && index2[i] <= index2[i-1]) {
            printf("You should enter elements in ascending order.\n"); // Неверный формат ввода матрицы !!!
            _Exit(0);
        }
        if (index2[i] > n*m || index2[i] <= 0) {
            printf("In this matrix only %d elements!\n", m*n); // Выход за границы матрицы !!!
            _Exit(0);
        }
    }

    fclose(input_file);

    // Вывод считанных значений
    printf("You entered: m = %d, n=%d;\n", m, n);
    printf("Number of nonzero elements for first matrix %d;\n", k1);
    printf("Number of nonzero elements for second matrix %d;\n", k2);
    printf("First entered matrix is\n");
    for (int i = 0; i < k1; i++)
        printf("%d %d ", elements1[i], index1[i]);
    printf("\nSecond entered matrix is\n");
    for (int i = 0; i < k2; i++)
        printf("%d %d ", elements2[i], index2[i]);
    int vector_size1 = elementsCounter(n, k1, index1); // кол-во элементов в массиве 1 вектора
    int vector1[vector_size1];
    printf("\n\nFirst matrix in internal represantation\n"); // внутренний вид 1 матрицы
    toOneVector(elements1, index1, k1, n, vector1, vector_size1);
    for (int i = 0; i < vector_size1; i++) // вывод вектора
        printf("%d ", vector1[i]);
    printf("\n");
    int vector_size2 = elementsCounter(n, k2, index2); // кол-во элементов в массиве 2 вектора
    int vector2[vector_size2];
    printf("Second matrix in internal represantation\n"); // внутренний вид 2 матрицы
    toOneVector(elements2, index2, k2, n, vector2, vector_size2);
    for (int i = 0; i < vector_size2; i++) // вывод вектора
        printf("%d ", vector2[i]);
    printf("\n");
    printf("First full matrix"); // Естественный вид 1 матрицы
    toNatural(vector1, vector_size1, m, n);
    printf("Second full matrix"); // Естественный вид 2 матрицы
    toNatural(vector2, vector_size2, m, n);
    int vector_sizeR = vector_size1 + vector_size2; // кол-во элементов в массиве результирующей матрицы
    int vectorR[vector_sizeR];
    printf("Sum of the first and second matrix in internal represantaion\n"); // сумма двух вышеопределенных матриц
    sumMatrix(vector1, vector2, vector_size1, vector_size2, vectorR, vector_sizeR);
    for (int i = 0; i < vector_sizeR; i++) { // вывод вектора
        if (vectorR[i-2] == 0 && vectorR[i-1] == 0){
            vector_sizeR = i;
            break;
        }
        printf("%d ", vectorR[i]);
    }
    printf("\n");
    printf("Sum full matrix"); // Естественный вид результрующей матрицы
    toNatural(vectorR, vector_sizeR, m, n);
    CheckSymmetry(vectorR, vector_sizeR, m, n); // проверка симметричности матрицы
    return 0;
}
