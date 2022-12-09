#include "return_codes.h"
#include "tree_funcs.h"
#include "io_funcs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NO_WORD 0
#define WORD_EXIST 1
#define STR_BUFF 501

tree_node_t *create_node(const char *name)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    
    if (node)
    {
        node->name = strdup(name);
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }

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
        {
            free(node->name);
            free(node);
        }
        else if (cmp < 0)
            tree->left = insert(tree->left, node);
        else
            tree->right = insert(tree->right, node);
    }

    return tree;
}

tree_node_t *insert_balance(tree_node_t *tree, tree_node_t *node)
{
    int cmp; // вспомагательнaя переменна, которая будет сохранят результат сравнивания

    if (tree == NULL)
        return node;
    else
    {
        cmp = strcmp(node->name, tree->name);
        
        if (cmp == 0)
        {
            free(node->name);
            free(node);

            return tree;
        }
        else if (cmp < 0)
            tree->left = insert(tree->left, node);
        else
            tree->right = insert(tree->right, node);
    }

    return balance_node(tree);
}

size_t what_height(tree_node_t *tree)
{
    return tree ? tree->height : 0;
}

void new_height(tree_node_t *tree)
{
    size_t left_height = what_height(tree->left); // высота левого поддерева
    size_t right_height = what_height(tree->right); // высота правого поддерева

    tree->height = ((left_height > right_height) ? left_height : right_height) + 1;
}

int difference_in_length(tree_node_t *tree)
{
    return what_height(tree->right) - what_height(tree->left);
}

tree_node_t *turn_right(tree_node_t *tree)
{
    tree_node_t *temp_tree = tree->left;
    tree->left = temp_tree->right;
    temp_tree->right = tree;

    new_height(tree);
    new_height(temp_tree);

    return temp_tree;
}

tree_node_t *turn_left(tree_node_t *tree)
{
    tree_node_t *temp_tree = tree->right;
    tree->right = temp_tree->left;
    temp_tree->left = tree;

    new_height(tree);
    new_height(temp_tree);

    return temp_tree;
}

tree_node_t *balance_node(tree_node_t *tree)
{
    new_height(tree);

    if (difference_in_length(tree) == 2)
    {
        if (difference_in_length(tree->right) < 0)
            tree->right = turn_right(tree->right);

        return turn_left(tree);
    }

    if (difference_in_length(tree) == -2)
    {
        if (difference_in_length(tree->left) > 0)
            tree->left = turn_left(tree->left);

        return turn_right(tree);
    }
    return tree;
}

void btree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->right, f, arg);
    btree_apply_pre(tree->left, f, arg);
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
            tree = tree->right;
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
        search_word_pre(tree->right, f, node_name, flag);
    }
}