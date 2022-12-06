#include "return_codes.h"
#include "io_funcs.h"
#include "tree_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSWER_LEN 3

int main()
{
    tree_node_t *tree = NULL;
    int choice = -1;
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
                if (tree == NULL)
                {
                    read_tree(&tree);
                    read_tree2(&tree);
                }
                else
                    printf("\tДерево построено!\n");

                break;
            case (2):
                if (tree != NULL)
                {
                    show_tree(&tree);
                    system("xdot ./func_tests/data/output_first_tree.dot");
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
            
                break;
            case (3):
                add_node(&tree);
                break;
            case (4):
                if (tree != NULL)
                {
                    search_letter(&tree, &start, &end);
                    system("xdot ./func_tests/data/painted_tree.dot");
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            case (5):
                if (tree != NULL)
                {
                    search_word(&tree);
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            case (6):
                if (tree != NULL)
                {
                    delete_node(&tree);
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            case (7):
                if (tree != NULL)
                {
                    printf("\tВремя поиска буквы в дерево: %.6f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
                    
                    search_file(&start, &end);
                    printf("\tВремя поиска буквы в файле: %.6f сек.\n", (double)(end - start) / CLOCKS_PER_SEC );
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            case (8):
                if (tree != NULL)
                {
                    start = clock();
                    sort_tree(&tree);
                    end = clock();
                    printf("\tВремя сортировки дерева: %.6f\n", (double)(end - start) / CLOCKS_PER_SEC);

                    start = clock();
                    sort_file();
                    end = clock();
                    printf("\tВремя сортировки файла: %.6f\n", (double)(end - start) / CLOCKS_PER_SEC);
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
