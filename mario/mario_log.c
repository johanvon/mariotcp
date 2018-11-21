/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_log.c
 *	
 *  Created on: 2010-6-30
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#include "mario_log.h"
#include "mario_util.h"
#include <pthread.h>

#define MAX_LOG_QUEUE_COUNT (131072)
#define LOG_QUEUE_SIZE (16384)

static LOG_QUEUE *log_queues[MAX_LOG_QUEUE_COUNT];
static int log_count = 0;
static pthread_mutex_t log_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

sint32 record_log(LOG_QUEUE *log_queue, int fd, const char *fmt, ...) {
	LOG *log = GET_PRODUCER(log_queue);
	if (log == NULL) {
		fprintf(stderr, "get log_queue producer error! %d %d\n", log_queue->consumer, log_queue->producer);
		return -1;
	}
	log->fd = fd;
	va_list args;
	va_start(args, fmt);
	vsprintf(log->buf, fmt, args);
	va_end(args);
	PUT_PRODUCER(log_queue);
	return 0;
}

static void *log_worker_fun(void *arg) {
	while (1) {
		int s = 0;
		for (int i = 0; i < log_count; i++) {
			LOG_QUEUE *queue = log_queues[i];
			LOG *log = GET_CONSUMER(queue);
			if (log == NULL) {
				++s;
				continue;
			}
			write(log->fd, log->buf, strlen(log->buf));
			PUT_CONSUMER(queue);
		}
		if (s == log_count)
			nsleep(10);
	}
	return NULL;
}

sint32 start_log_thread() {
	pthread_t thread_id;
	return pthread_create(&thread_id, NULL, log_worker_fun, NULL);
}

LOG_QUEUE* create_log_queue() {
	pthread_mutex_lock(&log_queue_mutex);
	if (log_count >= MAX_LOG_QUEUE_COUNT) {
		pthread_mutex_unlock(&log_queue_mutex);
		return NULL;
	}

	LOG_QUEUE *log_queue = (LOG_QUEUE*) malloc(sizeof(LOG_QUEUE) + sizeof(LOG) * LOG_QUEUE_SIZE);
	if (log_queue == NULL) {
		fprintf(stderr, "create_log_queue malloc error!\n");
		pthread_mutex_unlock(&log_queue_mutex);
		return NULL;
	}
	memset(log_queue, 0, sizeof(LOG_QUEUE) + sizeof(LOG) * LOG_QUEUE_SIZE);
	log_queue->size = LOG_QUEUE_SIZE;

	log_queues[log_count++] = log_queue;
	pthread_mutex_unlock(&log_queue_mutex);
	return log_queue;
}
