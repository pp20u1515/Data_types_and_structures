#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

// матрица смежности
typedef struct matrix_t
{
    size_t amount_node; // количество вершин
    double **data; // данные
} matrix_t;

#endif // STRUCT_H
