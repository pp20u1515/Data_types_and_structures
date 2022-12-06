#include "../inc/return_codes.h"
#include "../inc/io_funcs.h"
#include "../inc/struct.h"
#include "../inc/additional_funcs.h"
#include "../inc/sort_funcs.h"

#include <stdio.h>
#include <string.h>

#define MAX_DATA_SIZE 100
#define MAX_ARR_SIZE 1000
#define PERSONAL 0
#define COMPANY 1

void menu()
{
    printf("\t\t\t\tМеню\n\n");
    printf("\t\tДоступные действия:\n");
    printf("\t1) Показать таблицу данных.\n\
    \t2) Показать массив ключей (номер телефона)\n\
    \t3) Показать исходную таблицу в упорядоченном виде, используя упорядоченную\n\
    \tтаблицу ключе.\n\
    \t4) Добавить запись в таблицу.\n\
    \t5) Удалить запись из таблицы.\n\
    \t6) Отсортировать таблицу по номеру телефона.\n\
    \t7) Отсортировать массив ключей, где ключ - номер телефона абонементa\n\
    \t8) Найти абонементов, у которых скоро день рождения!\n\
    \t9) Оценить эффективность сортировок.\n\
    \t0) Завершить программу.\n");
}

void read_file(subscriber_t *subs, FILE *f_open, size_t *size)
{
    *size = 0; // количество абонементов
    size_t index = 0;

    while (!feof(f_open))
    {
        fscanf(f_open,"%s%s%zu%s%s%u", subs[index].last_name, subs[index].first_name,\
        &subs[index].phone, subs[index].street, subs[index].house, &subs[index].status);
        if (subs[index].status == PERSONAL)
            fscanf(f_open, "%zu%zu%zu", &subs[index].subs_info.person_info.birthday.day,\
            &subs[index].subs_info.person_info.birthday.month, &subs[index].subs_info.person_info.birthday.year);
        else if (subs[index].status == COMPANY)
            fscanf(f_open, "%s%s", subs[index].subs_info.company_info.position, \
            subs[index].subs_info.company_info.name);
        
        *size = index + 1;
        index++;
    }
}

size_t input_string(char *string)
{
    size_t rc = OK; // код возврата 
    char temp_string; // вспомагательная переменная
    size_t index = 0; // индекс
    
    scanf(" %c", &temp_string);
    
    while (rc == OK && temp_string != '\n')
        if (strlen(string) <= MAX_DATA_SIZE + 1)
        {
            string[index++] = temp_string;
            scanf("%c", &temp_string);
        }
        else
            rc = DATA_ERROR;
    
    string[index] = '\0';
    
    if (index == 0)
        rc = DATA_ERROR;
    
    return rc;
}

void show_table(const subscriber_t *sub, const size_t size)
{
    printf("+-------+---------------+------------+--------------+--------------");
    printf("+-----------------+--------+------------------+---------------------+\n");
    printf("| Index |   Last name   | First name | Phone number |    Street    | Number of house ");
    printf("| Status | Data of birthday |   Official status   |\n");
    
    for (size_t index = 0; index < size; index++)
    {   
        printf("|%-7zu|%-15s|%-12s|%-14zu|%-14s|%-17s|%-8d|", index, sub[index].last_name,\
        sub[index].first_name, sub[index].phone, sub[index].street,\
        sub[index].house, sub[index].status);

        if (sub[index].status == personal)
            printf("%-2zu.%-2zu.%-11zu |                     |", sub[index].subs_info.person_info.birthday.day, \
            sub[index].subs_info.person_info.birthday.month, sub[index].subs_info.person_info.birthday.year);
        else if (sub[index].status == company)
            printf("                  |%-10s %-10s|", sub[index].subs_info.company_info.position, \
            sub[index].subs_info.company_info.name);
        printf("\n");
    }
    printf("+-------+---------------+------------+--------------+--------------");
    printf("+-----------------+--------+------------------+---------------------+\n");
}

void print_key(const key_t *key, const size_t size)
{
    printf("+-------+-------------------+\n");
    printf("| Index | Key(phone number) |\n");
    for (size_t index = 0; index < size; index++)
        printf("|%-7d|%-19zu|\n", key[index].cout, key[index].key);
    printf("+-------+-------------------+\n");
}

void print_birthday_subs(const subscriber_t sub)
{
    printf("+---------------+------------+--------------+--------------");
    printf("+-----------------+--------+------------------+\n");
    printf("|   Last name   | First name | Phone number |    Street    | Number of house ");
    printf("| Status | Data of birthday |\n");

    printf("|%-15s|%-12s|%-14zu|%-14s|%-17s|%-8d|", sub.last_name,sub.first_name, \
    sub.phone, sub.street, sub.house, sub.status);

        if (sub.status == personal)
            printf("%-2zu.%-2zu.%-11zu|", sub.subs_info.person_info.birthday.day, \
            sub.subs_info.person_info.birthday.month, sub.subs_info.person_info.birthday.year);
    
    printf("\n");
    printf("+---------------+------------+--------------+--------------");
    printf("+-----------------+--------+------------------+\n");
}

void show_sorted_table_by_key(const subscriber_t *subs, const key_t *key, const size_t size)
{
    sort_table_by_key(subs, key, size);
}