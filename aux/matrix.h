#ifndef MATRIX_H_
#define MATRIX_H_

typedef float** Matrix;
typedef float* Line;
typedef char* filepath;

typedef struct {
  Matrix data;
  int n;
  int m;
} MatrixStruct;
typedef struct {
  MatrixStruct matrixStruct;
  double timeSpent;
} MatrixReport;

int createMatrixFiles(int n1, int m1, int n2, int m2);
Matrix createMatrix(int n, int m);
void freeMatrix(Matrix matrix, int n);
void writeMatrixToFile(Matrix matrix, char* filename, int n, int m);
void writeMatrixReportToFile(MatrixReport matrixReport, char* filename);
MatrixStruct readMatrixFromFile(filepath filename);
MatrixReport multiplicateMatrixSeq(MatrixStruct m1, MatrixStruct m2);

#endif // MATRIX_H_
