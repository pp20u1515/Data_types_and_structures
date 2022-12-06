#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H

#include "struct.h"

#include <stdio.h>

/**
 * \brief create_node - Функция, которая создает узел(корень деревья)
 * \param name Название узла
 * \return Дерево
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
 * \brief lookup - Поиск в деревье
 * \param tree Структура деревья
 * \param letter Буква, которая хотим найти
 */
void lookup(tree_node_t *tree, const char letter, size_t *count, void *arg);

/**
 * \brief btree_apply_pre - Обход дерева в префиксную форму
 * \param tree Структура дерева
 * \param f Указатель на функцию
 * \param arg Параметр
 */
void btree_apply_pre(tree_node_t *tree, void (*f)(tree_node_t *, void *), void *arg);

/**
 * \brief search_letter_pre - Поиск буквы в дерево в префиксной форме
 * \param tree Структура дерева
 * \param f Указатель на функцию
 * \param letter Буква
 * \param count Счетчик
 * \param arg Параметр
 */
void search_letter_pre(tree_node_t *tree, void (*f)(tree_node_t *, const char, size_t *, void *), const char letter, size_t *count, void *arg);

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
 * \brief delete_word_pre - Удаление слова в дерево в префиксной форме
 * \param tree Структура дерева
 * \param f Указатель на функцию
 * \param node_name Слово
 */
void delete_word_pre(tree_node_t *tree, tree_node_t *((*f)(tree_node_t *, const char *)), const char *node_name);

/**
 * \brief delete_word - Удаление слова в дерево
 * \param tree Структура дерева
 * \param node_name Слово
 * \param search Указатель на функцию
 */
size_t delete_word(tree_node_t **tree, const char *node_name, void (*search)(tree_node_t **, const char *, tree_node_t **));

/**
 * \brief sort_tree - Функция, которая сортирует вершины дерева по возрастанию в дереве
 * \param tree Структура дерева
 */
void sort_tree(tree_node_t **tree);

/**
 * \brief sort - Функция, которая сортирует вершины дерева по возрастанию
 * \param arr Массив
 * \param tree Структура дерева
 * \param index Индекс элемета
 */
void sort(char **arr, tree_node_t *tree, size_t *index);

/**
 * \brief sort_file - Функция, которая сортирует вершины дерева по возрастанию в файле
 */
void sort_file();

/**
 * \brief find_word - Функция для поиска в поддереве и установки его родителя
 * \param temp_tree Структура дерева 
 * \param word Слово, которое нужно удалить из дерева
 * \param parent Переменная для хранения родителя текущего узла
 */
void find_word(tree_node_t **temp_tree, const char *word, tree_node_t **parent);

void read_tree2(tree_node_t **tree);

#endif // TREE_FUNCS_H
