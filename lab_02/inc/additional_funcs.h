#ifndef CHECK_FUNCS_H
#define CHECK_FUNCS_H

#include "struct.h"

/**
 * @brief check_birthday - Функция, проверяющая день рождения абонемента на корректность
 * 
 * @param day День
 * @param mounth Месяц
 * @param year год
 * @return Код ошибки или код успеха
 */
size_t check_birthday(const size_t day, const size_t mounth, const size_t year);

/**
 * @brief copy_struct - Функция, которая копирует старую структуру в новую 
 * 
 * @param temp_subs Новая структура абонементов
 * @param subs Исходная структура абонементов
 * @param size Количество абонементов
 */
void copy_struct(subscriber_t *temp_subs, const subscriber_t *subs, const size_t size);

/**
 * @brief create_key_arr - Функция, получаюшая массив ключей, где ключ - номер телефона абонементов
 * 
 * @param subs Структура абонементов
 * @param key Массив ключей, где ключ - номер телефона абонементов
 * @param size Количество абонементов
 */
void create_key_arr(subscriber_t *subs, key_t *key, size_t const size);

#endif // CHECK_FUNCS_H