#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef struct tree_node_t
{
    char *name; // название узла
    size_t height; // высота узлов дерева 
    struct tree_node_t *left; // меньшие
    struct tree_node_t *right; // старшие
}tree_node_t;

typedef struct cell_t
{
    size_t flag; // показатель, что ячецка занята
	char *value; // данные ячейки
    struct cell_t *next;
}cell_t;

typedef struct hash_t
{
    cell_t *data;  // ячейка
	size_t limit; // количество коллизий
	size_t size; // текущий размер таблицы
	size_t max_size; // максимальный размер таблицы
}hash_t;

typedef struct hash_tbl_t
{
    cell_t **data;
    size_t size; // текущий размер таблицы
    size_t max_size; // максимальный размер таблицы
}hash_tbl_t;

#endif // STRUCT_H