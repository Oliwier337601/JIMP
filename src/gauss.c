#include "gauss.h"

double mfabs(double d){ return (d >= 0) ? d : -d;}

int main_elem(Matrix *mat, int col, int start){
    int row = 0;
    for (int r = start; r < mat->r; r++)
        if (mfabs(mat->data[r][col]) > mfabs(mat->data[row][col])) row = r;
    return row;
}

void row_switch(Matrix *matA, Matrix *matB, int row1, int row2){
    double *temp = matA->data[row1];
    matA->data[row1] = matA->data[row2];
    matA->data[row2] = temp;
    
    temp = matB->data[row1];
    matB->data[row1] = matB->data[row2];
    matB->data[row2] = temp;
}

void operation(Matrix *matA, Matrix *matB, int diag){
    for (int row = diag + 1; row < matA->r; row++){
        double mult = matA->data[row][diag] / matA->data[diag][diag];
        for (int col = diag; col < matA->c; col++)
            matA->data[row][col] -= matA->data[diag][col] * mult;
        matB->data[row][0] -= matB->data[diag][0] * mult;
    }
}

void get_cof(Matrix *mat, Matrix *temp, int p, int q){
    int i = 0, j = 0;
    for (int row = 0; row < mat->r; row++){
        for (int col = 0; col < mat->r; col++){
            if (row != p && col != q) {
                temp->data[i][j++] = mat->data[row][col];
                if (j == mat->r - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double det_matrix(Matrix *mat){
    if (mat->r == 1)
        return mat->data[0][0];

    double det = 0;
    int sign = 1;

    Matrix *temp;
    temp = createMatrix(mat->r - 1, mat->r - 1);

    for (int f = 0; f < mat->r; f++){
        get_cof(mat, temp, 0, f);
        det += sign * mat->data[0][f] * det_matrix(temp);
        sign = -sign;
    }
    freeMatrix(temp);

    return det;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    double det = det_matrix(mat);
    if (det_matrix(mat) == 0)
        return 1;
    
    int col = 0;
    for (int row = 0; row < mat->r; row++){
        int elem_row = main_elem(mat, col, row);
        if (elem_row != 0){
            row_switch(mat, b, row, elem_row);
        }
        operation(mat, b, row);
    }
    return 0;
}

