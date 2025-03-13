#include <stdint.h>
#include <stdlib.h>
#include "matrix.h"

#define getAddress(matrix_pointer, current_row, current_column, columns) \
    (matrix_pointer + current_row * columns + current_column)
    
void initializeMatrix(uint64_t *matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            *getAddress(matrix, row, col, cols) = rand() % 100;
        }
    }
}    

void multiplyMatrices(uint64_t *a_mat, uint64_t *b_mat, uint64_t *c_mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                *getAddress(c_mat, i, j, rows) += *getAddress(a_mat, i, k, cols) * *getAddress(b_mat, k, j, rows);
            }
        }
    }
}
