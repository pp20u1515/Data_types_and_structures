#include "../inc/sort_funcs.h"
#include "../inc/return_codes.h"
#include "../inc/additional_funcs.h"

#include <time.h>
#include <string.h>
#include <stdio.h>

#define MAX_ARR_SIZE 1000

void bubble_sort_table(subscriber_t *subs, const size_t size)
{
    subscriber_t temp_subs; // временная переменная
    
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size - 1; j++)
            if (subs[j].phone > subs[j + 1].phone)
            {
                temp_subs = subs[j];
                subs[j] = subs[j + 1];
                subs[j + 1] = temp_subs;
            }
}

int sub_phone_cmp(const void *a, const void *b)
{
    subscriber_t sub_a = *(const subscriber_t *)a;
    subscriber_t sub_b = *(const subscriber_t *)b;

    return sub_a.phone - sub_b.phone;
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void sort_table(subscriber_t *subs, const size_t size)
{
    size_t choice; // выбор

    printf("\t\t1)BubbleSort\n");
    printf("\t\t2)QuickSort\n\n");
    printf("\tВыберите сортировку: ");
    if(scanf("%zu", &choice) == 1)
    {
        if (choice == 1)
            bubble_sort_table(subs, size);
        else if (choice == 2)
            qsort(subs, size, sizeof(subscriber_t), sub_phone_cmp);
        else
            printf("\tОшибка: Неправильно выбрали сортировку!\n");
    }
    else
        printf("\tОшибка: Неправильно выбрали сортировку!\n");
}

void sort_keys(key_t *key, const size_t size)
{
    bubble_sort_key(key, size);
}

void bubble_sort_key(key_t *key, const size_t size)
{
    size_t temp; // вспомагательная переменная

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size - 1; j++)
            if (key[j].key > key[j + 1].key)
            {
                temp = key[j].key;
                key[j].key = key[j + 1].key;
                key[j + 1].key = temp;

                temp = key[j].cout;
                key[j].cout = key[j + 1].cout;
                key[j + 1].cout = temp;
            }
}

void effency_sorting(const subscriber_t *subs, const size_t size)
{
    subscriber_t temp_subs[MAX_ARR_SIZE]; // вспомагательная структура
    key_t key[MAX_ARR_SIZE]; // массив ключей
    double array_time[4] = { 0 }; // время сортировки
    clock_t start, end; // начало и конец времени

    copy_struct(temp_subs, subs, size);
    
    // buble sort
    start = clock();
    bubble_sort_table(temp_subs, size);
    end = clock();
    array_time[0] = (end - start) / (CLOCKS_PER_SEC * 1.0);
    
    // qsort
    start = clock();
    qsort(temp_subs, size, sizeof(subscriber_t), sub_phone_cmp);
    end = clock();
    array_time[1] = (end - start) / (CLOCKS_PER_SEC * 1.0);

    // bubble sort key
    start = clock();
    bubble_sort_key(key, size);
    end = clock();
    array_time[2] = (end - start) / (CLOCKS_PER_SEC * 1.0);

    //qsort_key
    start = clock();
    qsort(key, size, sizeof(long int), compare);
    end = clock();
    array_time[3] = (end - start) / (CLOCKS_PER_SEC * 1.0);

    printf("\tОценка эффективности сортировoк (в секундах) при %zu элементов:\n", size);
    printf("+---------+---------------+------------+\n");
    printf("|         |  Bubble sort  |    qsort   |\n");
    printf("| Таблица |%-9f sec  |%-5f sec|\n", array_time[0], array_time[1]);
    printf("|   key   |%-9f sec  |%-5f sec|\n", array_time[2], array_time[3]);
    printf("+---------+---------------+------------+\n");
    printf("\tОбъем памяти: %zu\n", size * sizeof(size_t));
    printf("\tРазница по времени (Bubble_sort_table) / (Bubble_sort_key): %.2lf\n", array_time[0] / array_time[2]);
    printf("\tРазница по времени (qsort_table) / (qsort_key): %.2lf\n", array_time[1] / array_time[3]);
}

void sort_table_by_key(const subscriber_t *subs, const key_t *key, const size_t size)
{
    subscriber_t temp_subs[MAX_ARR_SIZE];
    subscriber_t temp_subs2[MAX_ARR_SIZE];

    copy_struct(temp_subs, subs, size);

    for (size_t index_i = 0; index_i < size; index_i++)
    {
        for (size_t index_j = 0; index_j < size; index_j++)
            if (key[index_i].key == temp_subs[index_j].phone)
            {
                temp_subs2[index_i] = temp_subs[index_j];
            }
    }
    print_table_by_key(temp_subs2, key, size);
}

void print_table_by_key(const subscriber_t *sub, const key_t *key, const size_t size)
{
    printf("+-------+---------------+------------+--------------+--------------");
    printf("+-----------------+--------+------------------+---------------------+\n");
    printf("| Index |   Last name   | First name | Phone number |    Street    | Number of house ");
    printf("| Status | Data of birthday |   Official status   |\n");
    
    for (size_t index = 0; index < size; index++)
    {   
        printf("|%-7d|%-15s|%-12s|%-14zu|%-14s|%-17s|%-8d|", key[index].cout, sub[index].last_name,\
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