#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "struct.h"

#include <stdio.h>

#define MAX_SIZE 4000

void menu();

void read_graph(matrix_t **graph, const char *file_name);

size_t fill_matrix(matrix_t **matrix, const char *file_name);

size_t input_data(matrix_t **matrix, FILE *f_open);

void to_dot(matrix_t *graph, const char *file_name);

void print_matrix(matrix_t *graph);

void find_nodes_with_Dijkstra(matrix_t **graph, const char *file_name, size_t *flag);

int get_file(void);
int get_command(int *command);
int get_ways(matrix_t *graph, int *count);
void Dijkstra(matrix_t *graph, double *distance, int top);

#endif // IO_FUNCS_H
