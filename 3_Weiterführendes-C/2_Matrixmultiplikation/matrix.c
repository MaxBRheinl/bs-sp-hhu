#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define A_ROWS 3
#define A_COLS 2
#define B_ROWS A_COLS
#define B_COLS A_ROWS

#define getAddress(matrix_pointer, current_row, current_column, columns) \
    (matrix_pointer + current_row * columns + current_column)

void initializeMatrix(uint64_t *matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            *getAddress(matrix, row, col, cols) = rand() % 100;
        }
    }
}

void initializeMatrixZeros(uint64_t *matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            *getAddress(matrix, row, col, cols) = 0;
        }
    }
}

void print_matrix(uint64_t *matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%ld ", *getAddress(matrix, row, col, cols));
        }
        printf("\n");
    }
}

void multiplyMatrices(uint64_t *a_mat, uint64_t *b_mat, uint64_t *c_mat) {
    for (int i = 0; i < A_ROWS; i++) {
        for (int j = 0; j < B_COLS; j++) {
            for (int k = 0; k < A_COLS; k++) {
                *getAddress(c_mat, i, j, B_COLS) += *getAddress(a_mat, i, k, A_COLS) * *getAddress(b_mat, k, j, B_COLS);
            }
        }
    }
}

int main() {
    uint64_t *a_mat = malloc(A_ROWS * A_COLS * sizeof(uint64_t));
    if (a_mat == NULL) {
        printf("ERROR: Allokation fehlgeschlagen.\n");
        exit(EXIT_FAILURE);
    }
    uint64_t *b_mat = malloc(B_ROWS * B_COLS * sizeof(uint64_t));
    if (b_mat == NULL) {
        printf("ERROR: Allokation fehlgeschlagen.\n");
        exit(EXIT_FAILURE);
    }
    uint64_t *c_mat = malloc(A_ROWS * B_COLS * sizeof(uint64_t));
    if (c_mat == NULL) {
        printf("ERROR: Allokation fehlgeschlagen.\n");
        exit(EXIT_FAILURE);
    }

    initializeMatrix(a_mat, A_ROWS, A_COLS);
    printf("A:\n");
    print_matrix(a_mat, A_ROWS, A_COLS);
    initializeMatrix(b_mat, B_ROWS, B_COLS);
    printf("B:\n");
    print_matrix(b_mat, B_ROWS, B_COLS);

    initializeMatrixZeros(c_mat, A_ROWS, B_COLS);
    multiplyMatrices(a_mat, b_mat, c_mat);
    printf("C:\n");
    print_matrix(c_mat, A_ROWS, B_COLS);

    free(a_mat);
    free(b_mat);
    free(c_mat);

    exit(EXIT_SUCCESS);
}
