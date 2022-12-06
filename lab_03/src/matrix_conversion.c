#include "../inc/matrix_conversion.h"
#include "../inc/struct.h"

#include <stdlib.h>

void default_to_sparse(const matrix_t matrix, const int number_nonzero_el, \
sparse_matrix_t *sparse_matrix)
{
    sparse_matrix->a = malloc(number_nonzero_el * sizeof(int));
    sparse_matrix->ai = malloc(number_nonzero_el * sizeof(int));
    sparse_matrix->aj = malloc((matrix.columns + 1) * sizeof(int));

    int a_ind = 0, ja_ind = 0;

    *(sparse_matrix->aj + ja_ind) = 0;
    ja_ind++;

    for (int i = 0; i < matrix.columns; i++)
    {
        for (int j = 0; j < matrix.rows; j++)
        {
            if (*(matrix.data + j * matrix.columns + i) != 0)
            {
                *(sparse_matrix->a + a_ind) = *(matrix.data + j * matrix.columns + i);
                *(sparse_matrix->ai + a_ind) = j;
                a_ind++;
            }
        }
        *(sparse_matrix->aj + ja_ind) = a_ind;
        ja_ind++;
    }
    
    sparse_matrix->pa = sparse_matrix->a + a_ind;
    sparse_matrix->pai = sparse_matrix->ai + a_ind;
    sparse_matrix->paj = sparse_matrix->aj + ja_ind;
}

void free_all(matrix_t first_matrix, matrix_t second_matrix, matrix_t result_matrix,\
sparse_matrix_t first_sparse_matrix, sparse_matrix_t second_sparse_matrix, sparse_matrix_t result_sparse_matrix)
{
    if (first_matrix.data)
        free(first_matrix.data);

    if (second_matrix.data)
        free(second_matrix.data);

    if (result_matrix.data)
        free(result_matrix.data);

    if (first_sparse_matrix.a)
        free(first_sparse_matrix.a);

    if (first_sparse_matrix.ai)
        free(first_sparse_matrix.ai);

    if (first_sparse_matrix.aj)
        free(first_sparse_matrix.aj);

    if (second_sparse_matrix.a)
        free(second_sparse_matrix.a);

    if (second_sparse_matrix.ai)
        free(second_sparse_matrix.ai);

    if (second_sparse_matrix.aj)
        free(second_sparse_matrix.aj);

    if (result_sparse_matrix.a)
        free(result_sparse_matrix.a);

    if (result_sparse_matrix.ai)
        free(result_sparse_matrix.ai);

    if (result_sparse_matrix.aj)
        free(result_sparse_matrix.aj);
}