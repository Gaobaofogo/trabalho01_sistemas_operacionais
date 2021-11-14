#ifndef MATRIX_H_
#define MATRIX_H_

typedef float** Matrix;
typedef float* Line;
typedef char* filepath;


int createMatrixFiles(int n1, int m1, int n2, int m2);
Matrix createMatrix(int n, int m);
void freeMatrix(Matrix matrix, int n);
void writeMatrixToFile(Matrix matrix, char* filename, int n, int m);
Matrix readMatrixFromFile(filepath filename);

#endif // MATRIX_H_
