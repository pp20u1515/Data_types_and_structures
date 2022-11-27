#ifndef IO_FUNCS_H  
#define IO_FUNCS_H

#include "struct.h"

#include <time.h>

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

void search_letter(tree_node_t **tree, clock_t *start, clock_t *end);

void search_file(clock_t *start, clock_t *end);

#endif // IO_FUNCS_H