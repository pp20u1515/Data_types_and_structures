#ifndef SORT_FUNCS_H
#define SORT_FUNCS_H

#include "struct.h"

/**
 * @brief bubble_sort_table - Функция, использующая метод пузырка для сортировки таблицы
 * 
 * @param subs Структура абонементов
 * @param size Количество абонементов
 */ 
void bubble_sort_table(subscriber_t *subs, const size_t size);

/**
 * @brief sub_phone_cmp - Функция, сравнивающая номер телефона абонементов
 * 
 * @param a Первый элемент
 * @param b Второй элемент
 * @return Разность между первым и вторым элементами (a - b)
 */
int sub_phone_cmp(const void *a, const void *b);

/**
 * @brief compare - Функция, сравнивающая две числа
 * 
 * @param a Первый элемент
 * @param b Второй элемент
 * @return Разность между первым и вторым элементами (a - b)
 */
int compare(const void *a, const void *b);

/**
 * @brief sort_table - Функция, сортирующая таблицу по возрастанию по двумя методам, 
 * где ключ - номер телефона абонементов 
 * 
 * @param subs Структура абонементов 
 * @param size Количество абонементов
 */
void sort_table(subscriber_t *subs, const size_t size);

/**
 * @brief sort_keys - Функция, сортирующая массив ключей по возрастанию, где ключ - 
 * номер телефона абонементов
 * 
 * @param key Массив ключей 
 * @param size Количество абонементов
 */
void sort_keys(key_t *key, const size_t size);

/**
 * @brief bubble_sort_key - Функция, сортирующая ключи по возрастанию методом пузырка
 * 
 * @param key Массив ключей
 * @param size Количество абонементов
 */
void bubble_sort_key(key_t *key, const size_t size);

/**
 * @brief effency_sorting - Функция, определяющая эффективность сортировок
 * 
 * @param subs Структура абонементов
 * @param size Количество абонементов
 */
void effency_sorting(const subscriber_t *subs, const size_t size);

void sort_table_by_key(const subscriber_t *subs, const key_t *key, const size_t size);
void print_table_by_key(const subscriber_t *sub, const key_t *key, const size_t size);

#endif // SORT_FUNCS_H