#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

CONF *conf = NULL;

sint32 init_conf() {
	uint32 size = sizeof(CONF);
	conf = (CONF *) malloc(size);
	if (!conf) {
		fprintf(stderr, "[error]init_conf, malloc conf failed.\n");
		return -1;
	}
	memset(conf, 0, size);

	FILE * fp;
	char line[1024];
	char name[128];
	char value[128];

	fp = fopen("init.conf", "r");
	if (fp == NULL) {
		fprintf(stderr, "[error] init_conf, fopen failed, errno: %d %m\n", errno);
		return -1;
	}
	memset(line, 0, sizeof(line));
	while (fgets(line, 1024, fp)) {
		if (line[0] == '#' || strcmp(line, "") == 0) {
			continue;
		}
		memset(name, 0, sizeof(name));
		memset(value, 0, sizeof(value));
		sscanf(line, "%s %s", name, value);
		if (strcmp(name, "PORT") == 0) {
			conf->port = atoi(value);
		} else if (strcmp(name, "TIMEOUT") == 0) {
			conf->timeout = atoi(value);
		} else if (strcmp(name, "WORKERNUM") == 0) {
			conf->workernum = atoi(value);
		} else if (strcmp(name, "CONNNUM") == 0) {
			conf->connnum = atoi(value);
		} else if (strcmp(name, "USERNUM") == 0) {
			conf->usernum = atoi(value);
		} else if (strcmp(name, "FILENUM") == 0) {
			conf->filenum = atoi(value);
		}
		memset(line, 0, sizeof(line));
	}
	//check conf
	if (0 == conf->port) {
		fprintf(stderr, "[error] init_conf, port is 0\n");
		fclose(fp);
		return -1;
	}
	fprintf(stdout, "\n>>>>>>>>>>>>>>>init_conf>>>>>>>>>>>>>>>\n");
	fprintf(stdout, "%-24s%u\n", "port", conf->port);
	fprintf(stdout, "%-24s%u\n", "timeout", conf->timeout);
	fprintf(stdout, "%-24s%u\n", "workernum", conf->workernum);
	fprintf(stdout, "%-24s%u\n", "connnum", conf->connnum);
	fprintf(stdout, "%-24s%u\n", "usernum", conf->usernum);
	fprintf(stdout, "%-24s%u\n", "filenum", conf->filenum);
	fprintf(stdout, "\n");
	fflush(stdout);
	fclose(fp);
	return 0;
}
