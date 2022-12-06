#include "../inc/io_funcs.h"
#include "../inc/matrix_conversion.h"
#include "../inc/matrix_sum.h"
#include "../inc/struct.h"
#include "../inc/return_codes.h"

#include <time.h>
#include <string.h>
#include <stdio.h>

#define ANSWER_LEN 3

int main(void)
{
    matrix_t first_matrix, second_matrix, result_matrix;
    sparse_matrix_t first_sparse_matrix, second_sparse_matrix, result_sparse_matrix;
    int num_nonzero_elem1 = 0, num_nonzero_elem2 = 0;
    clock_t ts, te;

    init_matrix(&first_matrix);
    init_matrix(&second_matrix);
    init_matrix(&result_matrix);

    init_sparse_matrix(&first_sparse_matrix);
    init_sparse_matrix(&second_sparse_matrix);
    init_sparse_matrix(&result_sparse_matrix);
    
    int menu_number = -1;
    char answer_char[ANSWER_LEN];

    condition();

    while (menu_number != 0)
    {
        menu();
        scanf("%s", answer_char);
        menu_number = atoi(answer_char);

        while (!menu_number)
        {
            if (strcmp(answer_char, "0") == 0)
                break;

            print_error(MENU_NUMBER_ERROR);

            scanf("%s", answer_char);
            menu_number = atoi(answer_char);
        }

        if (menu_number == 1)
        {
            if (first_matrix.data != NULL || second_matrix.data != NULL)
            {
                free(first_matrix.data);
                free(second_matrix.data);
            }

            printf("\n\t\tВведите первую матрицу:\n");
            
            if (input_matrix_dimension(&first_matrix.rows, &first_matrix.columns) != OK)
            {
                print_error(IO_ERROR);
                continue;
            }
            if (input_matrix_default_format(&first_matrix, &num_nonzero_elem1) != OK)
            {
                print_error(IO_ERROR);

                if (first_matrix.data)
                    free(first_matrix.data);
                
                first_matrix.data = NULL;
                continue;
            }
            printf("\n\t\tВведите вторую матрицу:\n");
            
            if (input_matrix_dimension2(&second_matrix.rows, &second_matrix.columns, \
            first_matrix.rows, first_matrix.columns) != OK)
            {
                print_error(IO_ERROR);
                
                if (first_matrix.data)
                    free(first_matrix.data);

                first_matrix.data = NULL;
                continue;
            }
            if (input_matrix_default_format(&second_matrix, &num_nonzero_elem2) != OK || \
            first_matrix.columns != second_matrix.columns || first_matrix.rows != second_matrix.rows || \
            (num_nonzero_elem1 == 0 && num_nonzero_elem2 == 0))
            {
                print_error(IO_ERROR);

                if (first_matrix.data)
                    free(first_matrix.data);
                
                if (second_matrix.data)
                    free(second_matrix.data);
                
                first_matrix.data = NULL;
                second_matrix.data = NULL;
                continue;
            }
            default_to_sparse(first_matrix, num_nonzero_elem1, &first_sparse_matrix);
            default_to_sparse(second_matrix, num_nonzero_elem2, &second_sparse_matrix);
            continue;
        }
        else if (menu_number == 2)
        {
            if (first_matrix.data != NULL || second_matrix.data != NULL)
            {
                free(first_matrix.data);
                free(second_matrix.data);
                free(first_sparse_matrix.a);
                free(first_sparse_matrix.ai);
                free(first_sparse_matrix.aj);
                free(second_sparse_matrix.a);
                free(second_sparse_matrix.ai);
                free(second_sparse_matrix.aj);
                
            }

            printf("\n\t\tГенерирование первой матрицы:\n");

            if (input_matrix_dimension(&first_matrix.rows, &first_matrix.columns) != OK)
            {
                print_error(IO_ERROR);
                continue;
            }
            if (matrix_generate(&first_matrix, &num_nonzero_elem1) != OK)
            {
                print_error(MATRIX_GENERATE_ERROR);
                
                if (first_matrix.data)
                    free(first_matrix.data);
                
                first_matrix.data = NULL;
                continue;
            }
            printf("\n\t\tГенерирование второй матрицы:\n");
            
            if (input_matrix_dimension2(&second_matrix.rows, &second_matrix.columns, \
            first_matrix.rows, first_matrix.columns) != OK)
            {
                print_error(IO_ERROR);

                if (first_matrix.data)
                    free(first_matrix.data);

                first_matrix.data = NULL;
                continue;
            }
            if (matrix_generate(&second_matrix, &num_nonzero_elem2) != OK || \
            first_matrix.columns != second_matrix.columns || first_matrix.rows != second_matrix.rows)
            {
                print_error(MATRIX_GENERATE_ERROR);
                
                if (first_matrix.data)
                    free(first_matrix.data);

                if (second_matrix.data)
                    free(second_matrix.data);
                
                first_matrix.data = NULL;
                second_matrix.data = NULL;
                continue;
            }
            default_to_sparse(first_matrix, num_nonzero_elem1, &first_sparse_matrix);
            default_to_sparse(second_matrix, num_nonzero_elem2, &second_sparse_matrix);
            continue;
        }
        else if (menu_number == 3)
        {
            if (first_matrix.data == NULL || second_matrix.data == NULL)
            {
                print_error(EMPTY_MATRIX_ERROR);
                continue;
            }
            default_matrix_sum(first_matrix, second_matrix, &result_matrix);

            printf("\n\t\tРезультат сложения матриц:\n");
            print_matrix_default_format(result_matrix);

            sparse_matrix_sum(&result_sparse_matrix, first_sparse_matrix, second_sparse_matrix, \
            num_nonzero_elem1, num_nonzero_elem2, first_matrix.rows, &ts, &te);
            
            printf("\n\t\tРезультат сложения матриц:\n");
            
            print_matrix_sparse_format(result_sparse_matrix);
            continue;

        }
        else if (menu_number == 4)
        {
            if (first_matrix.data == NULL || second_matrix.data == NULL)
            {
                print_error(EMPTY_MATRIX_ERROR);
                continue;
            }
            printf("\n\t\tВывод первой матрицы:\n");
            print_matrix_default_format(first_matrix);
            print_matrix_sparse_format(first_sparse_matrix);

            printf("\n\t\tВывод второй матрицы:\n");
            print_matrix_default_format(second_matrix);
            print_matrix_sparse_format(second_sparse_matrix);
            continue;
        }
        else if (menu_number == 5)
        {
            if (first_matrix.data == NULL || second_matrix.data == NULL)
            {
                print_error(EMPTY_MATRIX_ERROR);
            }
            else
            {
                printf("\n\t\tСтолбцовый формат\n");
                printf("\t\tСкорость работы (секунды): ");
                sparse_matrix_sum(&result_sparse_matrix, first_sparse_matrix, second_sparse_matrix,\
                num_nonzero_elem1, num_nonzero_elem2, first_matrix.rows, &ts, &te);
                printf("%lf sec\n", ((te - ts) / 2) / (CLOCKS_PER_SEC * 1.0));
                printf("\t\tОбъем памяти (байты): ");
                printf("%lu\n", (result_sparse_matrix.pa - result_sparse_matrix.a) * sizeof(int) + (result_sparse_matrix.pai - result_sparse_matrix.ai) * sizeof(int) + (result_sparse_matrix.paj - result_sparse_matrix.aj) * sizeof(int) + (first_sparse_matrix.pa - first_sparse_matrix.a) * sizeof(int) + (first_sparse_matrix.pai - first_sparse_matrix.ai) * sizeof(int) + (first_sparse_matrix.paj - first_sparse_matrix.aj) * sizeof(int) + (second_sparse_matrix.pa - second_sparse_matrix.a) * sizeof(int) + (second_sparse_matrix.pai - second_sparse_matrix.ai) * sizeof(int) + (second_sparse_matrix.paj - second_sparse_matrix.aj) * sizeof(int));
                printf("\n\t\tСтандартный формат\n");
                printf("\t\tСкорость работы (секунды): ");
                ts = clock();
                default_matrix_sum(first_matrix, second_matrix, &result_matrix);
                te = clock();
                printf("%lf sec\n", (te - ts) / (CLOCKS_PER_SEC * 1.0));
                printf("\t\tОбъем памяти (байты): ");
                printf("%lu\n", result_matrix.rows * result_matrix.columns * sizeof(int) + first_matrix.rows * first_matrix.columns * sizeof(int) + second_matrix.rows * second_matrix.columns * sizeof(int));
            }
        }
        else if (menu_number == 0)
        {
            printf("\tПрограмма завершена!\n");
            return OK;
        }
        else
            print_error(IO_ERROR);
    }

    return OK;
}
