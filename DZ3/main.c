#include "graphviz/cgraph.h"
#include "graphviz/gvc.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#define ONE_CHAR_AND_STR_END 2
#define LONG_ENOUGH 100
#define LONG 50


typedef struct node_status
{
        Agnode_t *node;
        bool status;
        Agnode_t **adj_nodes;
}node_st;

Agnode_t **adj_list_maker(Agraph_t *g, Agnode_t *node)
{
    int i, k;
    Agnode_t *current_node = agfstnode(g);
    Agnode_t **adj_list = (Agnode_t **)malloc(agnnodes(g)*sizeof(Agnode_t *));

    for (i = 0; i < agnnodes(g); i++)
        adj_list[i] = NULL;

    for (k = 0; current_node; current_node = agnxtnode(g, current_node))
    {
        if (agedge(g,node,current_node,NULL,FALSE) && (node != current_node))
        {
            adj_list[k] = current_node;
            k++;
        }
    }
    return adj_list;
}

node_st ** create_node_list (Agraph_t *g)
{
    int nodes_num = agnnodes(g);
    int i;
    Agnode_t *current_node = agfstnode(g);
    node_st **node_list = (node_st **)malloc(nodes_num*sizeof(node_st *));
    for (i = 0; i < nodes_num && current_node; i++, current_node = agnxtnode(g, current_node))
    {
        node_list[i] = (node_st *)malloc(sizeof(node_st));
        node_list[i] -> node = current_node;
        node_list[i] -> status = false;
        node_list[i] -> adj_nodes = adj_list_maker(g, current_node);
    }
    return node_list;
}

int DFS(Agraph_t* g, node_st **node_list, node_st *start_node)
{
    int nodes_num = agnnodes(g);
    int i, j, k;
        for (i = 0; i < nodes_num; i++)
        {
            if (node_list[i] == start_node)
            {
                node_list[i]->status = true;
            }
        }

        node_st *neighbour = NULL;
        for (j = 0; j < nodes_num; j++)
        {
            neighbour = node_list[j];
            if (neighbour -> status == true)
            {
                continue;
            }
            else
            {
                for (k = 0; k < nodes_num; k++)
                {
                    if (start_node -> adj_nodes[k] == neighbour -> node)
                    {
                        DFS(g, node_list, neighbour);
                    }
                }
            }
        }
    int visited = 0;
    for (int p = 0; p < nodes_num; p++)
        {
            if (node_list[p] -> status == true)
            {
                visited++;
                agsafeset(node_list[p] -> node, "color", "black", "");
            }
            else
            {
                agsafeset(node_list[0] -> node, "color", "blue", "");
                agsafeset(node_list[p] -> node, "color", "red", "");
            }
        }
    return visited;
}

int txt_to_png(GVC_t *gvc)
{
    Agraph_t *g = agopen("GRAPH", Agundirected, NULL);

    char search_path[LONG_ENOUGH];
    char file_name[LONG];
    FILE *graph_file = NULL;

    puts("ENTER file name without format (must be in 'lists_of_edges_txt' directory)\nor 'done' to terminate app window:");
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

    node_st** node_list = create_node_list(g);
    int visited_nods = DFS(g, node_list, node_list[0]);
    visited_nods == agnnodes(g) ?
    puts("\n--------------------------------------------------------------------------\n"
        "graph connected\n"
        "--------------------------------------------------------------------------\n")
    : puts("\n--------------------------------------------------------------------------\n"
           "graph not connected: there's no edges between blue node and every red node\n"
           "--------------------------------------------------------------------------\n");

    fclose(graph_file);

    gvLayout (gvc, g, "dot");

    char png_save_path[LONG_ENOUGH] = "./lists_of_edges_png/";

    strcat(png_save_path, file_name);
    strcat(png_save_path, ".png");

    gvRenderFilename (gvc, g, "png", png_save_path);
    gvFreeLayout(gvc, g);
    agclose(g);
    printf("-------------------------------------------------------------------------\n"
           "Rendered and saved as %s.png\n"
           "--------------------------------------------------------------------------\n\n\n", file_name);
    return 1;
}


int main(void)
{
    GVC_t *gvc = gvContext();
    while (txt_to_png(gvc));
    return (gvFreeContext(gvc));

}
