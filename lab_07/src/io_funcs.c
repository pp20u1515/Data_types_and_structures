#include "io_funcs.h"
#include "return_codes.h"
#include "tree_funcs.h"
#include "hash_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#define NO_WORD 0
#define WORD_EXIST 1
#define LIMIT 23 // количество элементов

void menu()
{
    printf("\t\t\tМеню\n\n");
    printf("\t1) Прочитать деревa и хеш-таблицу из файла.\n\
        2) Вывести дерева на экран.\n\
        3) Вывести хеш-таблицы на экран.\n\
        4) Найти слово в дереве и хеш-таблицу.\n\
        5) Сравнить время поиска слова в дереве и в файле.\n\
        6) Добавить элемент в деревях и в хеш-таблицу.\n\
        0) Выйти из программы.\n");
}

void read_tree(tree_node_t **tree, tree_node_t **balanced_tree, const char *file_name)
{
    FILE *f_open = fopen(file_name, "r"); // Входный файл
    tree_node_t *node = NULL, *node_balance = NULL; // узель дерева
    size_t count = 0; // счетчик
    size_t flag = 1; // флаг
    char node_name[STR_BUFF]; // название узла
    
    if (f_open)
    {
        while (!feof(f_open) && flag == 1 && fscanf(f_open, "%s", node_name))
        {
            node = create_node(node_name);
            node_balance = create_node(node_name);
            count += 1;

            if (node != NULL && node_balance != NULL)
            {
                *tree = insert(*tree, node);
                *balanced_tree = insert_balance(*balanced_tree, node_balance);
            }
            else
            {
                count -= 1;
                flag = 0;
                printf("\tОшибка: Не удалось добавить новый узел!\n");
            }
        }
        if (count == 0)
            printf("\tФайл пустой!\n");

        fclose(f_open);
    }
    else
        printf("\tОшибка: Не удалось открыть файл!\n");
}

void read_table(hash_t **hash_table1, hash_t **hash_table2, const char *file_name)
{
    FILE *f_open = fopen(file_name, "r"); // входный файл
    hash_t *temp_hash_table1 = NULL, *temp_hash_table2 = NULL; // вспомогательная структура хеш-таблицы 
    char word[STR_BUFF]; // входное слово 
    int count= 0;
    if (f_open)
    {
        temp_hash_table1 = create_table(LIMIT);
        temp_hash_table2 = create_table(LIMIT);

        if (temp_hash_table1 && temp_hash_table2)
            while (!feof(f_open))
            {
                count++;
                fscanf(f_open, "%s", word);
                
                temp_hash_table1 = load_table(temp_hash_table1, word, LIMIT);
                temp_hash_table2 = load_table2(temp_hash_table2, word, LIMIT);

                temp_hash_table1->size += 1;
                temp_hash_table2->size += 1;
            }
        else
            printf("\tОшибка: Не удалось выделить память под хеш-таблицой!\n");

        fclose(f_open);
    }
    else
        printf("\tОшибка: Не удалось открыть файл!\n");
    
    *hash_table1 = temp_hash_table1;
    *hash_table2 = temp_hash_table2;
}

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f_write = param; // выходной файл

    if (f_write)
    {
        if (tree)
            fprintf(f_write, "%s;\n", tree->name);

        if (tree->left)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->left->name); 
        
        if (tree->right)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->right->name);
    }
}

void show_tree(tree_node_t **tree, const char *file_name)
{
    FILE *f_write = fopen(file_name, "w");

    if (f_write)
    {
        fprintf(f_write, "digraph %s {\n", "tree");
        btree_apply_pre(*tree, node_to_dot, f_write);
        fprintf(f_write, "}\n");
        fclose(f_write);
    }
    else
        printf("\tОшибка: Не удалось открыть файл!\n");
}

void search_word(tree_node_t **tree, tree_node_t **balanced_tree, hash_t **hash_table)
{
    char word[STR_BUFF]; // название узла 
    tree_node_t *node = NULL, *node_balanced = NULL;
    size_t flag = 0;
    char choice;

    printf("\tВведите слово, которое хотите найти: ");
    scanf("%s", word);

    search_word_pre(*tree, lookup_word, word, &flag);

    if (flag == WORD_EXIST)
    {
        flag = 0;
        printf("\tСлово <%s> найдено в дереве!\n", word);
        flag = lookup_word_hash_closed(*hash_table, word);

        if (flag == WORD_EXIST)
        {
            printf("\tСлово <%s> найдено в хеш-таблице используя закрытое хеширование!\n", word);

            flag = lookup_word_hash_closed(*hash_table, word);
        }
    }
    else
    {
        printf("\tСлово <%s> не найдено в дереве!\n", word);
        printf("\tСлово <%s> не найдено в хеш-таблице!\n", word);
        printf("\tХотите его добавить?(y/n): ");

        scanf(" %c", &choice);
        
        if (choice == 'y')
        {
            node = create_node(word);
            node_balanced = create_node(word);

            *tree = insert(*tree, node);
            *balanced_tree = insert_balance(*balanced_tree, node_balanced);

            *hash_table = load_table(*hash_table, word, LIMIT);
            (*hash_table)->size += 1;
        }
    }
}

void show_hash_table(hash_t *hash_table)
{
    printf("\n\tХеш-таблица:\n\n");
    printf("+-------+---------+-------------+\n");
    printf("|   №   |   Хеш   |     Слово   |\n");
    printf("+-------+---------+-------------+\n");

    for (size_t index = 0, count = 0; index < hash_table->max_size; index++)
    {
        if (hash_table->data[index].value != NULL)
        {
            int key_len = get_len(hash_table->data[index].value);

            printf("|%4zu   |%7d   |%9s   |\n", count, hash_function(key_len, hash_table->max_size), \
            hash_table->data[index].value);

            count++;
        }
    }
    printf("+-------+---------+-------------+\n");

    printf("\tКоличество колизии: %zu\n", hash_table->limit);
    printf("\n");
}

void add_to_tree(tree_node_t **tree, tree_node_t **balanced_tree)
{
    char node_name[STR_BUFF];
    tree_node_t *node = NULL, *node_balance = NULL; // узель дерева

    printf("\tВведите слово, которое хотите добавить в дерево: ");
    scanf("%s", node_name);

    node = create_node(node_name);
    node_balance = create_node(node_name);

    if (node != NULL && node_balance != NULL)
    {
        *tree = insert(*tree, node);
        *balanced_tree = insert_balance(*balanced_tree, node_balance);
    }
    else
        printf("\tОшибка: Не удалось добавить новый узел!\n");
}

void add_to_hash(hash_t **hash_table1, hash_t **hash_table2)
{
    char node_name[STR_BUFF]; 
    
    printf("\tВведите слово, которое хотите добавить в дерево: ");
    scanf("%s", node_name);
    (*hash_table1)->size += 1;
    (*hash_table2)->size += 1;
    *hash_table1 = load_table(*hash_table1, node_name, LIMIT);
    *hash_table2 = load_table2(*hash_table2, node_name, LIMIT);
}