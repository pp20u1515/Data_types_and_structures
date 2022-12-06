#include "../inc/io_funcs.h"
#include "../inc/struct.h"
#include "../inc/return_codes.h"

#include <stdlib.h>
#include <time.h>

size_t input_matrix_dimension(int *rows, int *columns)
{
    printf("\t\tВведите количество строк матрицы: ");
    if (scanf("%d", rows) != 1 || *rows <= 0)
    {
        return IO_ERROR;
    }
    printf("\t\tВведите количество столбцов матрицы: ");
    if (scanf("%d", columns) != 1 || *columns <= 0)
        return IO_ERROR;

    return OK;
}

size_t input_matrix_dimension2(int *second_rows, int *second_columns, const int first_rows, const int first_columns)
{
    printf("\t\tВведите количество строк матрицы: ");
    if (scanf("%d", second_rows) != 1 || *second_rows <= 0 || *second_rows != first_rows)
        return IO_ERROR;

    printf("\t\tВведите количество столбцов матрицы: ");
    if (scanf("%d", second_columns) != 1 || *second_columns <= 0 || *second_columns != first_columns)
        return IO_ERROR;

    return OK;
}

size_t input_matrix_default_format(matrix_t *matrix, int *number_nonzero_el)
{
    printf("\t\tВведите количество ненулевых элементов матрицы: ");
    if (scanf("%d", number_nonzero_el) != 1)
        return IO_ERROR;
    
    if (*number_nonzero_el > matrix->rows * matrix->columns || *number_nonzero_el < 1)
        return IO_ERROR;

    matrix->data = calloc(matrix->rows * matrix->columns, sizeof(int));

    for (int count = 0, i, j, val; count < *number_nonzero_el; count++)
    {
        printf("\t\tВведите номер строки и столбца и элемент матрицы: ");
        if (scanf("%d", &i) != 1)
            return IO_ERROR;
        
        if (i >= matrix->rows)
            return IO_ERROR;
            
        if (scanf("%d", &j) != 1)
            return IO_ERROR;

        if (j >= matrix->columns)
            return IO_ERROR;

        if (scanf("%d", &val) != 1)
            return IO_ERROR;

        if (val == 0)
            return IO_ERROR;

        matrix->data[i * matrix->columns + j] = val;
    }

    return OK;
}

void print_matrix_default_format(const matrix_t matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            printf("%4d", *(matrix.data + i * matrix.columns + j));
        }
        printf("\n");
    }
    printf("\n\n");
}

void print_matrix_sparse_format(sparse_matrix_t result_sparse_matrix)
{
    printf("\tМатрица в разреженой форме:\n\n");
    printf(" A = [ ");
    for (; result_sparse_matrix.a < result_sparse_matrix.pa; result_sparse_matrix.a++)
    {
        if (result_sparse_matrix.a == 0)
            continue;
        else
            printf("%d ", *result_sparse_matrix.a);
    }
    printf("]\n");

    printf("IA = [ ");
    for (; result_sparse_matrix.ai < result_sparse_matrix.pai; result_sparse_matrix.ai++)
    {
        printf("%d ", *result_sparse_matrix.ai);
    }
    printf("]\n");

    printf("JA = [ ");
    for (; result_sparse_matrix.aj < result_sparse_matrix.paj; result_sparse_matrix.aj++)
    {
        printf("%d ", *result_sparse_matrix.aj);
    }
    printf("]\n");
}

size_t matrix_generate(matrix_t *matrix, int *number_nonzero_el)
{
    float procent_matrix_sparse;

    printf("\t\tВведите процент разреженности матрицы (от 1 до 99): ");

    if (scanf("%f", &procent_matrix_sparse) != 1)
        return MATRIX_GENERATE_ERROR;

    if (procent_matrix_sparse <= 0 || procent_matrix_sparse > 99)
        return MATRIX_GENERATE_ERROR;

    matrix->data = calloc(matrix->rows * matrix->columns, sizeof(int));

    *number_nonzero_el = (matrix->rows * matrix->columns) - (procent_matrix_sparse / 100 * matrix->rows * matrix->columns);
    
    srand(time(NULL));
    for (int i = 0, row, column; i < *number_nonzero_el; i++)
    {
        row = rand() % matrix->rows;
        column = rand() % matrix->columns;
        
        while (*(matrix->data + row * matrix->columns + column) != 0)
        {
            row = rand() % matrix->rows;
            column = rand() % matrix->columns;
        }
        *(matrix->data + row * matrix->columns + column) = rand() % 100 + 1;  
    }

    return OK;
}

void condition()
{
    printf("\n\n\t\tРазреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:\n\
            \t- массив A содержит значения ненулевых элементов;\n\
            \t- массив IA содержит номера строк для элементов вектора A;\n\
            \t- массив JA, в элементе Nk которого находится номер компонент\n\
            \t  в A и IA, с которых начинается описание столбца Nk матрицы A.\n\n");
}

void menu(void)
{
    printf("\n\n                                 МЕНЮ \n\n");
    printf("\t\t1  - Ввести две матрицы с клавиатуры.\n");
    printf("\t\t2  - Сгенерировать две матрицы с заданным процентом разреженности.\n");
    printf("\t\t3  - Сложить две матрицы.\n");
    printf("\t\t4  - Вывести две матрицы.\n");
    printf("\t\t5  - Сравнить время выполнения операций и объем памяти при сложении матриц в разных форматах\n");
    printf("\t\t0  - Выйти\n\n");
    printf("\n\t\tВыберите действие: ");
}

void print_error(const int error_code)
{
    if (error_code == IO_ERROR)
        printf("\t\tОшибка: вы ввели матрицу некорректно!");

    if (error_code == EMPTY_MATRIX_ERROR)
        printf("\t\tОшибка: вы не ввели матрицы!");

    if (error_code == MENU_NUMBER_ERROR)
        printf("\t\tОшибка: вы ввели неверный пункт меню");
        
    if (error_code == MATRIX_GENERATE_ERROR)
        printf("\t\tОшибка: вы ввели неверные данные для генерации матрицы");
}

void init_matrix(matrix_t *matrix)
{
    matrix->data = NULL;
    matrix->rows = 0;
    matrix->columns = 0;
}

void init_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
    sparse_matrix->a = NULL;
    sparse_matrix->ai = NULL;
    sparse_matrix->aj = NULL;
}
