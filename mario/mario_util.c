/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_util.c
 *	
 *  Created on: 2010-7-1
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */
#define _GNU_SOURCE
#include "mario_util.h"
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

void nsleep(uint32 ns) {
	struct timespec req;
	req.tv_sec = 0;
	req.tv_nsec = ns;
	nanosleep(&req, 0);
}

void susleep(uint32 s, uint32 us) {
	struct timeval tv;
	tv.tv_sec = s;
	tv.tv_usec = us;
	select(0, NULL, NULL, NULL, &tv);
}

void signal_handler(int sig, sighandler_t handler) {
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(sig, &action, NULL);
}

void run_daemon() {
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr, "daemon can't fork\n");
		exit(1);
	} else if (pid != 0) {
		exit(0);
	}
	setsid();

	signal_handler(SIGHUP, SIG_IGN);
	signal_handler(SIGTERM, SIG_IGN);
	signal_handler(SIGPIPE, SIG_IGN);
}

