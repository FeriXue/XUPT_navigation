#include "sql.h"

#include <mysql/mysql.h>
#include <stdio.h>

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
