/*
 * mario.c
 *
 *  名称：Mario
 *
 *  Date: 2013-3-1
 *  Author: feng jianhua (johan fong)
 *  Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#include <stdio.h>
#include <stdlib.h>
#include "mario/mario.h"
#include "function.h"
#include "config.h"
#include "protocol.h"
#include "collect.h"
#include <pthread.h>

int main(void) {

	run_daemon();

	if (init_conf() < 0)
		return -1;
	if (init_collect() < 0)
		return -1;

	SERVER *server = init_server(conf->port, conf->workernum, conf->connnum, conf->timeout,
			conf->timeout);
	if (server == NULL)
		return -1;

	regist_akg_func(CMD_FUNCTION_LOGIN, login);
	regist_disconnected_func(logout);

	if (start_log_thread() != 0) {
		fprintf(stderr, "[error] start_log_thread, errno: %d %m\n", errno);
		return -1;
	}

	if (start_collect_thread() != 0) {
		fprintf(stderr, "[error] start_collect_thread, errno: %d %m\n", errno);
		return -1;
	}

	//协议头HEAD的结构请见mario_akg.h,包含一个uint32的token，可用过此函数来注册；如果不注册，则默认为DEFAULT_STX
	regist_stx(0x8eb69af7);

	start_server((void*) server);
	return EXIT_SUCCESS;
}
