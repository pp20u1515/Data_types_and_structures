#ifndef MATRIX_SUM_H
#define MATRIX_SUM_H

#include <time.h>
#include <stdlib.h>

#include "struct.h"

/**
 * @brief default_matrix_sum - Сложение двух матриц в обычную форму
 * 
 * @param first_matrix Структура первой матрицы
 * @param second_matrix Структура второй матрицы
 * @param result Структура результурующей матрицы
 */
void default_matrix_sum(const matrix_t first_matrix, const matrix_t second_matrix, matrix_t *result);

/**
 * @brief sparse_matrix_sum - Сложение двух матриц в разреженную форму
 * 
 */
void sparse_matrix_sum(sparse_matrix_t *sparse_result_matrix, const sparse_matrix_t sparse_first_matrix, \
const sparse_matrix_t sparse_second_matrix, const int number_nonzero_el1, \
const int number_nonzero_el2, const int columns, clock_t *ts, clock_t *te);

#endif // MATRIX_SUM_H
