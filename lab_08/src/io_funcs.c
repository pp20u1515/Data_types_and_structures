#include "io_funcs.h"
#include "graph_funcs.h"
#include "struct.h"
#include "return_codes.h"

#include <limits.h>

void menu()
{
    printf("\n\t\t\tМеню\n\n\
        1) Загрузить граф из файла.\n\
        2) Вывести граф.\n\
        3) Вывести матрицу графа.\n\
        4) Найти все вершины графа, к которым от заданной вершины можно добраться по\n\
            пути не длиннее А.\n\
        5) Вывести сравнительную характеристику.\n\
        0) Выйти из программы.\n");
}

size_t input_data(matrix_t **matrix, FILE *f_open)
{
    size_t rc = OK;

    for (size_t index_i = 0; rc == OK && index_i < (*matrix)->amount_node; index_i++)
        for (size_t index_j = 0; rc == OK && index_j < (*matrix)->amount_node; index_j++)
            if (fscanf(f_open, "%lf", &(*matrix)->data[index_i][index_j]) != 1)
                rc = DATA_ERROR;
    
    return rc;
}

void read_graph(matrix_t **graph, const char *file_name)
{
    size_t node_amount; // количество вершин графа
    matrix_t *matrix = NULL;
    size_t rc = OK;
    FILE *f_open = fopen(file_name, "r");

    if (f_open && fscanf(f_open, "%zu", &node_amount) == 1)
    {
        matrix = create_matrix(node_amount);

        if (matrix)
        {
            rc = input_data(&matrix, f_open);

            if (rc == OK)
                *graph = matrix;
            else
            {
                printf("\tОшибка: Некоректные входные данные!\n");
                free_matrix(matrix->data, matrix->amount_node);
            }
        }
        else
            printf("\tОшибка: Не удалось выделить память под матрицой!\n");
    }
    else if (f_open == NULL)
        printf("\tОшибка: Не удалось открыть файл!\n");
    else
        printf("\tОшибка: Неправильно указали кoличество вершин графа!\n");

    if (f_open)
        fclose(f_open);
}

void print_matrix(matrix_t *graph)
{
    for (size_t index_i = 0; index_i < graph->amount_node; index_i++)
        for (size_t index_j = 0; index_j < graph->amount_node; index_j++)
            printf("%6.2lf%c", graph->data[index_i][index_j], index_j < graph->amount_node - 1 ? ' ' : '\n');
}

void to_dot(matrix_t *graph, const char *file_name)
{
    FILE *f_write = fopen(file_name, "w");

    fprintf(f_write, "digraph my_graph {\n");

    for (size_t index_i = 0; index_i < graph->amount_node; index_i++)
        for (size_t index_j = 0; index_j < graph->amount_node; index_j++)
            if (graph->data[index_i][index_j] != 0)
                fprintf(f_write, "%zu -> %zu [label=\"%.1f\"];\n", index_i, index_j, graph->data[index_i][index_j]);

    fprintf(f_write, "}\n");
    fclose(f_write);
}

size_t get_top_and_way(size_t *top, double *min_way, matrix_t *graph)
{
    size_t rc = OK;

    printf("\nВведите ключевую вершину (номер): ");
    if (scanf("%zu", top) == 1 && *top < graph->amount_node)
    {
        printf("\nВведите максимальную длину А: ");
        if (scanf("%lf", min_way) != 1 && *min_way <= 0)
        {
            printf("Число должно быть неотрицательным.\n");
            rc = DATA_ERROR;
        }
    }
    else
    {
        printf("Неверный номер.\n");
        rc = DATA_ERROR;
    }
    
    return rc;
}

void Dijkstra(matrix_t *graph, double *distance, int top)
{
    int visited[graph->amount_node];
    size_t buf = 0;

    // в самом начале все вершины обозначаются как непосещены с помощью добавления
    // максимальное целое число, а самой первой вершины присваивается ноль
    for (size_t index = 0; index < graph->amount_node; index++)
    {
        distance[index] = INT_MAX;
        visited[index] = 0; 
    }

    distance[top] = 0; // первая вершина равна нулю

    // проверяются все вершины, кроме начальной
    for (size_t count = 0; count < graph->amount_node - 1; count++)
    {
        int min = INT_MAX;

        for (size_t index = 0; index < graph->amount_node; index++)
        {
            if (visited[index] == 0 && distance[index] <= min)
            {
                min = distance[index];
                buf = index;
            }
        }
        
        visited[buf] = 1; 
        
        for (size_t index = 0; index < graph->amount_node; index++)
        {
            if (visited[index] == 0 && graph->data[buf][index] && distance[buf] != INT_MAX &&\
                distance[buf] + graph->data[buf][index] < distance[index])
                distance[index] = distance[buf] + graph->data[buf][index];
        }
    }
}

void find_nodes_with_Dijkstra(matrix_t **graph, const char *file_name, size_t *flag)
{
    size_t top = 0;
    double max_way = 0;
    FILE *f_write = fopen(file_name, "w");
    size_t rc = OK;
    
    rc = get_top_and_way(&top, &max_way, *graph); 
    if (rc == OK)
    {
        double distance[(*graph)->amount_node];
        Dijkstra(*graph, distance, top);

        fprintf(f_write, "digraph task {\n");

        for (size_t index = 0; index < (*graph)->amount_node; index++)
            if (distance[index] != INT_MAX && index != top)
            {
                if (distance[index] <= max_way)
                {
                    *flag = 1;
                    fprintf(f_write, "%zu -> %zu [label=\"%.1f\"];\n", top, index, distance[index]);
                }
            }
        fprintf(f_write, "}\n");
    }
    fclose(f_write);
}
