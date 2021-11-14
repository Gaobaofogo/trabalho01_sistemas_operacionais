##
# Programa Auxiliar
#
# @file
# @version 0.1

all: main
	cppcheck . --enable=all --inconclusive --suppress=missingIncludeSystem

main: aux.o matrix.o
	gcc -o prog aux.o matrix.o

matrix.o: matrix.c
	gcc -o matrix.o matrix.c -c -Wall -pedantic

aux.o: aux.c
	gcc -o aux.o aux.c -c -Wall -pedantic

clean-all: clean-matrix clean-trash
	rm -rf prog

clean-matrix:
	rm -rf *.txt

clean-trash:
	rm -rf *.o *~


# end
