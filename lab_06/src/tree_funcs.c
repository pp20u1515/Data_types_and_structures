#include "return_codes.h"
#include "tree_funcs.h"
#include "io_funcs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define NO_WORD 0
#define WORD_EXIST 1
#define STR_BUFF 501

tree_node_t *create_node(const char *name)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node)
    {
        node->name = strdup(name);
        node->left = NULL;
        node->righ = NULL;
    }
    else
        node = NULL;

    return node;
}

tree_node_t *insert(tree_node_t *tree, tree_node_t *node)
{
    int cmp; // вспомагательнaя переменна, которая будет сохранят результат сравнивания
    
    if (tree == NULL)
        return node;
    else
    {
        cmp = strcmp(node->name, tree->name);
        
        if (cmp == 0)
            free(node);
        else if (cmp < 0)
            tree->left = insert(tree->left, node);
        else
            tree->righ = insert(tree->righ, node);
    }

    return tree;
}

void btree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->righ, f, arg);
    btree_apply_pre(tree->left, f, arg);
}

void search_letter_pre(tree_node_t *tree, void (*f)(tree_node_t *, const char, size_t *, void *), const char letter, size_t *count, void *arg)
{
    if (tree == NULL)
        return;
    
    f(tree, letter, count, arg);
    search_letter_pre(tree->righ, f, letter, count, arg);
    search_letter_pre(tree->left, f, letter, count, arg);
}

size_t lookup_word(tree_node_t *tree, const char *node_name)
{
    int cmp; // вспомагательнaя переменна, которая будет сохранят результат сравнивания
    size_t rc = NO_WORD; // код возврата

    while (tree)
    {
        cmp = strcmp(tree->name, node_name);

        if (cmp == 0)
            return WORD_EXIST;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->righ;
    }

    return rc;
}

void search_word_pre(tree_node_t *tree, size_t (*f)(tree_node_t *, const char *), const char *node_name, size_t *flag)
{
    int rc = NO_WORD; // код возврата

    if (tree == NULL)
        return;

    if (*flag == 0)
        rc = f(tree, node_name);

    if (rc == WORD_EXIST)
    {
        *flag = 1;
        return;
    }
    else
    {
        search_word_pre(tree->left, f, node_name, flag);
        search_word_pre(tree->righ, f, node_name, flag);
    }
}

void delete_word_pre(tree_node_t *tree, tree_node_t *((*f)(tree_node_t *, const char *)), const char *node_name)
{
    if (tree == NULL)
        return;

    tree = f(tree, node_name);
    delete_word_pre(tree->left, f, node_name);
    delete_word_pre(tree->righ, f, node_name);
}

void find_word(tree_node_t **temp_tree, const char *word, tree_node_t **parent)
{
    // обход дерева и поиск ключа
    while (*temp_tree != NULL && (strcmp(word, (*temp_tree)->name) != 0))
    {
        // обновить родителя до текущего узла
        *parent = *temp_tree;

        // если заданный ключ меньше текущего узла, переходим в левое поддерево
        // иначе идем в правое поддерево
        int cmp = strcmp(word, (*temp_tree)->name);

        if (cmp < 0)
           *temp_tree = (*temp_tree)->left;
        else
            *temp_tree = (*temp_tree)->righ;
    }
}

// Вспомогательная функция для поиска узла минимального значения в поддереве с корнем temp_tree
tree_node_t *find_min(tree_node_t *temp_tree)
{
    while (temp_tree->left != NULL)
        temp_tree = temp_tree->left;

    return temp_tree;
}

