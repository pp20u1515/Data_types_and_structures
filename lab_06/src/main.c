#include "return_codes.h"
#include "io_funcs.h"

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
                printf("\tПрограмма завершена!");
                return OK;
            case (1):
                if (tree == NULL)
                    read_tree(&tree);
                else
                    printf("\tДерево построено!\n");

                break;
            case (2):
                if (tree != NULL)
                    show_tree(&tree);
                else
                    printf("\tОшибка: Дерево пустое!\n");
            
                break;
            case (3):
                if (tree != NULL)
                {
                    search_letter(&tree, &start, &end);
                }
                else
                    printf("\tОшибка: Дерево пустое!\n");
                break;
            case (4):
                if (tree != NULL)
                {
                    printf("\tВремя поиска буквы в дерево: %.6f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
                    
                    search_file(&start, &end);
                    printf("\tВремя поиска буквы в файле: %.6f сек.\n", (end - start) / (CLOCKS_PER_SEC * 1000000.0));
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