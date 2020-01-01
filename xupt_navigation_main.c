#include "xupt_navigation_menu.h"
#include "sql.h"

int main()
{
    sql_init();
    adj_matrix *G = (adj_matrix *)malloc(sizeof(adj_matrix));
    create_gragh(G);
    show_main_menu(G);
    return 0;
}
