#include "xupt_navigation_menu.h"
#include "stack_list.h"
#include "sql.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clear_input_buffer()
{
    while(getchar() != '/')
        ;
}

int Locate(adj_matrix *G, char *name)
{
    for (int i = 1; i <= G->vexnum; i++) {
        if (!strcmp(G->vex[i].name, name)) {
            return i;
        }
    }
    return -1;
}

void create_gragh(adj_matrix *G)
{
    char vexnum[][50] = {{}, {"北门"}, {"水煮鸽子"}, {"基础教学楼"}, {"实验楼"}, {"图书馆"}, {"美广"}, {"西区宿舍"}, {"旭日大酒楼"}, {"操场"}, {"东门"}, {"天桥"}, {"西门"}, {"东区教学楼"}, {"东升小破餐厅"}, {"东区宿舍"}};  
    char edges[][2][50]={{},
    {{"北门"},{"基础教学楼"}}, {{"北门"},{"水煮鸽子"}}, {{"北门"},{"西门"}}, {{"基础教学楼"},{"水煮鸽子"}}, {{"实验楼"},{"基础教学楼"}}, {{"实验楼"},{"水煮鸽子"}},
    {{"图书馆"},{"水煮鸽子"}}, {{"实验楼"},{"图书馆"}}, {{"实验楼"},{"美食广场"}}, {{"图书馆"},{"美食广场"}}, {{"图书馆"},{"东门"}}, {{"图书馆"},{"操场"}},
    {{"东门"},{"操场"}}, {{"西区宿舍"},{"美食广场"}}, {{"图书馆"},{"旭日大酒楼"}}, {{"操场"},{"旭日大酒楼"}}, {{"西区宿舍"},{"旭日大酒楼"}}, {{"西门"},{"天桥"}}, {{"东升苑"},{"天桥"}},
    {{"东区宿舍"},{"天桥"}}, {{"东区宿舍"},{"东升小破餐厅"}}, {{"东区教学楼"},{"东升小破餐厅"}}, {{"东区教学楼"},{"东区宿舍"}}, {{"西门"},{"东区教学楼"}}, {{"东门"},{"天桥"}}}; 
    int weights[] = {0, 210, 129, 425, 109, 272, 228, 290, 145, 372, 364, 372, 201, 255, 144, 334, 133, 132, 359, 153, 451, 167, 317, 140, 24, 106};
    G->vexnum = 15;
    G->arcnum = 25;
    char name1[50], name2[50];
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 0; j <= G->vexnum; j++) {
            G->arcs[i][j] = INIT_NUM;
        }
    }
    for (int i = 1; i <= G->vexnum; i++) {
        G->vex[i].no = i;
        G->vex[i].stack_statu = -1;
        strcpy(G->vex[i].name, vexnum[i]);
    }
    int i, j;
    for (int k = 1; k <= G->arcnum; k++) {
        strcpy(name1, edges[k][0]);
        strcpy(name2, edges[k][1]);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weights[k];
        G->arcs[j][i] = weights[k];
    }
    //printf("地图初始化成功");
    /*for (int i = 1; i <= G->vexnum; i++) {
        printf("\n");
        for (int j = 1; j <= G->vexnum; j++) {
            printf("\t%d", G->arcs[i][j]);
        }
        printf("\n");
    }*/
}

void dfs(adj_matrix *G, int *visited, char *place_a, char *place_b, int p_a, int p_b, Stack S)
{
    if (!strcmp(place_b, G->vex[p_a].name)) {
        Stack tmp = S;                                      
        while (tmp->Next != NULL) {                         
            printf("%s<--", G->vex[tmp->Next->Element].name);
            tmp = tmp->Next;                                
        }                                                   
        printf("\n\n");                                       
        //sleep(1);
        G->vex[Top(S)].stack_statu = -1;                    
        Pop(S);                                             
        return;
    }
    int next = -1;
    for (int i = 1; i <= G->vexnum; i++) {
            if (G->arcs[p_a][i] != INIT_NUM && visited[i] == 0) {
                next = i;
                visited[next] = 1;
                Push(next, S);
                G->vex[next].stack_statu = 1;
                dfs(G, visited, place_a, place_b, next, p_b, S);
                visited[next] = 0;
            } 
    }
    Pop(S);
}

void ready_for_dfs(adj_matrix *G, char *place_a, char *place_b)
{
    int visited[G->vexnum+1]; 
    for (int i = 1; i <= G->vexnum; i++) {
        visited[i] = 0;
    }
    int p_a = -2, p_b = -2;
    for (int i = 1; i <= G->vexnum; i++) {
        if (!strcmp(place_a, G->vex[i].name)) {
            p_a = G->vex[i].no;                
        }                                      
    }
    for (int i = 1; i <= G->vexnum; i++) {     
        if (!strcmp(place_b, G->vex[i].name)) {
            p_b = G->vex[i].no;                
        }                                      
    }                                          
    visited[p_a] = 1;
    Stack S = CreateStack();
    Push(p_a, S);
    G->vex[p_a].stack_statu = 1;
    dfs(G, visited, place_a, place_b, p_a, p_b, S);
    clear_input_buffer();
}

