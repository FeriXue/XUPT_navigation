#include "sql.h"
#include "xupt_navigation_menu.h"

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#define SENTENCELEN 500

void sql_init(void)
{
    if (mysql_init(&sql) == NULL) {
        perror("mysql_init");
    }
    if (mysql_library_init(0, NULL, NULL) != 0) {
        perror("mysql_library_init");
    }
    if (mysql_real_connect(&sql, "127.0.0.1", "root", "1017129dameinv", "xupt_navigation", 0, NULL, 0) == NULL) {
        perror("mysql_real_connect");
    }
    if (mysql_set_character_set(&sql, "utf8") < 0) {
        perror("mysql_set_character_set");
    }
    printf("成功连接数据库\n");
}

void find(char *target, char *now)
{
    char buffer[SENTENCELEN];
    sprintf(buffer, "select *from place_message where name1 = \"%s\" and name2 = \"%s\"", target, now);
    //sprintf(buffer, "insert into xupt_navigation values(\"%s\", \"%s\", \"%s\", \"%s\")", target, now, target, now);
    mysql_query(&sql, buffer);
    MYSQL_RES *result = mysql_store_result(&sql);
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("\t\t\t\t\t\t<<%s>>距离您当前位置<<%s>>距离为<%sm>.\n\t\t\t\t\t\t目标地点简介：%s\n", row[0], row[1], row[2], row[3]);
    clear_input_buffer();
}
