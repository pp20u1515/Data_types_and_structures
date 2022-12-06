#ifndef MATRIX_CONVERISON_H
#define MATRIX_CONVERISON_H

#include <stdio.h>

#include "struct.h"

/**
 * @brief default_to_sparse - Функция, заполняющая матрицу в разреженную форму
 * 
 */
void default_to_sparse(const matrix_t matrix, const int number_nonzero_el, \
sparse_matrix_t *sparse_matrix);

/**
 * @brief free_all - Функция, которая освобождает выделенную память 
 * 
 */
void free_all(matrix_t first_matrix, matrix_t second_matrix, matrix_t result_matrix,\
sparse_matrix_t first_sparse_matrix, sparse_matrix_t second_sparse_matrix, sparse_matrix_t result_sparse_matrix);

#endif // MATRIX_CONVERISON_H
