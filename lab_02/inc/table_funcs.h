#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H

#include "struct.h"

#include <stdio.h>
/**
 * @brief del_subs - Функция, удаляющая абонементa
 * 
 * @param subs Структура абонементов
 * @param size Количество абонементов
 */
void del_subs(subscriber_t *subs, size_t *size);

/**
 * @brief del_by_phone - Функция, удаляющая абонемента по его номеру телефона
 * 
 * @param del_sub Переменная, содержающая номер телефона абонемента, которого надо
 * надо удалить из таблицы
 * @param sub Структура абонементов
 * @param size Количество абонементов
 */
void del_by_phone(const size_t del_sub, subscriber_t *sub, size_t *size);

/**
 * @brief del - Функция удаления
 * 
 * @param sub Структура абонементов
 * @param index Переменная, содержающая индекс абонемента, которого надо удалить из таблицы
 * @param size Количество абонементов
 */
void del(subscriber_t *sub, size_t index, size_t *size);

/**
 * @brief add_subs - Функция, добавляющая абонементов в таблицу
 * 
 * @param subs Структура абонементов
 * @param size Количество абонементов
 */
void add_subs(subscriber_t *subs, size_t *size);

/**
 * @brief add_status - Функция, которая вводит статус абонемента
 * 
 * @param sub Структура абонемента
 * @return Код успеха или код ошибки
 */
size_t add_status(subscriber_t *sub);

/**
 * @brief add_personal_info - Функция, которая вводит личную информацию о абонементе
 * 
 * @param sub Структура абонемента
 * @param size Количество абонементов
 * @return Код усшеха или код ошибки
 */
size_t add_personal_info(subscriber_t *sub, const size_t *size);

/**
 * @brief has_birthday_soon - Функция, определяющая у кого скоро день рождения
 * 
 * @param subs Структура абонементов
 * @return Код ошибки или код успеха 
 */
size_t has_birthday_soon(const subscriber_t subs);

/**
 * @brief find_birthday - Функция, которая ище у кого скоро день рождения
 * 
 * @param subs Структура абонементов
 * @param size Количество абонементов
 */
void find_birthday(const subscriber_t *subs, const size_t size);

#endif // TABLE_FUNCS_H