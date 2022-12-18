#include "opened_hash_funcs.h"
#include "return_codes.h"
#include "hash_funcs.h"

#include "stdlib.h"
#include "string.h"

void create_table2(hash_tbl_t *hash_table, const size_t size)
{
    hash_table->data = calloc(size, sizeof(cell_t *));
    
    if (hash_table->data)
    {
        hash_table->max_size = size;
        hash_table->size = 0;
    }
}

cell_t *create_node2(const char *word)
{
    cell_t *node = malloc(sizeof(cell_t));

    if (node)
    {
        node->value = strdup(word);
        node->next = NULL;
    }
    return node;
}

void push(cell_t **list, cell_t *node)
{   
    if (list != NULL)
    {
        printf("list = %s\n", (*list)->value);
        //(*list)->value = strdup(word);
        //(*list)->next = NULL;
    }
    else
        printf("AS22123123\n");
    if (*list && node)
    {
        cell_t *cur = *list;

        for (; cur && cur->next; cur = cur->next)
        {
            if (strcmp(cur->value, node->value) == 0)
            {
                free(node);
                return;
            }
        }
        if (strcmp(cur->value, node->value) == 0)
        {
            free(node);
            return;
        }
        //strcpy(node->value, node->value);
        //node->next = cur->next;
        //cur->next = node;
        *list = (!*list) ? node : *list;
    }
}

void load_table2(hash_tbl_t *hash_table, const char *word)
{
    int word_len = get_len(word);
    
    int index = hash_function(word_len, hash_table->max_size);
    cell_t *node = create_node2(word);
    
    if (node)
        push(&hash_table->data[index], node);
}