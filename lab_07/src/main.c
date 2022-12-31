#include <stdio.h>
#include <stdlib.h>

#include "../inc/constants.h"
#include "../inc/io.h"
#include "../inc/tree_ddp.h"
#include "../inc/tree_avl.h"
#include "../inc/hash.h"
#include "../inc/graphviz.h"
#include "../inc/compare_structures.h"
#include "../inc/time.h"
#include "../inc/hash_closed.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Ошибка ввода аргументов.\n");
        return 1;
    }
    tree_t *root = NULL;
    tree_t *balance = NULL;
    hash_table_t table;
    hash2_t *table2;

    int size = 0;
    FILE *in_file;

    int process = START;
    int command;
    int flag = 0;
    char answer;

    while (process)
    {
        print_menu();
        int code = input_command(&command);

        if (code)
        {
            printf("\nКоманда введена неверно.\n");
            print_menu();
        }
        else if (command == INPUT_FROM_FILE)
        {
            in_file = fopen(argv[1], "r");

            if (!in_file)
                printf("\nОшибка открытия файла.\n");
            else
            {
                create_tree(&root, in_file, &size);
                rewind(in_file);

                if (size == 0)
                    printf("\nФайл пуст.\n");
                else
                {
                    create_tree_avl(&balance, in_file);
                    rewind(in_file);

                    hash_table_init(&table, size);
                    create_hash_table(in_file, &table);
                    rewind(in_file);
                    read_table(&table2, in_file);
                }
            }
        }
        else if (command == PRINT_BST)
        {
            if (size == 0)
                printf("\nДерево не загружено из файла\n");
            else
            {
                printf("\n\nДерево двоичного поиска: tree_ddp.png\n\n");
                tree_export_to_dot_ddp(root);
            }
        }
        else if (command == PRINT_BALANCE)
        {
            if (size == 0)
                printf("\nДерево не загружено из файла\n");
            else
            {
                printf("\n\nСбалансированное дерево: tree_avl.png\n\n");
                tree_export_to_dot_avl(balance);
            }
        }
        else if (command == PRINT_HASH_TABLE)
        {
            if (size == 0)
                printf("\nДерево не загружено из файла\n");
            else
            {
                printf("\n\nХеш-таблица:\n\n");
                print_table(&table);
                show_hash_table(table2);
            }
        }
        else if (command == SEARCH)
        {
            if (size == 0)
                printf("\nДерево не загружено из файла\n");
            else
            {
                char word[WORD_SIZE];
                int count_cmprs, code = 0, cmprs = 0;

                printf("\n\nВведите слово для поиска: ");
                scanf("%s", word);
                printf("\nВведите допустимое число сравнений в хеш-таблице: ");
                int rc = scanf("%d", &count_cmprs);

                if (!rc || count_cmprs < 1)
                    printf("\nНеверное число сравнений\n");
                else
                {
                    printf("\n\nПоиск в дереве двоичного поиска\n");
                    uint64_t start = get_time_ticks();
                    code = find_tree(root, word, &cmprs);
                    uint64_t time = get_time_ticks() - start;

                    if (code == OK)
                        printf("\nСлово %s найдено\n"
                            "Дерево двоичного поиска занимает - %ld байт\n"
                            "Число сравнений до искомого слова - %d \n",
                            word, size * sizeof(tree_t), cmprs);
                    else
                    {
                        printf("\nЭлемент не найден\n");
                        flag = 1;
                    }

                    cmprs = 0;
                    printf("\n\nПоиск в сбалансированном дереве\n");
                    start = get_time_ticks();
                    code = find_tree(balance, word, &cmprs);
                    time = get_time_ticks() - start;

                    if (code == OK)
                        printf("\nСлово %s найдено\n"
                            "Сбалансированное дерево занимает - %ld байт\n"
                            "Число сравнений до искомого слова - %d \n",
                            word, size * sizeof(tree_t), cmprs);
                    else
                        printf("\nЭлемент не найден\n");

                    rewind(in_file);
                    cmprs = 0;
                    printf("\n\nПоиск в таблице\n");
                    time = 0;
                    code = 0;
                    hash_find_time(&table, word, &cmprs, &time, &code, count_cmprs);

                    if (code == OK)
                        printf("\nСлово %s найдено\n"
                            "Хеш-таблица занимает - %ld байт\n"
                            "Число сравнений до искомого слова - %d \n",
                            word, find_table_size(&table), cmprs);
                    else if (code == RESTRUCT)
                    {
                        printf("\nЭлемент найден, но требуется реструктуризация\n");
                        restructuring(in_file, &table);
                        rewind(in_file);

                        printf("\nНовая хеш-таблица:\n");
                        print_table(&table);
                    }
                    else
                        printf("\nЭлемент не найден\n");

                    rewind(in_file);
                    cmprs = 0;
                    printf("\n\nПоиск в файле\n");
                    start = get_time_ticks();
                    code = search_file(word, in_file, &cmprs);
                    time = get_time_ticks() - start;

                    if (code == OK)
                        printf("\nСлово %s найдено\n"
                            "Файл занимает - %d байт\n"
                            "Число сравнений до искомого слова - %d \n",
                            word, file_bytes(in_file), cmprs);
                    else
                        printf("\nЭлемент не найден\n");

                    if (flag == 1)
                    {
                        printf("Хотите добавить элемент(y/n): ");
                        scanf(" %c", &answer);

                        if (answer == 'y')
                        {
                            add_to_tree(&root, word);
                            add_to_avl(&balance, word);
                        }
                    }
                    compare_structures();
                }
            }
        }
        else if (command == END)
        {
            process = END;
        }
    }

    return OK;
}