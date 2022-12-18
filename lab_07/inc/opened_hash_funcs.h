#ifndef OPENED_HASH_FUNCS_H
#define OPENED_HASH_FUNCS_H

#include "struct.h"

#include <stdio.h>

void create_table2(hash_tbl_t *hash_table, const size_t size);

void push(cell_t **list, cell_t *node);

void load_table2(hash_tbl_t *hash_table, const char *word);

#endif // OPENED_HASH_FUNCS_H