#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {

	if (mat->r != mat->c) return 2;

	Matrix * temp = createMatrix(mat->r, 1);
	int row;
	for (row = mat->r - 1; row >= 0; row--)
	{
		if (mat->data[row][row] == 0)
		{
			freeMatrix(temp);
			return 1;
		}

		double res = b->data[row][0];
		int col;
		for (col = row + 1; col < mat->c; col++)
		{
			res -= temp->data[col][0] * mat->data[row][col];
		}
		res /= mat->data[row][row];
		temp->data[row][0] = res;
	
	}

	int i;
	for (i =0; i < x->r; i++) 
	{
		x->data[i][0] = temp->data[i][0];
	}
	freeMatrix(temp);
	return 0;
}


