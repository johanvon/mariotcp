/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_conn.h
 *	
 *  名称：网络连接管理
 *  功能：管理网络连接的数据结构和算法，供network等模块交互信息使用
 *  
 *  Created on: 2010-6-30
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 *  （1）2010-7-14 conn增加连接相关信息和用户相关信息，后者待拆离
 */

#ifndef MARIO_CONN_H_
#define MARIO_CONN_H_
#include <stdlib.h>
#include <string.h>
#include "mario_global.h"
#include <event.h>

typedef struct _CONN CONN;
typedef struct _CONN_LIST CONN_LIST;
typedef struct _WORKER WORKER;

struct _CONN {
	int fd;
	struct bufferevent *bufev;
	uint32 ind;
	char in_buf[CONN_BUF_LEN];
	uint16 in_buf_len;
	char out_buf[CONN_BUF_LEN];
	uint16 out_buf_len;
	CONN *next;
	WORKER *owner;
	uint32 cip;
	uint16 cport;
	uint16 err_type;
	void *user;
};

struct _CONN_LIST {
	CONN *head;
	CONN *tail;
	CONN list[0];
};

CONN_LIST* init_conn_list(uint32 size);

#define PUT_FREE_CONN(list, item)	\
		list->tail->next = item;	\
		list->tail = item;
#define	GET_FREE_CONN(list, item)	\
		if(list->head != list->tail){	\
			item = list->head;	\
			list->head = list->head->next;	\
		} else {	\
			item = NULL;\
		}

#endif /* MARIO_CONN_H_ */
