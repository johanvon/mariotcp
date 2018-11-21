/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_util.h
 *	
 *  名称：工具方法
 *  功能：提供一些常用方法
 *  
 *  Created on: 2010-7-1
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_UTIL_H_
#define MARIO_UTIL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mario_type.h"
#include <signal.h>

/*
 * 纳秒sleep
 */
void nsleep(uint32 ns);

/*
 * 秒和微妙sleep
 */
void susleep(uint32 s, uint32 us);

/*
 输入:工作路径
 功能:设置程序后台工作
 */
void run_daemon();

/*
 输入:信号
 功能:设置信号集合
 */
typedef void (*sighandler_t)(int);
void signal_handler(int sig, sighandler_t handler);

#endif /* MARIO_UTIL_H_ */
