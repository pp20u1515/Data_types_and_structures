#include "graph_funcs.h"
#include "io_funcs.h"
#include "return_codes.h"

#include <stdlib.h>
#include <time.h>

matrix_t *create_matrix(const size_t amount_node)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    
    if (matrix)
    {
        matrix->amount_node = amount_node;

        matrix->data = allocate_matrix(amount_node);
        if (matrix->data == NULL)
        {
            free(matrix);
            matrix = NULL;
        }
    }

    return matrix;
}

double **allocate_matrix(const size_t amount_node)
{
    double **data = calloc(amount_node, sizeof(double*));

    if (data)
        for (size_t index = 0; index < amount_node; index++)
        {
            data[index] = calloc(amount_node, sizeof(double));

            if (data[index] == NULL)
            {
                free_matrix(data, amount_node);
                data = NULL;
            }
        }

    return data;
}

void free_matrix(double **data, const size_t amount_node)
{
    for (size_t index = 0; index++ < amount_node; index++)
        free(data[index]);

    free(data);
}

void timeget()
{
    printf("\nПроизводится сравнение времени работы и памяти, \nзатраченной на работу, ");
    printf("алгоритма Дейкстры\n");
    printf("\n__________________________________\n");
    printf("| Кол-во |   Время    |   Память |\n");
    printf("|________|____________|__________|\n");
    clock_t start, end;

    matrix_t *g4 = NULL;
    read_graph(&g4, "./func_tests/data/in_10.txt");
    double arr4[g4->amount_node];
    start = clock();
    Dijkstra(g4, arr4, 0);
    end = clock();
    printf("| %6d |  %5f  |  %7zu |\n", 10, (end - start) / (CLOCKS_PER_SEC * 1.0), sizeof(double) * (g4->amount_node * g4->amount_node) + sizeof(matrix_t));
    printf("|________|____________|__________|\n");

    matrix_t *g3 = NULL;
    read_graph(&g3, "./func_tests/data/in_50.txt");
    double arr3[g3->amount_node];
    start = clock();
    Dijkstra(g3, arr3, 0);
    end = clock();
    printf("| %6d |  %5f  |  %7zu |\n", 50, (end - start) / (CLOCKS_PER_SEC * 1.0), sizeof(double) * (g3->amount_node * g3->amount_node) + sizeof(matrix_t));
    printf("|________|____________|__________|\n");

    matrix_t *g2 = NULL;
    read_graph(&g2, "./func_tests/data/in_100.txt");
    double arr2[g2->amount_node];
    start = clock();
    Dijkstra(g2, arr2, 0);
    end = clock();
    printf("| %6d |  %5f  |  %7zu |\n", 100, (end - start) / (CLOCKS_PER_SEC * 1.0), sizeof(double) * (g2->amount_node * g2->amount_node) + sizeof(matrix_t));
    printf("|________|____________|__________|\n");

    matrix_t *g1 = NULL;
    read_graph(&g1, "./func_tests/data/in_500.txt");
    double arr1[g1->amount_node];
    start = clock();
    Dijkstra(g1, arr1, 0);
    end = clock();
    printf("| %6d |  %5f  |  %7zu |\n", 500, (end - start) / (CLOCKS_PER_SEC * 1.0), sizeof(double) * (g1->amount_node * g1->amount_node) + sizeof(matrix_t));
    printf("|________|____________|__________|\n");
}
