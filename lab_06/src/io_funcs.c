#include "io_funcs.h"
#include "return_codes.h"
#include "tree_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE

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
    ssize_t read; // код возврата функции getline
    size_t len = 0; // размер в байтах блока памяти, на который указывает первый параметр
    size_t count = 0; // счетчик
    size_t flag = 1;

    if (f_open)
    {
        while (flag == 1 && (read = getline(&node_name, &len, f_open)) != -1)
        {
            node = create_node(node_name);
            count += 1;

            if (node != NULL)
            {
                *tree = insert(*tree, node);
                free(node_name);
            }
            else
            {
                count -= 1;
                flag = 0;
                printf("\tОшибка: Не удалось добавить новый узел!\n");
            }
            printf("asdasdasd\n");
        }
        printf("read = %zu\n", read);

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
    FILE *f_write = fopen("../func_tests/data/output_first_tree.gv", "w");

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