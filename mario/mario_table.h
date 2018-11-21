/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_table.h
 *	
 *  名称：单一生产者、消费者的表(每一行都是一个队列）
 *  功能：为单一安全访问提供数据结构
 *  
 *  Created on: 2010-6-30
 *      Author: feng jianhua (johan fong)
 *        Mail: 56683216@qq.com
 *
 *  修改记录：
 */

#ifndef MARIO_TABLE_H_
#define MARIO_TABLE_H_

/* these structs are modulars, don't use
 typedef struct _QUEUE {
 uint32 size;
 uint32 producer;
 uint32 consumer;
 void items[0];
 } QUEUE;

 typedef struct _STRITEM_QUEUE {
 uint32 size;
 uint32 producer;
 uint32 consumer;
 char items[QUEUE_SIZE][MAX_STR_LEN];
 } STRITEM_QUEUE;

 typedef struct _TABLE {
 unit16 row_size;
 unit32 col_size;
 QUEUE rows[0];
 } TABLE;
 structs modulars*/

#define PUT_CONSUMER(row)	(row)->consumer = ((row)->consumer + 1) % (row)->size
#define PUT_PRODUCER(row) (row)->producer = ((row)->producer + 1) % (row)->size
#define GET_CONSUMER(row)	\
		((row)->producer != (row)->consumer) \
				?	&(row)->items[(row)->consumer] : NULL;
#define GET_PRODUCER(row) \
		(((row)->producer + 1) % (row)->size != (row)->consumer) \
						?	&(row)->items[(row)->producer] : NULL;

#define PUT_CONSUMER_T(table, rindex)	\
		(table)->rows[(rindex)].consumer = ((table)->rows[(rindex)].consumer + 1) % (table)->rows[(rindex)].size
#define PUT_PRODUCER_T(table, rindex) \
		(table)->rows[(rindex)].producer = ((table)->rows[(rindex)].producer + 1) % (table)->rows[(rindex)].size
#define GET_CONSUMER_T(table, rindex)	\
		((table)->rows[(rindex)].producer != (table)->rows[(rindex)].consumer) \
				?	&(table)->rows[(rindex)].items[(table)->rows[(rindex)].consumer] : NULL;
#define GET_PRODUCER_T(table, rindex) \
		(((table)->rows[(rindex)].producer + 1) % (table)->rows[(rindex)].size != (table)->rows[(rindex)].consumer ) \
						?	&(table)->rows[(rindex)].items[(table)->rows[(rindex)].producer] : NULL;

#define PUT_CONSUMER_STRITEM(row)	(row)->consumer = ((row)->consumer + 1) % (row)->size
#define PUT_PRODUCER_STRITEM(row) (row)->producer = ((row)->producer + 1) % (row)->size
#define GET_CONSUMER_STRITEM(row)	\
		((row)->producer != (row)->consumer) \
				?	(row)->items[(row)->consumer] : NULL;
#define GET_PRODUCER_STRITEM(row) \
		(((row)->producer + 1) % (row)->size != (row)->consumer) \
						?	(row)->items[(row)->producer] : NULL;
#endif /* MARIO_TABLE_H_ */
