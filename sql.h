#ifndef SQL_H
#define SQL_H

#include <mysql/mysql.h>

MYSQL sql;

void sql_init(void);
void find(char *target, char *now);

#endif
