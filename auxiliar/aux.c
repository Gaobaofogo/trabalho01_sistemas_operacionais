#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "matrix.h"

typedef void maybe_throw_error;


int errorArguments();
maybe_throw_error testMatrixMultiplicationExistenceCondition(int m1, int n2);
int amountOfArgumentsIsValid(int argsQuantity);


int main(int argc, char *argv[]) {
    if (amountOfArgumentsIsValid(argc)) {
        srand((unsigned int)time(NULL));

        int n1 = atoi(argv[1]);
        int m1 = atoi(argv[2]);
        int n2 = atoi(argv[3]);
        int m2 = atoi(argv[4]);

        testMatrixMultiplicationExistenceCondition(m1, n2);

        return createMatrixFiles(n1, m1, n2, m2);
    } else {
        return errorArguments();
    }
}


int errorArguments() {
  printf("Uso incorreto do programa auxiliar.\n");
  printf("Exemplo de uso: ./prog 4 3 3 5\n");

  return 1;
}

int amountOfArgumentsIsValid(int argsQuantity) {
    return argsQuantity == 5;
}

/*
** Como diz nesse artigo https://brasilescola.uol.com.br/matematica/multiplicacao-matrizes.htm,
** para a multiplicação de matrizes existir, o numero de colunas da primeira matriz precisa ser
** igual ao número de linhas da segunda matriz. Se esse fator não for correspondido, a operação
** de multiplicação não existe e não faz sentido continuar o programa.
*/
maybe_throw_error testMatrixMultiplicationExistenceCondition(int m1, int n2) {
    if (m1 != n2) {
        printf("O número de colunas da primeira matriz é diferente do numero de \n");
        printf("linhas da segunda matriz: %d != %d\n", m1, n2);
        exit(2);
    }
}
