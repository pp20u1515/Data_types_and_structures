#ifndef STRUCT_H
#define STRUCT_H

#include <stdlib.h>

#define MAX_DATA_SIZE 100

typedef struct key
{
    size_t key; // ключ, где ключ номер телефона абонемента
    int cout; // количество ключей
}key_t;

// Структура, показывающая статус абонемента
typedef enum
{
    personal, // личный статус
    company // службеный статус
}status_t;

// Структура, показывающая дата рождения абонемента
typedef struct data
{
    size_t day; // день рождения
    size_t month; // месяц рождения
    size_t year; // год рождения
}data_t;

// Структура, показывающая службеный статус абонемента
typedef struct company
{
    char name[MAX_DATA_SIZE + 1]; // должность абонемента
    char position[MAX_DATA_SIZE + 1]; // организация/компания
}company_info_t;

// Структура, показывающая личный статус абонемента
typedef struct personal_info
{
    data_t birthday; // дата рождения абонемента
}personal_info_t;

// Структура, объединяющая личный и службеный статус абонемента
typedef union subscriber_info
{
    personal_info_t person_info; // полная личная информация о абонементе 
    company_info_t company_info; // полная службеная информация о абонементе
}subscriber_info_t;

typedef struct subscriber
{
    char first_name[MAX_DATA_SIZE + 1]; // имя абонемента
    char last_name[MAX_DATA_SIZE + 1]; // фамилия абонемента
    size_t phone; // номер телефона абонемента
    char street[MAX_DATA_SIZE + 1]; // название улицы
    char house[MAX_DATA_SIZE + 1]; // дом проживания
    status_t status; // статус абонемента
    subscriber_info_t subs_info; // информация о статусе абонемента
}subscriber_t;

#endif // STRUCT_H