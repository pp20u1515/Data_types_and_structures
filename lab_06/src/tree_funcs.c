#include "return_codes.h"
#include "tree_funcs.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>

tree_node_t *create_node(const char *name)
{
    printf("name = %s\n", name);
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node)
    {
        node->name = name;
        node->left = NULL;
        node->righ = NULL;
    }
    return node;
}

tree_node_t *insert(tree_node_t *tree, tree_node_t *node)
{
    int cmp; // вспомагательнaя переменна, которая будет сохраня результат сравнивания

    if (tree)
    {
        cmp = strcmp(node->name, tree->name);

        if (cmp == 0)
            free(node);
        else if (cmp < 0)
            tree->left = insert(tree->left, node);
        else
            tree->righ = insert(tree->righ, node);
    }
    else
        return node;

    return tree;
}

tree_node_t *lookup(tree_node_t *tree, const char *name)
{
    int cmp; // вспомагательнaя переменна, которая будет сохраня результат сравнивания

    while (tree)
    {
        cmp = strcmp(name, tree->name);

        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->righ;
    }
    
    return NULL;
}

void btree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->righ, f, arg);
    btree_apply_pre(tree->left, f, arg);
}

void free_tree(tree_node_t *tree)
{
    if (tree)
        free(tree);

    tree = NULL;
}