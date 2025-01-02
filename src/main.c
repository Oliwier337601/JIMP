#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv) {
	int ress;
	Matrix *A = readFromFile(argv[1]);
	Matrix *b = readFromFile(argv[2]);
	Matrix *x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	ress = eliminate(A, b);
    if (ress == 1) {
        fprintf(stderr, "Błąd! Macierz osobliwa.\n");
        return 1;
    }
    
	x = createMatrix(b->r, 1);
    if (x == NULL) {
        fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        return 1;
    }
    
    ress = backsubst(x, A, b);
    if (ress == 1) {
        fprintf(stderr, "Błąd! Dzielenie przez 0.\n");
        return 1;
    } else if (ress == 2) {
        fprintf(stderr,"Błąd! Macierz nie jest kwadratowa.\n");
        return 1;
    }

    printToScreen(x);
    freeMatrix(x);

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
