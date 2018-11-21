/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_akg.h
 *	
 *  名称：业务逻辑触发模块
 *  功能：管理、触发业务逻辑，接收处理报告
 *  
 *  Created on: 2010-6-30
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_AKG_H_
#define MARIO_AKG_H_
#include "mario_type.h"
#include "mario_conn.h"

#define MAX_PKG_TYPE (0xffff)
extern const uint16 g_akg_connected_id;
extern const uint16 g_akg_timeout_id;
extern const uint16 g_akg_closed_id;
extern const uint16 g_akg_error_id;

typedef sint32 (*FUNC_PTR)(CONN* c);

extern FUNC_PTR AKG_FUNC[MAX_PKG_TYPE];

#pragma pack(1)
typedef struct _HEAD {
	uint32 stx;
	uint16 pkglen;
	uint16 akg_id;
} HEAD;
#pragma pack()
#define DEFAULT_STX	(0xffffffff)
extern uint32 g_stx;
#define SIZE_OF_HEAD	((uint16) 8)

#endif /* MARIO_AKG_H_ */
