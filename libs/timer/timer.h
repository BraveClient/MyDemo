/**
 * @file timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include "../../include/common.h"
#include <sys/time.h>

/**
*@brief 定时器
*/
typedef struct
{
	unsigned int id;	 /**< 定时器ID */
	unsigned int period; /**< 定时周期 */
	timeval last_timer;	 /**< 旧计数器 */
	timeval cur_timer;	 /**< 新计数器 */
} TIMER;

class timer
{
private:
	uint32_t _id;
	uint32_t _period;
	timeval _last_timer; /**< 旧计数器 */
	timeval _cur_timer;	/**< 新计数器 */
public:
	timer(uint32_t period);
	~timer();

	bool is_timer_up();//定时器是否到时

};

/**
*@brief 获取到目前时间的滴答数
*/
void get_tick_count(timeval *timer);

/**
*@brief 获取相对时间
*@param 计时器
*/
int get_releative_time_count(TIMER *timer);

/**
*@brief 延时函数
*@param usec 延时时长，单位ms
*/
void delay(unsigned int usec);
