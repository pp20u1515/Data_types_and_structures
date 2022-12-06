#include "../inc/table_funcs.h"
#include "../inc/struct.h"
#include "../inc/return_codes.h"
#include "../inc/additional_funcs.h"
#include "../inc/io_funcs.h"

#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_DATA_SIZE 100
#define MAX_ARR_SIZE 1000

void del(subscriber_t *sub, size_t index, size_t *size)
{
    for (; index < *size - 1; index++)
    {
        strcpy(sub[index].last_name, sub[index + 1].last_name);
        strcpy(sub[index].first_name, sub[index + 1].first_name);
        sub[index].phone = sub[index + 1].phone;
        strcpy(sub[index].street, sub[index + 1].street);
        strcpy(sub[index].house, sub[index + 1].house);
        sub[index].subs_info.person_info.birthday.day = sub[index + 1].subs_info.person_info.birthday.day;
        sub[index].subs_info.person_info.birthday.month = sub[index + 1].subs_info.person_info.birthday.month;
        sub[index].subs_info.person_info.birthday.year = sub[index + 1].subs_info.person_info.birthday.year;
        sub[index].status = sub[index + 1].status;
        strcpy(sub[index].subs_info.company_info.position, sub[index + 1].subs_info.company_info.position);
        strcpy(sub[index].subs_info.company_info.name, sub[index + 1].subs_info.company_info.name);
    }
    *size -= 1;
}

void del_by_phone(const size_t del_sub, subscriber_t *sub, size_t *size)
{
    int flag = 0; // flag = False
    
    for (size_t index = 0; flag == 0 && index < *size; index++)
    {    
        if (del_sub == sub[index].phone && flag == 0)
            flag = 1;
            
        if (flag == 1)
            del(sub, index, size);
    }

    if (flag == 0)
        printf("\tОшибка: Такого номера нет!\n");
}

void del_subs(subscriber_t *subs, size_t *size)
{
    size_t del_sub; // переменная для удаления абонемента
    
    printf("\tЧтобы удалить абонемента введите его номер телефона: ");
    if (scanf("%zu", &del_sub) == 1)
        del_by_phone(del_sub, subs, size);
    else
        printf("\tОшибка: Такой абонемент не существует!\n");
}

size_t add_personal_info(subscriber_t *sub, const size_t *size)
{
    size_t index = 0; // индекс вводимого абонемента
    
    if (*size > MAX_ARR_SIZE)
    {
        printf("\tОшибка: Таблица полная!\n");
        return OVERFLOW_ERROR;
    }

    printf("\tВведите фамилию абонемента: ");
    size_t rc = input_string(sub[index].last_name);

    if (rc == OK)
    {
        printf("\tВведите имя абонемента: ");
        rc = input_string(sub[index].first_name);

        if (rc == OK)
        {
            printf("\tВведите номер телефона абонемента: ");
            if (scanf("%zu", &sub[index].phone) != 1)
            {
                printf("\tОшибка: Неправильно ввели номер телефона!\n");
                printf("\tНомер телефона содержит только цифры!\n");
                rc = PHONE_ERROR;
            }
        }
        else
            printf("\tОшибка: Неправильно указали имя абонемента!\n");
    }
    else
        printf("\tОшибка: Неправильно указали фамилию абонемента!\n");

    if (rc == OK)
    {
        printf("\tВведите название улицы проживания абонемента: ");
        rc = input_string(sub[index].street);

        if (rc == OK)
        {
            printf("\tВведите дом проживания абонемента: ");
            rc = input_string(sub[index].house);

            if (rc != OK)
                printf("\tОшибка: Неправильно указали дом проживания абонемента!\n");
        }
        else
            printf("\tОшибка: Неправильно указали название улицы проживания абонемента!\n");
    }
    return rc;
}

size_t add_status(subscriber_t *sub)
{
    size_t index = 0;
    char buff[MAX_DATA_SIZE]; // буффер
    size_t day, mounth, year; // вспомагательные переменные для дня, месяця и лет

    printf("\tВведите статус абонемента(personal/company): ");
    size_t rc = input_string(buff);

    if (rc == OK && strcmp(buff, "personal") == 0)
    {
        sub[index].status = 0;

        printf("\tВведите день месяц и год рождения абонемента: ");
        if (scanf("%zu%zu%zu", &day, &mounth, &year) == 3)
        {
            rc = check_birthday(day, mounth, year);

            if (rc == OK)
            {
                sub[index].subs_info.person_info.birthday.day = day;
                sub[index].subs_info.person_info.birthday.month = mounth;
                sub[index].subs_info.person_info.birthday.year = year;
            }
            else
                printf("\tОшибка: Неправильно ввели день рождения абонемента!\n");
        }
        else
        {
            printf("\tОшибка: Неправильно ввели день рождения абонемента!\n");
            rc = BIRTHDAY_ERROR;
        }
    }
    else if (rc == OK && strcmp(buff, "company") == 0)
    {
        sub[index].status = 1;

        printf("\tВведите должность абонемента: ");
        rc = input_string(sub[index].subs_info.company_info.name);
        
        if (rc == OK)
        {
            printf("\tВведите название организации/компании, где работает абонемент: ");
            rc = input_string(sub[index].subs_info.company_info.position);
            
            if (rc != OK)
                printf("\tОшибка: Неправильно ввели название организации/компании, где работает абонемент!\n");
        }
        else
            printf("\tОшибка: Неправильно ввели название организации/компании, где работает абонемент!\n");
    }
    else
    {
        printf("\tОшибка: Неправильно указалы статус абонемента!\n");
        rc = STATUS_ERROR;
    }
    return rc;
}

void add_subs(subscriber_t *subs, size_t *size)
{
    subscriber_t sub[MAX_ARR_SIZE]; // структура абонемента
    size_t temp_index = 0; // временный индекс
    
    size_t rc = add_personal_info(sub, size);
    
    if (rc == OK)
    {
        rc = add_status(sub);

        if (rc == OK)
        {
            strcpy(subs[*size].last_name, sub[temp_index].last_name);
            strcpy(subs[*size].first_name, sub[temp_index].first_name);
            subs[*size].phone = sub[temp_index].phone;
            strcpy(subs[*size].street, sub[temp_index].street);
            strcpy(subs[*size].house, sub[temp_index].house);
            subs[*size].status = sub[temp_index].status;
            
            if (sub[temp_index].status == personal)
            {
                subs[*size].subs_info.person_info.birthday.day = sub[temp_index].subs_info.person_info.birthday.day;
                subs[*size].subs_info.person_info.birthday.month = sub[temp_index].subs_info.person_info.birthday.month;
                subs[*size].subs_info.person_info.birthday.year = sub[temp_index].subs_info.person_info.birthday.year;
            }
            else
            {
                strcpy(subs[*size].subs_info.company_info.position, sub[temp_index].subs_info.company_info.position);
                strcpy(subs[*size].subs_info.company_info.name, sub[temp_index].subs_info.company_info.name);
            }
            
        }
        
        *size += 1;
    }
}

size_t has_birthday_soon(const subscriber_t subs)
{
    size_t rc = FALSE; // код возврата

    if (subs.status == personal)
        if (subs.subs_info.person_info.birthday.day > 14 && \
            subs.subs_info.person_info.birthday.day < 23 && subs.subs_info.person_info.birthday.month == 10)
            rc = TRUE;
    
    return rc;
}

void find_birthday(const subscriber_t *subs, const size_t size)
{
    for (size_t index = 0; index < size; index++)
        if (has_birthday_soon(subs[index]))
            print_birthday_subs(subs[index]);
}