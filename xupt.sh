#!/bin/bash
gcc -Wall -Werror -g -std=gnu11 sql.c sql.h xupt_navigation_menu.c xupt_navigation_menu.h xupt_navigation_main.c stack_list.c stack_list.h -lmysqlclient
