#ifndef STATS_PTCL_H_
#define STATS_PTCL_H_

#include "_type.h"
typedef enum _CMD {
	CMD_FUNCTION_BASE = 0x6100,
	CMD_FUNCTION_LOGIN = 0x6101,
} CMD;

#define MY_STX	(0x8eb69af7)
#define SIZE_OF_HEAD	((uint16_t) 8)

#pragma pack(1)

typedef struct _LOGIN {
	uint16_t uid;
} LOGIN;

typedef struct _HEAD {
	uint32_t stx;
	uint16_t pkglen;
	uint16_t cmd;
} HEAD;


#pragma pack()


#endif /* STATS_PTCL_H_ */
