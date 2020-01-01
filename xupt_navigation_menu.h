#ifndef XUPT_NAVIGATION_MENU_H
#define XUPT_NAVIGATION_MENU_H

#define MAX_NUM 50
#define INIT_NUM -1

typedef enum ma_status {
    INIT = 1,
    ONE,
    TOW,
    THREE,
    FOUR,
    FIVE,
    SIX,
    EXIT,
} ma_status_t;

typedef struct {
    int no;
    char name[50];
} vex_type;

typedef struct {
    int arcs[MAX_NUM+1][MAX_NUM+1];
    vex_type vex[MAX_NUM+1]; 
    int vexnum;//顶点数目
    int arcnum;//边数目
} adj_matrix;

void init();
void show_main_menu();
ma_status_t print_map();
void create_gragh(adj_matrix *G);
ma_status_t print_mess();
ma_status_t ask_directions();



#endif
