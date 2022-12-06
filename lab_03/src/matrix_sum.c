#include "../inc/matrix_sum.h"
#include "../inc/struct.h"

void default_matrix_sum(const matrix_t first_matrix, const matrix_t second_matrix, matrix_t *result)
{
    result->rows = first_matrix.rows;
    result->columns = first_matrix.columns;
    result->data = malloc(first_matrix.rows * first_matrix.columns * sizeof(int));

    for (int i = 0; i < first_matrix.rows; i++)
    {
        for (int j = 0; j < first_matrix.columns; j++) 
        {
            result->data[i * result->columns + j] = first_matrix.data[i * first_matrix.columns + j] +\
            second_matrix.data[i * second_matrix.columns + j];
        }
    }
}

void sparse_matrix_sum(sparse_matrix_t *sparse_result_matrix, const sparse_matrix_t sparse_first_matrix, \
const sparse_matrix_t sparse_second_matrix, const int number_nonzero_el1, \
const int number_nonzero_el2, const int columns, clock_t *ts, clock_t *te)
{
    sparse_result_matrix->a = malloc((number_nonzero_el1 + number_nonzero_el2) * sizeof(int));
    sparse_result_matrix->ai = malloc((number_nonzero_el1 + number_nonzero_el2) * sizeof(int));
    sparse_result_matrix->aj = malloc((columns + 1) * sizeof(int));

    int size = 0, js_size = 0;
    int check = 0;

    *(sparse_result_matrix->aj + js_size) = 0;
    js_size++;
    *ts = clock();

    for(int i = 1; i < sparse_first_matrix.paj - sparse_first_matrix.aj; i++)
    {
        for(int j = *(sparse_first_matrix.aj + i - 1); j < *(sparse_first_matrix.aj + i); j++)
        {
            check = 0;
            
            for(int k = *(sparse_second_matrix.aj + i - 1); k < *(sparse_second_matrix.aj + i); k++)
            {
                if ((*(sparse_first_matrix.ai + j) == *(sparse_second_matrix.ai + k)) && ((*(sparse_first_matrix.a + j) + *(sparse_second_matrix.a + k)) != 0))
                {
                    sparse_result_matrix->a[size] = *(sparse_first_matrix.a + j) + *(sparse_second_matrix.a + k);
                    sparse_result_matrix->ai[size] = *(sparse_first_matrix.ai + j);
                    size += 1;
                    check = 1;
                }
                else if ((*(sparse_first_matrix.ai + j) == *(sparse_second_matrix.ai + k)) && ((*(sparse_first_matrix.a + j) + *(sparse_second_matrix.a + k)) == 0))
                    check = 1;
            }
            if (check == 0)
            {
                sparse_result_matrix->a[size] = *(sparse_first_matrix.a + j);
                sparse_result_matrix->ai[size] = *(sparse_first_matrix.ai + j);
                size += 1;
            }
        }
        for(int k = *(sparse_second_matrix.aj + i- 1); k < *(sparse_second_matrix.aj + i); k++)
        {
            check = 0;
            
            for(int j = *(sparse_first_matrix.aj + i - 1); j < *(sparse_first_matrix.aj + i); j++)
            {
                if (*(sparse_first_matrix.ai + j) != *(sparse_second_matrix.ai + k) || ((*(sparse_first_matrix.a + j) + *(sparse_second_matrix.a + k)) == 0))
                {
                    check = 1;
                }
            }
            if (check == 0)
            {
                sparse_result_matrix->a[size] = *(sparse_second_matrix.a + k);
                sparse_result_matrix->ai[size] = *(sparse_second_matrix.ai + k);
                size += 1;
            }
        }
        
        sparse_result_matrix->aj[js_size] = size;
        js_size++;
    }
    *te = clock();

    sparse_result_matrix->pa = sparse_result_matrix->a + size;
    sparse_result_matrix->pai = sparse_result_matrix->ai + size;
    sparse_result_matrix->paj = sparse_result_matrix->aj + js_size;
}