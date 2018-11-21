#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <inttypes.h>
#include "ptcl.h"

const size_t NUM_THREAD = 9;
const size_t MAX_PKG_LEN = 1500;
uint32_t g_uid = 0;

int create_socket(char* server, int port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		printf("create socket failed, errno %d\n", errno);
		exit(1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(server);
	addr.sin_port = htons(port);
	if (-1 == connect(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr))) {
		printf("connect failed, errno %d\n", errno);
		exit(1);
	}
	return sockfd;
};

int send_cmd(int c, CMD cmd, char *data, size_t data_len)
{
	HEAD *h = (HEAD *) (data);
	h->pkglen = sizeof(HEAD) + data_len;
	h->stx = MY_STX;
	h->cmd = cmd;
	int rs = send(c, data, h->pkglen, 0);
	send(c, "\r\n", 2, 0);
	return rs == h->pkglen;
};

void login(int sock_id)
{
	char buf[MAX_PKG_LEN];
	LOGIN *login = (LOGIN *) (buf + sizeof(HEAD));
	login->uid = 10;
	send_cmd(sock_id, CMD_FUNCTION_LOGIN, buf, sizeof(LOGIN) );
};

int main(int argc, char** argv)
{
	char* server = argv[1];
	int port = atoi(argv[2]);
	int sock_id = create_socket(server, port);
	login(sock_id);
}
