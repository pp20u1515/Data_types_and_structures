#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include <stdio.h>
#include "struct.h"

/**
 * @brief condition - Условие задачи 
 * 
 */
void condition();

/**
 * @brief menu - Меню 
 * 
 */
void menu(void);

/**
 * @brief print_error - Вывод код ошибки
 * 
 * @param error_code 
 */
void print_error(const int error_code);

/**
 * @brief input_matrix_default_format - Ввод элементов матрицы
 * 
 * @param matrix Структура матрицы
 * @param number_nonzero_el Количество ненулевых элементов
 * @return Код успеха или код ошибки
 */
size_t input_matrix_default_format(matrix_t *matrix, int *number_nonzero_el);

/**
 * @brief print_matrix_default_format - Вывод матрицы в обычную форму
 * 
 * @param matrix Структура матрицы
 */
void print_matrix_default_format(const matrix_t matrix);

/**
 * @brief print_matrix_sparse_format - Вывод матрицы в разреженную форму
 * 
 * @param result_sparse_matrix Структура разреженной матрицы
 */
void print_matrix_sparse_format(sparse_matrix_t result_sparse_matrix);

/**
 * @brief input_matrix_dimension2 - Ввод размер второй матрицы
 * 
 * @param second_rows Количество строк второй матрицы
 * @param second_columns Количество столбцов второй матрицы
 * @param first_rows Количество строк первой матрицы
 * @param first_columns Количество столбцов первой матрицы
 * @return Код успеха или код ошибки
 */
size_t input_matrix_dimension2(int *second_rows, int *second_columns, const int first_rows, const int first_columns);

/**
 * @brief input_matrix_dimension - Ввод размер первой матрицы
 * 
 * @param rows Количество строк матрицы
 * @param columns Количество столбцов матрицы
 * @return Код ошибки или код успеха
 */
size_t input_matrix_dimension(int *rows, int *columns);

/**
 * @brief matrix_generate - Функция, которая автоматически заполняет матрицы
 * 
 * @param matrix Структура матрицы
 * @param number_nonzero_el Количество ненулевых элементов
 * @return Код ошибки или код успеха
 */
size_t matrix_generate(matrix_t *matrix, int *number_nonzero_el);

/**
 * @brief init_matrix - Функция, которая инициализирует матрицу
 * 
 * @param matrix Структура матрицы
 */
void init_matrix(matrix_t *matrix);

void init_sparse_matrix(sparse_matrix_t *sparse_matrix);

#endif // IO_FUNCS_H
