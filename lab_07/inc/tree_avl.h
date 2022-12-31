#ifndef __TREE_AVL_H__
#define __TREE_AVL_H__

#include <stdio.h>

#include "tree.h"
#include "tree_ddp.h"

int create_tree_avl(tree_t **root, FILE *f_in);

void add_to_avl(tree_t **tree, char *word);

#endif // __TREE_AVL_H__