void Dijkstra(adj_matrix  *G, int start, int end, int dist[], int path[][MAX_NUM+1]);

void Dij_Short_Path(adj_matrix *G) 
{
    char name[50];//choice = 'y';    //  
    int start, end;
    int dist[MAX_NUM+1];
        int path[MAX_NUM+1][MAX_NUM+1];
        for (int i = 1; i <= MAX_NUM; i++) {
            for (int j = 1; j <= MAX_NUM; j++) {
                path[i][j] = 0;
            }
        }
        printf("\n\t\t\t\t\t\t出发地：");
        scanf("%s", name);
        start = Locate(G, name);
        while(start == -1) 
        {   
            printf("\t\t\t\t\t\t无效输入,请重新输入:");
            scanf("%s", name);
            start = Locate(G,name);
        }   
        printf("\t\t\t\t\t\t目的地：");
        scanf("%s", name);
        end = Locate(G, name);
        while(end == -1) 
        {   
            printf("\t\t\t\t\t\t无效输入,请重新输入:");
            scanf("%s", name);
            end = Locate(G,name);
        }   
        Dijkstra(G, start, end, dist, path);
}

void Dijkstra(adj_matrix  *G, int start, int end, int dist[], int path[][MAX_NUM+1])
{
    int mindist, i, j, k, t = 1;
    
    //初始化
    for(i = 1; i <= G->vexnum; i++){        
        dist[i] = G->arcs[start][i];        //读入开始行的邻接信息
        if(G->arcs[start][i] != INIT_NUM)
            path[i][1] = start;
    }
    path[start][0] = 1;
    
    for(i = 2; i <= G->vexnum; i++){
        mindist = INIT_NUM;
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && dist[j] < mindist){
                mindist = dist[j];
                k = j;
            }
        }
        if(mindist == INIT_NUM)  break;
        path[k][0] = 1;
        
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && G->arcs[k][j] < INIT_NUM && G->arcs[k][j] + dist[k] < dist[j]){
                dist[j] = dist[k] + G->arcs[k][j];
               
                t = 1;
                while(path[k][t]){
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t+1] = 0;
            }
        }
    }
    if(dist[end] == INIT_NUM){
        printf("\n\t\t\t\t\t\t%s----->%s  不存在通路!!!\n", G->vex[start].name, G->vex[end].name);
        return;
    }
    printf("\n\t\t\t\t\t\t%s----->%s的最短路线：%s ", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for(j = 2; path[end][j]; j++) {
        printf("——>%s ", G->vex[path[end][j]].name);
    }
    printf("——>%s", G->vex[end].name);
    printf("\n\t\t\t\t\t\t距离为：%d\n", dist[end]);
    clear_input_buffer();
}

void Prim(adj_matrix *G, int start);
ma_status_t Prim_MiniSpanTree(adj_matrix *G)
{
    char name[50], choice = 'y';
    int start;
    printf("\t\t\t\t\t\t  最佳布网方案 \n");
    while(choice == 'y' || choice == 'Y'){
        printf("\t\t\t\t\t\t请输入起点：");
        scanf("%s", name);
        start = Locate(G, name);
        Prim(G, start);
        printf("\t\t\t\t\t\t是否继续查询(y || n): ");
        getchar();
        choice = getchar();
    }
    return INIT;
}

void Prim(adj_matrix *G, int start)
{
    struct{
        int adjvex;
        int lowcost;
        int pass;
    }closedge[MAX_NUM+1];
    int i, e, k, m, min;

    //初始化
    closedge[start].lowcost = 0;
    for(i = 1; i <= G->vexnum; i++){
        if(i != start){
        closedge[i].adjvex = start;
        closedge[i].lowcost = G->arcs[start][i];
        }
    }

    for(e = 1; e <= G->vexnum-1; e++){

        min = INIT_NUM;
        for(k = 1; k <= G->vexnum; k++){
            if(closedge[k].lowcost != 0 && closedge[k].lowcost < min){
                m = k;
                min = closedge[k].lowcost;
            }
        }
        printf("\t\t\t\t\t\t%s----->%s: 距离为%d\n", G->vex[closedge[m].adjvex].name, G->vex[m].name, closedge[m].lowcost);
        closedge[m].lowcost = 0;

        for(i = 1; i <= G->vexnum; i++){
            if(i != m && G->arcs[m][i] < closedge[i].lowcost){
                closedge[i].lowcost = G->arcs[m][i];
                closedge[i].adjvex = m;
            }
        }
    }

}

