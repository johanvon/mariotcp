/*
 * collcet.c
 *	
 *  Date: 2013-3-1
 *  Author: feng jianhua (johan fong)
 *  Mail: 56683216@qq.com
 *
 *  ÐÞ¸Ä¼ÇÂ¼£º
 */

#include "mario/mario.h"
#include "collect.h"

#define COLLECT_INTERVAL_SECOND		    (60)

REPORT *report = NULL;

static LOG_QUEUE *log = NULL;

sint32 init_collect() {
	log = create_log_queue();
	if (log == NULL) {
		fprintf(stderr, "init_report log error! errno: %d %m\n", errno);
		return -1;
	}
	report = (REPORT *) malloc(sizeof(REPORT) * conf->workernum);
	if (report == NULL) {
		fprintf(stderr, "init_report error!\n");
		return -1;
	}
	memset(report, 0, sizeof(REPORT) * conf->workernum);
	return 0;
}

void online_collect(const char *datetime) {
	uint64 sum = 0;
	for (int i = 0; i < conf->workernum; i++) {
		sum += report[i].online;
	}
	slog_info_t(log, "online number: %lu", sum);
}

void *collect_worker_fun(void *arg) {
	static int64_t timecount = 0;
	time_t timesec;
	static struct tm *timestr;
	static char datetime[50];
	while (1) {
		susleep(1, 0);
		if ((++timecount) % COLLECT_INTERVAL_SECOND == 0) {
			timesec = time(NULL);
			timestr = localtime(&timesec);
			memset(datetime, 0, sizeof(datetime));
			strftime(datetime, 50, "%Y-%m-%d %H:%M:%S", timestr);
			online_collect(datetime);
		}
	}
	return NULL;
}

sint32 start_collect_thread() {
	pthread_t thread_id;
	return pthread_create(&thread_id, NULL, collect_worker_fun, NULL);
}
