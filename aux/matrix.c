#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

int LIMIT_VALUE = 100;

void populateMatrix(FILE *file,  char* row, Matrix matrix, int n, int m);


int createMatrixFiles(int n1, int m1, int n2, int m2) {
    Matrix matrix1 = createMatrix(n1, m1);
    Matrix matrix2 = createMatrix(n2, m2);

    writeMatrixToFile(matrix1, "./matrix_1.txt", n1, m1);
    writeMatrixToFile(matrix2, "./matrix_2.txt", n2, m2);

    freeMatrix(matrix1, n1);
    freeMatrix(matrix2, n2);

    return 0;
}

void writeMatrixToFile(Matrix matrix, char* filename, int n, int m) {
    FILE *file;

    file = fopen(filename, "w");

    fprintf(file, "%d %d\n", n, m);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            fprintf(file, "c%zu%zu %f\n", i + 1, j + 1, matrix[i][j]);
        }
    }

    fclose(file);
}

Matrix readMatrixFromFile(filepath filename) {
    Matrix matrix;
    FILE *file;

    file = fopen(filename, "r");

    if (file) {
        char row[128];
        int n, m;
        char* columnFromFirstRow;

        fscanf(file, "%s", row);

        n = atoi(row);
        m = atoi(columnFromFirstRow);

        populateMatrix(file, row, matrix, n, m);
    } else {
        printf("Erro na leitura do arquivo %s\n", filename);
        exit(1);
    }

    return matrix;
}

void populateMatrix(FILE *file,  char* row, Matrix matrix, int n, int m) {
    int i = 0, j = 0;
    while (fscanf(file, "%s", row) != EOF) {
        char* numberFromRow = strtok(row, " ");
        float number = atof(numberFromRow);

        matrix[i][j] = number;

        if (n == i && m == j) {
            break;
        } else if (m == j) {
            ++i;
            j = 0;
        }
    }

    if (n != i && m != j) {
        perror("Erro na quantidade de valores lidos na matriz.\n");
        exit(1);
    }
}

Matrix createMatrix(int n, int m) {
    Matrix newMatrix = (Matrix) malloc(n * sizeof(Line));

    for (size_t i = 0; i < n; ++i) {
        newMatrix[i] = (Line) malloc(m * sizeof(float));
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            newMatrix[i][j] = ((float)rand()/(float)(RAND_MAX)) * LIMIT_VALUE;
        }
    }

    return newMatrix;
}

void freeMatrix(Matrix matrix, int n) {
    for (size_t i = 0; i < n; ++i) {
        free(matrix[i]);
    }

    free(matrix);
}
