#include "return_codes.h"
#include "io_funcs.h"
#include "tree_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSWER_LEN 3

int main(int argc, char **argv)
{
    tree_node_t *tree = NULL, *balanced_tree = NULL; // Структура дерева
    hash_t *hash_table = NULL; // Структура хеш-таблицы
    int choice = -1; // Выбор действия
    char choice_answer[ANSWER_LEN];
    clock_t start, end;
    
    while (choice != 0)
    {
        menu();
        
        printf("\tВыберите действие: ");
        scanf("%s", choice_answer);
        choice = atoi(choice_answer);

        while (!choice)
        {
            if (strcmp(choice_answer, "0") == 0)
                break;

            printf("\tОшибка: Вы выбрали неправильное действие!\n");
            printf("\tВыберите действие: ");

            scanf("%s", choice_answer);
            choice = atoi(choice_answer);
        }
        switch(choice)
        {
            case (0):
                printf("\tПрограмма завершена!\n");
                return OK;
            case (1):
                if (tree == NULL && balanced_tree == NULL)
                {
                    read_tree(&tree, &balanced_tree, argv[1]);
                    read_table(&hash_table, argv[1]);
                }
                else
                    printf("\tДерево построено!\n");

                break;
            case (2):
                if (tree != NULL && balanced_tree != NULL)
                {
                    show_tree(&tree, argv[2]);
                    show_tree(&balanced_tree, argv[3]);
                    show_hash_table(hash_table);
                    //system("xdot ./func_tests/data/output_btree.dot");
                    //system("xdot ./func_tests/data/output_balanced_tree.dot");
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
            
                break;
            case (3):
                if (tree != NULL && balanced_tree != NULL)
                {
                    search_word(&tree, &balanced_tree, &hash_table);
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            default:
                printf("\tОшибка: Вы выбрали неправильное действие!\n");
        }
    }
    return OK;
}
