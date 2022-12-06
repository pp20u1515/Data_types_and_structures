#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "struct.h"

#include <stdio.h>

/**
 * @brief Меню
 * 
 */
void menu();

/**
 * @brief read_file - Функция, читающая данные из файла и записывающие их в структуру
 * 
 * @param subs Структура абонементов
 * @param f_open Файл для чтения
 * @param size Количество абонементов
 */
void read_file(subscriber_t *subs, FILE *f_open, size_t *size);

/**
 * @brief show_table - Вывод таблицы
 * 
 * @param sub Структура абонементов
 * @param size Количество абонементов
 */
void show_table(const subscriber_t *sub, const size_t size);

/**
 * @brief input_string - Ввод символа
 * 
 * @param string Переменная, в которой будем хранить ввод
 * @return Код ошибки или код успеха
 */
size_t input_string(char *string);

/**
 * @brief print_key - Вывод ключей
 * 
 * @param key - Массив ключей, где ключ - номер телефона абонемента
 * @param size 
 */
void print_key(const key_t *key, const size_t size);

/**
 * @brief print_birthday_subs - Функция, которая вывод результат у кого скоро день рождения
 * 
 * @param sub Структура абонементов
 */
void print_birthday_subs(const subscriber_t sub);

void show_sorted_table_by_key(const subscriber_t *subs, const key_t *key, const size_t size);

#endif // IO_FUNCS_H