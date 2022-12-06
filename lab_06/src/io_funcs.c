#include "io_funcs.h"
#include "return_codes.h"
#include "tree_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#define STR_BUFF 255
#define NO_WORD 0
#define WORD_EXIST 1

void menu()
{
    printf("\t\t\tМеню\n\n");
    printf("\t1) Прочитать дерево из файла.\n\
        2) Вывести дерево на экран.\n\
        3) Добавить узел в дерево.\n\
        4) Сделать поиск в дерево.\n\
        5) Найти слово в дереве.\n\
        6) Удалить слово из дерева.\n\
        7) Сравнить время поиска слова в дереве и в файле.\n\
        8) Сравнить время сортировки слов в дереве и в файле.\n\
        0) Выйти из программы.\n");
}

void read_tree(tree_node_t **tree)
{
    FILE *f_open = fopen("./func_tests/data/input_first_tree.txt", "r");
    tree_node_t *node = NULL; // узель дерева
    size_t count = 0; // счетчик
    size_t flag = 1; // флаг
    char node_name[STR_BUFF]; // название узла
    
    if (f_open)
    {
        while (!feof(f_open) && flag == 1 && fscanf(f_open, "%s", node_name))
        {
            node = create_node(node_name);
            count += 1;

            if (node != NULL)
                *tree = insert(*tree, node);
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

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f_write = param; // выходной файл

    if (f_write)
    {
        if (tree)
            fprintf(f_write, "%s;\n", tree->name);

        if (tree->left)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->left->name); 
        
        if (tree->righ)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
    }
}

void show_tree(tree_node_t **tree)
{
    FILE *f_write = fopen("./func_tests/data/output_first_tree.dot", "w");

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

void search_letter(tree_node_t **tree, clock_t *start, clock_t *end)
{
    char letter; // ввод буквы
    size_t result = 0; // результат поиска буквы
    FILE *painted_tree = fopen("./func_tests/data/painted_tree.dot", "w");

    printf("\tВведите букву:");
    if (scanf(" %c", &letter) && painted_tree)
    {
        *start = clock();
        fprintf(painted_tree, "digraph %s {\n", "painted_tree");

        if ((*tree)->name[0] == letter)
        {
            fprintf(painted_tree, "{\n");

            fprintf(painted_tree, "\t%s [style=filled, fillcolor=brown1]\n", (*tree)->name);
            fprintf(painted_tree, "}\n");
            result += 1;
        }

        search_letter_pre(*tree, lookup, letter, &result, painted_tree);
        fprintf(painted_tree, "}\n");
        *end = clock();
        
        printf("\tКоличество слов, которые начинают на букву <%c> = %zu\n", letter, result);
        fclose(painted_tree);
    }
}

void search_file(clock_t *start, clock_t *end)
{
    size_t count = 0; // счетчик
    ssize_t read; // код возврата функции getline
    size_t len = 0; // размер элемента в байтах
    char *node_name = NULL; // название узла
    char letter; // входная буква
    FILE *f_open = fopen("./func_tests/data/input_first_tree.txt", "r");
    
    printf("\tВведите букву:");

    if (f_open && scanf(" %c", &letter))
    {
        *start = clock();
        
        while ((read = getline(&node_name, &len, f_open)) != -1)
        {
            if (node_name[0] == letter)
                count += 1;
        }
        *end = clock();
        
        fclose(f_open);
    }
}

void search_word(tree_node_t **tree)
{
    char word[STR_BUFF]; // название узла 
    size_t flag = 0;

    printf("\tВведите слово, которое хотите найти: ");
    scanf("%s", word);

    search_word_pre(*tree, lookup_word, word, &flag);

    if (flag == WORD_EXIST)
        printf("\tСлово <%s> найдено в дереве!\n", word);
    else
        printf("\tСлово <%s> не найдено в дереве!\n", word);
}

void delete_node(tree_node_t **tree)
{
    char word[STR_BUFF]; // название узла
    size_t rc = OK; // код возврата

    printf("\tВведите название узла:");
    if (scanf("%s", word))
    {
        rc = delete_word(tree, word, find_word);

        if (rc != OK)
            printf("\tВ дереве нет такого узла!\n");
    }
}

void print_array(char **arr, const size_t size)
{
    printf("\tОтсортированое дерево: ");
    for (size_t index = 0; index < size; index++)
        printf("%s ", arr[index]);
    printf("\n");
}

void lookup(tree_node_t *tree, const char letter, size_t *count, void *arg)
{
    FILE *f_write = arg; // выходной файл

    if (f_write)
    {
        if (tree->left)
        {
            if (tree->left->name[0] == letter)
            {
                *count += 1;
                fprintf(f_write, "{\n");
                fprintf(f_write, "\t%s [style=filled, fillcolor=brown1]\n", tree->left->name);
                fprintf(f_write, "}\n");
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->left->name);
            }
            else
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->left->name);         
        }
        if (tree->righ)
        {
            if (tree->righ->name[0] == letter)
            {
                *count += 1;
                fprintf(f_write, "{\n");
                fprintf(f_write, "\t%s [style=filled, fillcolor=brown1]\n", tree->righ->name);
                fprintf(f_write, "}\n");
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
            }
            else
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
        }
    }
}

size_t fill_arr(const char *file_name, char **arr)
{
    char node_name[STR_BUFF]; // название узла
    size_t count = 0; // счетчик
    FILE *f_open = fopen(file_name, "r");

    if (f_open)
    {
        rewind(f_open);

        while (!feof(f_open) && fscanf(f_open, "%s", node_name))
        {
            arr[count] = malloc(sizeof(char) * strlen(node_name + 1));
            strcpy(arr[count], node_name);
            count += 1;
        }

        fclose(f_open);
    }
    return count;
}

void add_node(tree_node_t **tree)
{
    tree_node_t *node = NULL;
    char word[STR_BUFF];

    printf("\tВведите название узла для добавления в дерево: ");
    scanf("%s", word);

    node = create_node(word);

    if (node)
        *tree = insert(*tree, node);
    else
        printf("\tОшибка: Не удалось добавить новый узел в дерево!\n");
}
