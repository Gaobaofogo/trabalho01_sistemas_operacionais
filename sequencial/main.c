#include <stdio.h>
#include "matrix.h"

int argumentsAreValid(int argc);
int mainExec(char* argv[]);
int badExit();

int main(int argc, char* argv[]) {
  if (argumentsAreValid(argc)) {
    return mainExec(argv);
  } else {
    return badExit();
  }
}

int mainExec(char* argv[]) {
  MatrixStruct matrix1 = readMatrixFromFile(argv[1]);
  MatrixStruct matrix2 = readMatrixFromFile(argv[2]);

  MatrixReport result = multiplicateMatrixSeq(matrix1, matrix2);
  writeMatrixReportToFile(result, "../matrix_report.txt");

  freeMatrix(matrix1.data, matrix1.n);
  freeMatrix(matrix2.data, matrix2.n);
  freeMatrix(result.matrixStruct.data, result.matrixStruct.n);

  return 0;
}

int argumentsAreValid(int argc) {
  return argc == 3;
}

int badExit() {
  perror("Quantidade de argumentos inválida.\n");
  perror("Exemplo de uso: ./prog matrix1.txt ../matrix2.txt");

  return 1;
}
