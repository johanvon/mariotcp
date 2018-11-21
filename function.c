/*
 * function.c
 *	
 *  Date: 2013-3-1
 *  Author: feng jianhua
 *  Mail: 56683216@qq.com
 *
 *  ĞŞ¸Ä¼ÇÂ¼£º
 */
#include "function.h"
#include "protocol.h"
#include "config.h"
#include "collect.h"

sint32 login(CONN* c) {
	HEAD *hreq = (HEAD*) c->in_buf;
	if (hreq->pkglen != sizeof(HEAD) + sizeof(LOGIN_REQ)) {
		slog_err_t_w(c->owner->qlog, "invalid login pkg.");
		close_err_conn(c);
		return -1;
	}
	++report[c->ind].online;
	HEAD *hrsp = (HEAD *) c->out_buf;
	hrsp->stx = hreq->stx;
	hrsp->akg_id = hreq->akg_id;
	hrsp->pkglen = sizeof(HEAD) + sizeof(LOGIN_RSP);
	LOGIN_RSP *lrsp = (LOGIN_RSP*) (c->out_buf + sizeof(HEAD));
	bufferevent_write(c->bufev, c->out_buf, hrsp->pkglen);
	return 0;
}

sint32 logout(CONN* c) {
	if(report[c->ind].online > 0)
		--report[c->ind].online;
	return 0;
}

