/*
 * MarioTCP:  Multi Libvent TCP Server    一个高性能的TCP服务器
 *
 * mario_akg.c
 *	
 *  Created on: 2010-7-3
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#include "mario_akg.h"

const uint16 g_akg_connected_id = 0xfffc;
const uint16 g_akg_timeout_id = 0xfffd;
const uint16 g_akg_closed_id = 0xfffe;
const uint16 g_akg_error_id = 0xffff;

FUNC_PTR AKG_FUNC[MAX_PKG_TYPE];
uint32 g_stx;
