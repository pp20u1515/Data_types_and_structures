#include "../inc/struct.h"
#include "../inc/return_codes.h"
#include "../inc/io_funcs.h"
#include "../inc/table_funcs.h"
#include "../inc/sort_funcs.h"
#include "../inc/additional_funcs.h"

#include <stdio.h>
#include <string.h>

#define MAX_ARR_SIZE 1000
#define MAX_LEN_ANSWER 3

int main()
{
    subscriber_t subscriber[MAX_ARR_SIZE + 1]; // сктруктура абонемента
    key_t key[MAX_ARR_SIZE]; // массив ключей
    size_t size = 0; // количество абонементов
    size_t rc = OK; // код возврата
    int choice = -1; // выбор варианта в меню
    char answer_char[MAX_LEN_ANSWER];
    FILE *f_open = fopen("./func_tests/data/table_1000.txt", "r");

    if (f_open)
    {
        read_file(subscriber, f_open, &size);
        create_key_arr(subscriber, key, size);
        
        while (choice != 0)
        {
            menu();
            printf("\n\tВыберите действие: ");
            
            scanf("%s", answer_char);
            choice = atoi(answer_char);

            while (!choice)
            {
                if (strcmp(answer_char, "0") == 0)
                    break;

                printf("\tОшибка: Неправильный ввод!\n");

                printf("\n\tВыберите действие: ");
                scanf("%s", answer_char);
                choice = atoi(answer_char);
            }
            switch (choice)
            {
                case (0):
                    printf("\tПрограмма завершена!\n");
                    return OK;
                case (1):
                    show_table(subscriber, size);
                    break;
                case (2):
                    print_key(key, size);
                    break;
                case (3):
                    show_sorted_table_by_key(subscriber, key, size);
                    break;
                case (4):
                    add_subs(subscriber, &size);
                    create_key_arr(subscriber, key, size);
                    break;
                case (5):
                    del_subs(subscriber, &size);
                    create_key_arr(subscriber, key, size);
                    break;
                case (6):
                    sort_table(subscriber, size);
                    break;
                case (7):
                    sort_keys(key, size);
                    break;
                case (8):
                    find_birthday(subscriber, size);
                    break;
                case (9):
                    effency_sorting(subscriber, size);
                    break;
                default:
                    printf("\tОшибка: Неправильный ввод!\n");
                    break;
            }
        }
        fclose(f_open);
    }
    else
    {
        printf("\tОшибка: Не удалось открыть файл!\n");
        rc = FOPEN_ERROR;
    }

    return rc;
}