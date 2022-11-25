#ifndef IO_FUNCS_H  
#define IO_FUNCS_H

#include "struct.h"

/**
 * \brief menu - Меню программы
 */
void menu();

/**
 * \brief show_tree - Функция, которая выводит дерево на экран
 * \param tree Структора дерева
 */
void show_tree(tree_node_t **tree);

/**
 * \brief node_to_dot - Функция, которая записывает узла дерева в файле
 * \param tree Структура дерева
 * \param param Параметр
 */
void node_to_dot(tree_node_t *tree, void *param);

/**
 * \brief read_tree - Функция, которая читает данные из файла и заполняет дерево
 * \param tree Структура дерева
 */
void read_tree(tree_node_t **tree);

#endif // IO_FUNCS_H