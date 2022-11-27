#include "return_codes.h"
#include "tree_funcs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>

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

void lookup(tree_node_t *tree, const char letter, size_t *count, void *arg)
{
    FILE *f_write = arg;

    if (f_write)
    {
        if (tree->left)
        {
            if (tree->left->name[0] == letter)
            {
                *count += 1;
                fprintf(f_write, "{\n");
                fprintf(f_write, "\tnode [shape=rounded]\n");
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
                fprintf(f_write, "\tnode [shape=rounded]\n");
                fprintf(f_write, "\t%s [style=filled, fillcolor=brown1]\n", tree->righ->name);
                fprintf(f_write, "}\n");
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
            }
            else
                fprintf(f_write, "%s -> %s;\n", tree->name, tree->righ->name);
        }
    }

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

void search_letter_pre(tree_node_t *tree, void (*f)(tree_node_t *, const char, size_t *, void *), const char letter, size_t *count, void *arg)
{
    if (tree == NULL)
        return;
    
    f(tree, letter, count, arg);
    search_letter_pre(tree->righ, f, letter, count, arg);
    search_letter_pre(tree->left, f, letter, count, arg);
}