ma_status_t ask_directions(adj_matrix *G)
{
    char place_a[50], place_b[50];
    printf("\t\t\t\t\t\t~            1.所有路径              ~\n");//深搜将中转次数最少的路径标出来
    printf("\t\t\t\t\t\t~            2.最佳访问路线          ~\n");//地杰斯特拉
    int op = 0;
    scanf("%d", &op);
    if (op == 1) {
        printf("\n\t\t\t\t\t\t出发地：\t");
        scanf("%s", place_a);              
        printf("\n\t\t\t\t\t\t目的地：\t");
        scanf("%s", place_b);              
        ready_for_dfs(G, place_a, place_b);
    } else if (op == 2) {
        Dij_Short_Path(G); 
    }
    return INIT;
}


ma_status_t print_mess()
{
    char target_place[50];
    printf("\t\t\t\t\t\t查询地点: ");
    scanf("%s", target_place);
    printf("\n");
    char now_place[50];
    printf("\t\t\t\t\t\t当前位置：");
    scanf("%s", now_place);
    find(target_place, now_place);
    return INIT;
}

ma_status_t print_map()
{
    system("clear");
    printf("\t\t\t ---------------------------【北门】--------------------     ----------------------------------\n");
    printf("\t\t\t|                             |  |                     |    |                                  |\n");
    printf("\t\t\t|           ------------------   |                     |    |                                  |\n");
    printf("\t\t\t|          |    --------------   |                     |    |                                  |\n");
    printf("\t\t\t|       【基  础】           【水煮】                  |    |     --------                     |\n");
    printf("\t\t\t|       【教学楼】           【鸽子】                  |    【西门】     【东  区】            |\n");
    printf("\t\t\t|         |    |              |  |                     |    |     -------【教学楼】            |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |              |  |                     |    |             |      |             |\n");
    printf("\t\t\t|         |    |--------------   |                     | 子 |             |      ---【东区】   |\n");
    printf("\t\t\t|       【实验楼】               |                     |    |             |      ---【宿舍】   |\n");
    printf("\t\t\t|         |-------------------   |                     |    |             |      |             |\n");
    printf("\t\t\t|                             |  |                     |    |         -----      |             |\n");
    printf("\t\t\t|                             |  |                     |    | 【东升苑】         |             |\n");
    printf("\t\t\t|                             |  |                     |    |         -----      |             |\n");
    printf("\t\t\t|                             |  |                     | 午 |             |      |             |\n");
    printf("\t\t\t|          -------------------    ---------------------|    |-------------|      |             |\n");
    printf("\t\t\t|         |                 【图书馆】             【东门】【天桥】              |             |\n");
    printf("\t\t\t|         |    --------------     ---------------------|    |---------------------             |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     | 大 |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|  【美食】   |               |   --------             |    |                                  |\n");
    printf("\t\t\t|  【广场】   |               |          【操场】      | 道 |                                  |\n");
    printf("\t\t\t|         |   |               |   --------             |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |               |  |                     |    |                                  |\n");
    printf("\t\t\t|         |   |---------------   |                     |    |                                  |\n");
    printf("\t\t\t|      【西区宿舍】         【旭日苑】                 |    |                                  |\n");
    printf("\t\t\t|         |-------------------   |                     |    |                                  |\n");
    printf("\t\t\t|                             |  |                     |    |                                  |\n");
    printf("\t\t\t -------------------------------------------------------     ----------------------------------\n");

    setbuf(stdin, NULL);
    clear_input_buffer();

    return INIT;
}

ma_status_t init_main_menu()
{
    system("clear");
    printf("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t\t\t\t~            欢迎使用西邮导航          ~\n");
    printf("\t\t\t\t\t\t~            1.校园平面图              ~\n");
    printf("\t\t\t\t\t\t~            2.校园地点信息查询        ~\n");
    printf("\t\t\t\t\t\t~            3.问路查询                ~\n");//两个地点的所有简单路径查询，一条最短的简单路径，一条最佳访问路线
    printf("\t\t\t\t\t\t~            4.最佳布网方案            ~\n");
    printf("\t\t\t\t\t\t~            5.新增或撤销地点或者路线  ~\n");
    printf("\t\t\t\t\t\t~            6.退出                    ~\n");
    printf("\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int op = 0;
    scanf("%d", &op);
    switch (op) {
    case 1:
        return ONE;
    case 2:   
        return TOW;
    case 3:   
        return THREE;
    case 4:   
        return FOUR;
    case 5:   
        return FIVE;
    case 6:   
        return EXIT;
    default :                                    
        printf("warning!! line is %d", __LINE__);
    }
    return INIT;
}

void show_main_menu(adj_matrix *G)
{
    ma_status_t status = INIT;
    while (status != EXIT) {
        switch (status) {
        case INIT:
            status = init_main_menu();
            break;
        case ONE:                    
            status = print_map();
            break;                    
        case TOW:
            status = print_mess();
            break;
        case THREE:
            status = ask_directions(G);
            break;
        case FOUR:                   
            status = Prim_MiniSpanTree(G);
            break;                    
        case EXIT:
            break;
        default :
            printf("warning!! line is %d", __LINE__);
        }
    }
}
