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
*@brief ��ʱ��
*/
typedef struct
{
	unsigned int id;	 /**< ��ʱ��ID */
	unsigned int period; /**< ��ʱ���� */
	timeval last_timer;	 /**< �ɼ����� */
	timeval cur_timer;	 /**< �¼����� */
} TIMER;

class timer
{
private:
	uint32_t _id;
	uint32_t _period;
	timeval _last_timer; /**< �ɼ����� */
	timeval _cur_timer;	/**< �¼����� */
public:
	timer(uint32_t period);
	~timer();

	bool is_timer_up();//��ʱ���Ƿ�ʱ

};

/**
*@brief ��ȡ��Ŀǰʱ��ĵδ���
*/
void get_tick_count(timeval *timer);

/**
*@brief ��ȡ���ʱ��
*@param ��ʱ��
*/
int get_releative_time_count(TIMER *timer);

/**
*@brief ��ʱ����
*@param usec ��ʱʱ������λms
*/
void delay(unsigned int usec);
