#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H

#include "struct.h"

#include <stdio.h>

#define STR_BUFF 501

/**
 * \brief create_node - Функция, которая создает узел
 * \param name Название узла
 * \return Узел
 */
tree_node_t *create_node(const char *name);

/**
 * \brief insert - Функция, которая добавляет узел в деревьe
 * \param tree Структура деревья
 * \param node Узел, который нужно добавить в дерево
 * \return Деревье
 */
tree_node_t *insert(tree_node_t *tree, tree_node_t *node);

/**
 * \brief btree_apply_pre - Обход дерева в префиксную форму
 * \param tree Структура дерева
 * \param f Указатель на функцию
 * \param arg Параметр
 */
void btree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg);

/**
 * \brief lookup_word - Поиск слова в деревье
 * \param tree Структура деревья
 * \param node_name Название узла, который хотим найти
 * \return Результат поиска
 */
size_t lookup_word(tree_node_t *tree, const char *node_name);

/**
 * \brief search_word_pre - Поиск слова в дерево в префиксной форме
 * \param tree Структура дерева
 * \param f Указатель на функцию
 * \param node_named Слово
 * \param flag Флаг
 */
void search_word_pre(tree_node_t *tree, size_t (*f)(tree_node_t *, const char *), const char *node_name, size_t *flag);

/**
 * \brief insert_balance - Функция, которая заполняет балансированое дерево элементамы
 * \param tree Структура дерева
 * \param node Узел
 * \return Новое дерево 
 */
tree_node_t *insert_balance(tree_node_t *tree, tree_node_t *node);

/**
 * \brief balance_node - Функция, которая, балансирует узел дерева
 * \param tree Структура дерева
 * \return Дерево
 */
tree_node_t *balance_node(tree_node_t *tree);

// записать длину в узле
/**
 * \brief new_height - Функция,, которая записывает длину в узле
 * \param tree Структура дерева
 */
void new_height(tree_node_t *tree);

/**
 * \brief what_height - Функция, которая определяет длину в узле
 * \param tree Структура дерева
 * \return Длина узла
 */
int what_height(tree_node_t *tree);

/**
 * \brief difference_in_length - Функция, которая определяет разницу между длинами в вершинах
 * \param tree Структура дерева
 * \return Результат разницы между длинами в вершинах
 */
int difference_in_length(tree_node_t *tree);

/**
 * \brief turn_right - Функция, которая поворачивает вершину направо
 * \param tree Структура Дерева
 * \return Изменненое дерево
 */
tree_node_t *turn_right(tree_node_t *tree);

/**
 * \brief turn_left - Функция, которая поворачивает вершину налево
 * \param tree Структура Дерева
 * \return Изменненое дерево
 */
tree_node_t *turn_left(tree_node_t *tree);

void compare_structures(hash_t **hash_table, tree_node_t **tree, tree_node_t **balanced_tree, const char *file_name);

#endif // TREE_FUNCS_H
