#ifndef HASH_CLOSED_H
#define HASH_CLOSED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell_t
{
    size_t flag; // показатель, что ячецка занята
	char *value; // данные ячейки
}cell_t;

typedef struct hash2_t
{
    cell_t *data;  // ячейка
	size_t limit; // количество коллизий
	size_t size; // текущий размер таблицы
	size_t max_size; // максимальный размер таблицы
}hash2_t;

void read_table(hash2_t **hash_table1, FILE *f_open);

cell_t *table_data(const size_t size);

hash2_t *create_table(const size_t size);

hash2_t *rewrite_hash(hash2_t *hash_table);

hash2_t *restruct(hash2_t *hash_table, const size_t limit);

int hash_function(int key, const size_t max_size); // max_size == table_size

int get_len(const char *word);

size_t duplicate_key(hash2_t *hash_table, const char *word);

hash2_t *load_table(hash2_t *hash_table, char *key, const size_t limit);

void show_hash_table(hash2_t *hash_table);

#endif // HASH_CLOSED_H