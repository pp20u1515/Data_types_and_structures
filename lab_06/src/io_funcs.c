#include "io_funcs.h"
#include "return_codes.h"
#include "tree_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#define STR_BUFF 255

void menu()
{
    printf("\t\t\tМеню\n\n");
    printf("\t1) Прочитать дерево из файла.\n\
        2) Вывести дерево на экран.\n\
        3) Сделать поиск в дерево.\n\
        4) Сравнить время поиска слова в дереве и в файле.\n");
}

void read_tree(tree_node_t **tree)
{
    FILE *f_open = fopen("../func_tests/data/input_first_tree.txt", "r");
    tree_node_t *node = NULL; // узель дерева
    char *node_name = NULL; // название узла
    size_t count = 0; // счетчик
    size_t flag = 1; // флаг
    char str[STR_BUFF];
    
    if (f_open)
    {
        while (!feof(f_open) && flag == 1 && fscanf(f_open, "%s", str))
        {
            node_name = strdup(str);
            node = create_node(node_name);
            count += 1;

            if (node != NULL)
            {
                *tree = insert(*tree, node);
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

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f_write = param;

    if (f_write)
    {
        if (tree->left)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->left->name); 
        
        if (tree->righ)
            fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
    }
}

void show_tree(tree_node_t **tree)
{
    FILE *f_write = fopen("../func_tests/data/output_first_tree.dot", "w");

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
    FILE *painted_tree = fopen("../func_tests/data/panted_tree.dot", "w");

    printf("\tВведите букву:");
    if (scanf(" %c", &letter) && painted_tree)
    {
        *start = clock();
        fprintf(painted_tree, "digraph %s {\n", "painted_tree");

        if ((*tree)->name[0] == letter)
        {
            fprintf(painted_tree, "{\n");
            fprintf(painted_tree, "\tnode [shape=rounded]\n");
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
    size_t count = 0;
    ssize_t read;
    size_t len = 0;
    char *node_name = NULL;
    char letter;
    FILE *f_open = fopen("../func_tests/data/input_first_tree.txt", "r");
    
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