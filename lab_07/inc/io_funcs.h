#ifndef IO_FUNCS_H  
#define IO_FUNCS_H

#include "struct.h"

#include <time.h>

#define STR_BUFF 501

/**
 * \brief menu - Меню программы
 */
void menu();

/**
 * \brief read_tree - Функция, которая читает данные из файла и заполняет дерево
 * \param tree Структура дерева
 * \param balanced_tree Структура сбалансированого дерева
 * \param file_name Название файла
 */
void read_tree(tree_node_t **tree, tree_node_t **balanced_tree, const char *file_name);

/**
 * \brief show_tree - Функция, которая выводит дерево на экран
 * \param tree Структора дерева
 * \param file_name Название файла
 */
void show_tree(tree_node_t **tree, const char *file_name);

/**
 * \brief node_to_dot - Функция, которая записывает узла дерева в файле
 * \param tree Структура дерева
 * \param param Параметр(выходный файл)
 */
void node_to_dot(tree_node_t *tree, void *param);

/**
 * \brief search_word - Функция, которая ищет первое вхождение указаного слова в дереве 
 * \param tree Структура дерева
 */
void search_word(tree_node_t **tree, tree_node_t **balanced_tree, hash_t **hash_table);

/**
 * \brief read_table - Функция, которая читает данные из файла и заполняет хеш-таблицу
 * \param hash_table Структура хеш-таблицы
 * \param file_name Название файла
 */
void read_table(hash_t **hash_table1, hash_tbl_t **hash_table2, const char *file_name);

/**
 * \brief show_hash_table - Функция, которая выводит хеш-таблицу
 * \param hash_table Структура хеш-таблицы
 */
void show_hash_table(hash_t *hash_table);

void add_to_tree(tree_node_t **tree, tree_node_t **balanced_tree);

void add_to_hash(hash_t **hash_table1, hash_t **hash_table2);

void show_hash_table2(hash_t *hash_table);

#endif // IO_FUNCS_H
