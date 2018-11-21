/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_network.h
 *	
 *  名称：网络处理模块（公共模块）
 *	功能：管理连接，网络读写，任务分发
 *  
 *  Created on: 2010-6-30
 *      Author: fengjianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_NETWORK_H_
#define MARIO_NETWORK_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "mario_type.h"
#include "mario_conn.h"
#include "mario_log.h"

#define CONN_READ_TIMEOUT (300)
#define CONN_WRITE_TIMEOUT (300)

typedef struct _SERVER SERVER;

struct _WORKER {
	pthread_t thread_id;
	uint16 ind;
	int sfd;
	struct event_base *base;
	CONN_LIST *conns;
	struct event notify_event;
	int notified_rfd;
	int notifed_wfd;
	LOG_QUEUE *qlog;
	SERVER *server;
};

typedef struct _WORKER_ARRAY {
	uint16 size;
	SERVER *server;
	WORKER array[0];
} WORKER_ARRAY;

struct _SERVER {
	int server_fd;
	int port;
	struct event_base *base;
	struct event listen_event;
	WORKER_ARRAY *workers;
	LOG_QUEUE *qlog;
	int ret;
	uint16 start_worker_num;
	uint64 conn_count;
	pthread_mutex_t start_lock;//start_worker_num同步;cond wait队列同步
	pthread_cond_t start_cond;
};

SERVER* init_server(int port, uint16 workernum, uint32 connnum, int read_timeout, int write_timeout);
WORKER_ARRAY* init_workers(SERVER *server, uint16 workernum, uint32 connnum, int read_timeout, int write_timeout);
void* start_server(void* arg);
int start_workers(WORKER_ARRAY* workers);

#endif /* MARIO_NETWORK_H_ */
