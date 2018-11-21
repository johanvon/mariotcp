/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_global.h
 *	
 *  名称：p2p全局定义文件
 *  功能：定义全局变量、宏等数据
 *  
 *  Created on: 2010-6-30
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_GLOBAL_H_
#define MARIO_GLOBAL_H_

#include "mario_type.h"

#define MAX_CONN_ARRAY_SIZE (131072) //1024 * 128
#define	CONN_BUF_LEN	(2048)
#define	MAX_BUF_READ_LEN	(1791) //CONN_BUF_LEN - 257
#define	MAX_PKG_LEN	(1500)
#endif /* MARIO_GLOBAL_H_ */
