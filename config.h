#ifndef __CONF_H__
#define __CONF_H__

#include "mario/mario.h"

#pragma pack(1)
typedef struct _CONF {
	uint16 port;
	uint32 timeout;
	uint32 workernum;
	uint32 connnum;
	uint32 usernum;
	uint32 filenum;
} CONF;
#pragma pack()

sint32 init_conf();

extern CONF* conf;

#endif	//__CONF_H__
