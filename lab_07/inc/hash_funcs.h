#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

#include "struct.h"

cell_t *table_data(const size_t size);

hash_t *create_table(const size_t size);

/**
 * \brief rewrite_hash - Функция, которая увеличивает размер хеш-таблицы и перезаписывает
 * \param hash_table Структура хеш-таблицы
 * \return Хеш-таблица 
 */
hash_t *rewrite_hash(hash_t *hash_table);

hash_t *restruct(hash_t *hash_table, const size_t limit);

int hash_function(int key, const size_t max_size); // max_size == table_size

// проверить, записывалось ли уже число
size_t duplicate_key(hash_t *hash_table, const char *word);

hash_t *load_table(hash_t *hash_table, char *key, const size_t limit);

int get_len(const char *word);

size_t lookup_word_hash_closed(hash_t *hash_table, const char *key);

#endif // HASH_FUNCS_H