#ifndef GRAPH_FUNCS_H
#define GRAPH_FUNCS_H

#include "struct.h"

matrix_t *create_matrix(const size_t amount_node);

double **allocate_matrix(const size_t amount_node);

void free_matrix(double **data, const size_t amount_node);

matrix_t *all_way(matrix_t *graph);
void timeget();

#endif // GRAPH_FUNCS_H
