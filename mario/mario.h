/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario.h
 *	
 *  名称：mario接口模块
 *  功能：mario高效网络处理功能的接口
 *  
 *  Created on: 2010-7-4
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_H_
#define MARIO_H_
#include "mario_global.h"
#include "mario_type.h"
#include "mario_log.h"
#include "mario_conn.h"
#include "mario_network.h"
#include "mario_akg.h"
#include "mario_util.h"

extern SERVER* init_server(int port, uint16 workernum, uint32 connnum, int read_timeout, int write_timeout);

extern void* start_server(void* arg);

extern void close_err_conn(CONN *c);

extern void close_conn(CONN *c, uint16 akg_id);

/**
 *	注册业务处理函数
 */
void regist_akg_func(uint16 id, FUNC_PTR func);

/**
 *	注册接受客户端连接时响应函数
 */
void regist_connected_func(FUNC_PTR func);

/**
 *	注册客户端断开处理函数
 */
void regist_disconnected_func(FUNC_PTR func);

/**
 *	注册网络超时处理函数
 */
void regist_timeout_func(FUNC_PTR func);

/**
 *	注册客户端连接关闭处理函数
 */
void regist_closed_func(FUNC_PTR func);

/**
 *	注册网络错误处理函数
 */
void regist_error_func(FUNC_PTR func);

/**
 * 注册用户自定义头部的同步密码
 */
void regist_stx(uint32 stx);

#endif /* MARIO_H_ */
