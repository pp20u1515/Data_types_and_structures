#include "hash_funcs.h"
#include "return_codes.h"
#include "struct.h"

#include <stdlib.h>
#include <string.h>

cell_t *table_data(const size_t size)
{
    cell_t *cells = malloc(sizeof(cell_t) * size);

    if (cells)
    {
        for (size_t index = 0; index < size; index++)
        {
            cells[index].flag = 0;
            cells[index].value = NULL;
        }
    }
    return cells;
}

hash_t *create_table(const size_t size)
{
    hash_t *hash_table = malloc(sizeof(hash_t));

    if (hash_table)
    {
        hash_table->data = table_data(size);
        hash_table->max_size = size;
        hash_table->size = 0;
        hash_table->limit = 0;
    }
    return hash_table;
}

hash_t *rewrite_hash(hash_t *hash_table)
{
    size_t size = hash_table->max_size;
    hash_table->max_size += (hash_table->max_size / 3);
    cell_t *new_data = table_data(hash_table->max_size);

    for (size_t index = 0; index < size; ++index)
    {
        new_data[index].flag = hash_table->data[index].flag;
        new_data[index].value = strdup(hash_table->data[index].value);
    }
    free(hash_table->data);
    hash_table->data = new_data;

    return hash_table;
}

hash_t *restruct(hash_t *hash_table, const size_t limit)
{
    printf("\nРеструктурирование таблицы:\n");
    hash_t *new_hash_table = create_table(hash_table->max_size * 2);

    for (size_t index = 0; index < hash_table->max_size; ++index)
        if (hash_table->data[index].flag == 1)
            load_table(new_hash_table, hash_table->data[index].value, limit);

    free(hash_table->data);
    free(hash_table);

    return new_hash_table;
}

int hash_function(int key, const size_t max_size) // max_size == table_size
{
    int sum = 0;

    key > 0 ? (key) : (key *= -1);

    return key % max_size;
}

int get_len(const char *word)
{
    int count = 0, cur_count = strlen(word);

    while (*word)
    {
        count += (int)*word;
        word++;
    }

    cur_count = cur_count - 1;

    do
    {
        word--;
        cur_count--;
    } while (cur_count >= 0);
    
    return count;
}

size_t duplicate_key(hash_t *hash_table, const char *word)
{
    int word_len = get_len(word);
    int h = hash_function(word_len, hash_table->max_size);
    int i = h;
    size_t limit = 0;

    while (limit < hash_table->max_size)
    {
        limit++;

        if (hash_table->data[hash_function(i, hash_table->max_size)].value != NULL &&\
        strcmp(hash_table->data[hash_function(i, hash_table->max_size)].value, word) == 0 && \
        hash_table->data[hash_function(i, hash_table->max_size)].flag == 1)
            return DATA_ERROR;
        
        i++;
    }
    return OK;
}

hash_t *load_table(hash_t *hash_table, char *key, const size_t limit)
{
    if (hash_table)
    {
        // если все ячейки заполнени
        if (hash_table->max_size == hash_table->size)
            hash_table = rewrite_hash(hash_table);

        // большое количество сравнений
        while (hash_table->limit >= limit)
            hash_table = restruct(hash_table, limit);

        if (duplicate_key(hash_table, key))
            return hash_table;
        
        int key_len = get_len(key);
        int h = hash_function(key_len, hash_table->max_size);
        
        size_t cur_limit = 0;
        
        while (hash_table->data[h % hash_table->max_size].flag == 1)
        {
            if (cur_limit >= hash_table->max_size)
            {
                printf("\tТаблица переполнена!\n");
                break;
            }
            h++;
            cur_limit++;
        }
        
        if (h >= hash_table->max_size)
            h %= hash_table->max_size;
        
        hash_table->limit += (cur_limit == 0) ? 0 : 1;
        hash_table->data[h].value = strdup(key);
        hash_table->data[h].flag = 1;
    }
    return hash_table;
}

hash_t *load_table2(hash_t *hash_table, char *key, const size_t limit)
{
    if (hash_table)
    {
        if (duplicate_key(hash_table, key))
            return hash_table;

        int key_len = get_len(key);
        int h = hash_function(key_len, hash_table->max_size);
        size_t cur_limit = 0; // проверка колизии

        while (hash_table->data[h % hash_table->max_size].flag == 1)
        {
            h++;
            cur_limit++;
        }
        
        if (h >= hash_table->max_size)
            h %= hash_table->max_size;
        
        hash_table->limit += (cur_limit == 0) ? 0 : 1;
        hash_table->data[h].value = strdup(key);
        hash_table->data[h].flag = 1;
    }
    
    return hash_table;
}

size_t lookup_word_hash_closed(hash_t *hash_table, const char *key)
{
    size_t index = 0;
    size_t flag = 0;

    while (flag == 0 && index < hash_table->size)
    {
        if (hash_table->data[index].value != NULL)
        {
            int key_len = get_len(hash_table->data[index].value);
            int h = hash_function(key_len, hash_table->max_size);

            if (hash_table->data[h].value != NULL && strcmp(hash_table->data[h].value, key) == 0)
                flag = 1;
        }
        index += 1;
    }
    return flag;
}