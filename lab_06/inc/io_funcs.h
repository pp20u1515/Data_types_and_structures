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
 * \brief show_tree - Функция, которая выводит дерево на экран
 * \param tree Структора дерева
 */
void show_tree(tree_node_t **tree);

/**
 * \brief node_to_dot - Функция, которая записывает узла дерева в файле
 * \param tree Структура дерева
 * \param param Параметр(выходный файл)
 */
void node_to_dot(tree_node_t *tree, void *param);

/**
 * \brief read_tree - Функция, которая читает данные из файла и заполняет дерево
 * \param tree Структура дерева
 */
void read_tree(tree_node_t **tree, char (*arr_words)[STR_BUFF]);

/**
 * \brief search_letter - Функция, которая определяет количество вершин дерева в дереве, содержащих
 * слова, начинающиеся на указанную букву
 * \param tree Структура дерева
 * \param start Текущее время, перед запуском функции search_letter
 * \param end Время, после запуска функции search_letter
 */
void search_letter(tree_node_t **tree, clock_t *start, clock_t *end);

/**
 * \brief search_file - Функция, которая определяет количество вершин дерева в файле, содержащих
 * слова, начинающиеся на указанную букву
 * \param start Текущее время, перед запуском функции search_file
 * \param end Время, после запуска функции search_letter
 */
void search_file(clock_t *start, clock_t *end);

/**
 * \brief delete_node - Функция, которая удаляет указаную вершину дерева
 * \param tree Структура дерева
 */
void delete_node(tree_node_t **tree);

/**
 * \brief search_word - Функция, которая ищет первое вхождение указаного слова в дереве 
 * \param tree Структура дерева
 */
void search_word(tree_node_t **tree);

/**
 * \brief print_array - Функция, которая выводит массив
 * \param arr Массив
 * \param size Размер массива
 */
void print_array(char **arr, const size_t size);

/**
 * \brief lookup - Функция, которая выполняет поиск буквы в слово
 * \param tree Структура дерева
 * \param letter Буква
 * \param count Считчик
 * \param arg Параметр (выходный файл)
 */
void lookup(tree_node_t *tree, const char letter, size_t *count, void *arg);

/**
 * \brief fill_arr - Функция, которая заполнаяет массив элементами
 * \param tree Название входного файла
 * \param node_name Массив
 * \return Количество элементов массива
 */
size_t fill_arr(const char *file_name, char **arr);

/**
 * \brief add_node - Функция, которая добавляет новый узел в дереве
 * \param tree Структура дерева
 */
void add_node(tree_node_t **tree);

#endif // IO_FUNCS_H