size_t delete_word(tree_node_t **tree, const char *node_name, void (*search)(tree_node_t **, const char *, tree_node_t **))
{
    tree_node_t *parent = NULL, *temp_tree = *tree; // переменная для хранения родителя текущего узла, и
                                                // переменная, которая начинает с корневого узла

    search(&temp_tree, node_name, &parent);

    if (temp_tree == NULL)
        return DATA_ERROR;

    // Случай 1: удаляемый узел не имеет дочерних элементов, т. е. является листовым узлом
    if (temp_tree->left == NULL && temp_tree->righ == NULL) 
    {
        // если удаляемый узел не является корневым узлом, то устанавливаем его
        // родительский левый/правый дочерний элемент в null
        if (temp_tree != *tree)
        {
            if (parent->left == temp_tree)
                parent->left = NULL;
            else
                parent->righ = NULL;
        }
        else // если дерево имеет только корневой узел, устанавливаем его в null
            *tree = NULL;

        free(temp_tree);
    }
    else if (temp_tree->left && temp_tree->righ) // Случай 2: удаляемый узел имеет двух потомков
    {
        tree_node_t *successor = find_min(temp_tree->righ); // найти его неупорядоченный узел-преемник
        char temp_word[STR_BUFF]; // сохраняем последующее значение
        strcpy(temp_word, successor->name);
        // рекурсивно удаляем преемника. Обратите внимание, что преемник
        // будет иметь не более одного потомка (правого потомка)
        delete_word(tree, successor->name, find_word);
        strcpy(temp_tree->name, temp_word);
    }
    else // Случай 3: удаляемый узел имеет только одного потомка
    {
        tree_node_t *child = temp_tree->left ? temp_tree->left : temp_tree->righ; // дочерний узел

        if (temp_tree != *tree) // если удаляемый узел не является корневым узлом, устанавливаем его родителя
        {                       // своему потомку
            if (temp_tree == parent->left)
                parent->left = child;
            else
                parent->righ = child;
        }
        else // если удаляемый узел является корневым узлом, то установить корень дочернему
            *tree = NULL;

        free(temp_tree);
    }

    return OK;
}

void sort(char **arr, tree_node_t *tree, size_t *index)
{
    if (tree != NULL)
    {
        sort(arr, tree->left, index);
        arr[(*index)++] = tree->name;
        sort(arr, tree->righ, index);
    }
}

void sort_tree(tree_node_t **tree)
{
    char *arr[STR_BUFF]; // массив, в котором будет сохранено отсортированное дерево
    size_t index = 0; // индекс элемента
    
    sort(arr, *tree, &index);
    print_array(arr, index);
}

int comp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_file()
{
    char *arr[STR_BUFF]; // массив, в котором будет сохранено отсортированное дерево
    const char *file_name = "./func_tests/data/input_first_tree.txt";
    size_t len = fill_arr(file_name, arr);

    if (len == 0)
    {
        printf("\tОшибка: Файл пустой!\n");
    }
    else
        qsort(arr, len, sizeof(char *), comp);

    print_array(arr, len);
}

void fill_array(int *arr, FILE *f_open)
{
    char node_name[STR_BUFF]; // название узла
    //size_t flag = 1;
    char array_char[][STR_BUFF] = {0};
    char array_char2[][STR_BUFF] = {0};
    size_t index = 0;
    
    while (!feof(f_open) && fscanf(f_open, "%s", node_name))
    {
        strcpy(array_char[index++], node_name);
    }
    strcpy(array_char2[0], array_char[0]);
    size_t new_index = 0;

    for (size_t i = 1; i < index; i++)
    {
        if(strcmp(array_char[i], array_char2[new_index]) != 0)
        {
            new_index++;
            strcpy(array_char2[new_index], array_char[i]);
        }
    }
    print_array(array_char2, new_index);
}

void read_tree2(tree_node_t **tree)
{
    FILE *f_open = fopen("./func_tests/data/input_first_tree.txt", "r");
    tree_node_t *node = NULL; // узель дерева
    size_t count = 0; // счетчик
    size_t flag = 1; // флаг
    char node_name[STR_BUFF]; // название узла
    int arr[STR_BUFF];
    char array_char[][STR_BUFF] = {0};
    
    if (f_open)
    {
        fill_array(arr, f_open);
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
