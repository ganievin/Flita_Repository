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

    puts("\nenter file name without format (must be in 'lists_of_edges_txt' directory)\nor 'done' to terminate app window\n");
    while(1)
    {
        scanf("%49s", file_name);
        if (strcmp(file_name, "done") == 0)
            return 0;

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
    fclose(graph_file);

    gvLayout (gvc, g, "dot");

    char png_save_path[100] = "./lists_of_edges_png/";

    strcat(png_save_path, file_name);
    strcat(png_save_path, ".png");

    gvRenderFilename (gvc, g, "png", png_save_path);
    gvFreeLayout(gvc, g);
    agclose(g);
    printf("Rendered and saved as %s.png\n", file_name);
    return 1;
}


int main(void)
{
    GVC_t *gvc = gvContext();
    while (txt_to_png(gvc));
    return (gvFreeContext(gvc));
}
