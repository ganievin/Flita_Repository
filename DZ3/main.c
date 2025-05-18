#include "graphviz/cgraph.h"
#include "graphviz/gvc.h"
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define ONE_CHAR_AND_STR_END 2
#define LONG_ENOUGH 100
#define LONG 50

//copied DFC code, raw
void DFS(struct Graph* graph, int vertex) {
    //creating an array which maintaining string names of visited nodes (names has length 2 - one character and \0)
    char **visited = (char **)malloc(nodes_num_in_graph * sizeof(curr_symb));
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while(temp!=NULL) {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

   /*just tested some features, code only for reference
    Agnode_t *n = NULL;
    n = agfstnode(g);
    for (int i = 0; i<2; i++) {
        agsafeset(n, "color", "red", "");
        n = agnxtnode(g,n);
    }*/

int txt_to_png(GVC_t *gvc)
{
    Agraph_t *g = agopen("GRAPH", Agundirected, NULL);

    char search_path[LONG_ENOUGH];
    char file_name[LONG];
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

    char curr_symb[ONE_CHAR_AND_STR_END];
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

    char png_save_path[LONG_ENOUGH] = "./lists_of_edges_png/";

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
