#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef struct tree_node_t
{
    char *name; // название узла
    struct tree_node_t *left; // меньшие
    struct tree_node_t *righ; // старшие
}tree_node_t;

#endif // STRUCT_H