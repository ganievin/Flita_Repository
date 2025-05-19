#include "graphviz/cgraph.h"
#include "graphviz/gvc.h"
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

int txt_to_png(GVC_t *gvc)
{
    Agraph_t *g = agopen("GRAPH", Agundirected, NULL);

    char search_path[100];
    char file_name[50];
    FILE *graph_file = NULL;

    puts("enter file name without format (must be in 'lists_of_edges_txt' directory)\n");
    while(1)
    {
        scanf("%49s", file_name);

        snprintf(search_path, sizeof(search_path),"./lists_of_edges_txt/%s.txt", file_name);
        graph_file = fopen(search_path, "r");

        if (graph_file != NULL)
            break;
        else
            puts("No such file. Try again.\n");
    }

    char curr_symb[2];
    while ((*curr_symb = fgetc(graph_file)) != EOF)
    {
           Agnode_t *tail_node = agnode(g, curr_symb, TRUE);
           fgetc(graph_file); //пропускаем ровно один пробел между цифрами в тесктовом файле
           *curr_symb = fgetc(graph_file);
           Agnode_t *head_node = agnode(g, curr_symb, TRUE);
           agedge(g, tail_node, head_node, NULL, TRUE);
           fgetc(graph_file);//пропускаем ровно одну табул€цию в тесктовом файле
    }


    char first_name[1];
    Agnode_t *first_node = NULL;
    char second_name[1];
    Agnode_t *second_node = NULL;
    while(1)
    {
        puts("enter two node names\n");

        puts("first node name: ");
        scanf("%1s", first_name);
        first_node = agnode(g, first_name, FALSE);
        puts("second node name: ");
        scanf("%1s", second_name);
        second_node = agnode(g, second_name, FALSE);

        /*if (strcmp(file_name, "done") == 0)
            return 0; */

        if ((first_node != NULL) && (second_node != NULL))
        {
            agedge(g, first_node, second_node, NULL, TRUE);
            break;
        }
        else
            puts("\nNo such nodes. Try again.\n");
    }
    fclose(graph_file);

    gvLayout (gvc, g, "dot");

    char png_save_path[100] = "./lists_of_edges_png/";

    strcat(png_save_path, file_name);
    strcat(png_save_path, ".png");

    gvRenderFilename (gvc, g, "png", png_save_path);
    gvFreeLayout(gvc, g);

    printf("Rendered and saved as %s.png\n", file_name);

    agclose(g);
    return 1;
}


int main(void)
{
    GVC_t *gvc = gvContext();
    txt_to_png(gvc);
    return (gvFreeContext(gvc));
}
