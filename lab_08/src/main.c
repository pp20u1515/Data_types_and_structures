#include "graph_funcs.h"
#include "io_funcs.h"
#include "return_codes.h"

#include <stdlib.h>
#include <string.h>

#define ANSWER_BUFF 3

int main(int argc, char **argv)
{
    matrix_t *graph = NULL;
    int choice = -1;
    char choice_answer[ANSWER_BUFF];
    size_t flag = 0;
    
    while (argc == 4 && choice != 0)
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

        switch (choice)
        {
            case (0):
                printf("\tПрограмма завершена!\n");
                return OK;
            case (1):
                if (graph == NULL)
                    read_graph(&graph, argv[1]);
                else
                    printf("\tГраф уже построен!\n");

                break;
            case (2):
                if (graph != NULL)
                {
                    to_dot(graph, argv[2]);
                    system("xdot ./func_tests/data/graph.dot");
                }
                else
                    printf("\tОшибка: Граф пустой!\n");
                break;
            case (3):
                if (graph != NULL)
                    print_matrix(graph);
                else
                    printf("\tОшибка: Матрица пустая!\n");
                break;
            case (4):
                if (graph != NULL)
                {
                    find_nodes_with_Dijkstra(&graph, argv[3], &flag);

                    if (flag == 1)
                        system("xdot ./func_tests/data/task.dot");
                    else
                        printf("Не успели найти такой путь!\n");
                }
                else
                    printf("\tОшибка: Граф пустой!\n");
                break;

            case (5):
                timeget();
                break;

            default:
                printf("\tОшибка: Неправильно выбрали действие!\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}
