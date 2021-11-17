#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "matrix.h"

int LIMIT_VALUE = 100;

void populateMatrix(FILE *file, Matrix matrix, int n, int m);


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
            fprintf(file, "%f\n", matrix[i][j]);
        }
    }

    fclose(file);
}

void writeMatrixReportToFile(MatrixReport matrixReport, char* filename) {
    FILE *file;

    file = fopen(filename, "w");

    fprintf(file, "%d %d\n", matrixReport.matrixStruct.n, matrixReport.matrixStruct.m);

    for (size_t i = 0; i < matrixReport.matrixStruct.n; ++i) {
        for (size_t j = 0; j < matrixReport.matrixStruct.m; ++j) {
            fprintf(file, "c[%lu][%lu] = %f\n", i + 1, j + 1, matrixReport.matrixStruct.data[i][j]);
        }
    }

    fprintf(file, "%f\n", matrixReport.timeSpent);

    fclose(file);
}

MatrixStruct readMatrixFromFile(filepath filename) {
    MatrixStruct matrixData;
    FILE *file;

    file = fopen(filename, "r");

    if (file) {
        char row[128];
        int n, m;
        char* columnFromFirstRow = "";

        fscanf(file, "%127s", row);

        n = atoi(row);
        columnFromFirstRow = strtok(row, " ");
        m = atoi(columnFromFirstRow);

        matrixData.n = n;
        matrixData.m = m;
        matrixData.data = createMatrix(n, m);

        populateMatrix(file, matrixData.data, n, m);
    } else {
        printf("Erro na leitura do arquivo %s\n", filename);
        exit(1);
    }

    return matrixData;
}

void populateMatrix(FILE *file, Matrix matrix, int n, int m) {
    char row[128] = {};
    int i = 0, j = 0;
    fscanf(file, "%127s", row);

    while (fscanf(file, "%127s", row) != EOF || (i < n && j < m)) {
        float number = atof(row);
        matrix[i][j] = number;

        ++j;
        if ((i + 1) == n && j == m) {
            break;
        }
        if (j >= m) {
            ++i;
            j = 0;
        }
    }

    if (n != i && m != j) {
        perror("Erro na quantidade de valores lidos na matriz.\n");
        exit(1);
    }
}

MatrixReport multiplicateMatrixSeq(MatrixStruct m1, MatrixStruct m2) {
    if (m1.m != m2.n) {
        perror("A quantidade de colunas e linhas são diferentes.\n");
        perror("Não é possível realizar a operação.\n");

        exit(1);
    }

    MatrixReport newMatrix;
    newMatrix.matrixStruct.n = m1.n;
    newMatrix.matrixStruct.m = m2.m;
    newMatrix.matrixStruct.data = createMatrix(m1.n, m2.m);

    clock_t begin = clock();

    for (size_t i = 0; i < m1.n; ++i) {
        for (size_t j = 0; j < m2.m; ++j) {
            for (size_t k = 0; k < m2.m; ++k) {
                newMatrix.matrixStruct.data[i][j] = m1.data[i][k] * m2.data[k][j];
            }
        }
    }

    clock_t end = clock();
    newMatrix.timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

    return newMatrix;
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
