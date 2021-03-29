#include "timer.h"

timer::timer(uint32_t period)
{
	_id = 0;
	gettimeofday(&_last_timer,NULL);
	gettimeofday(&_cur_timer,NULL);
	_period= period;
}

timer::~timer()
{
}

/**
*@brief 定时器是否到时
*/
bool timer::is_timer_up()
{
	gettimeofday(&_cur_timer,NULL);

	long int sec = _cur_timer.tv_sec - _last_timer.tv_sec;
	long int usec = _cur_timer.tv_usec - _last_timer.tv_usec;
	double time_diff = sec * 1000 + usec / 1000.0;

	if (time_diff >= _period)
	{
		/*更新计数器*/
		_last_timer.tv_sec = _cur_timer.tv_sec;
		_last_timer.tv_usec = _cur_timer.tv_usec;
		return 1;
	}
	return 0;
}

/**
 * @brief 获取相对时间
 * 
 */
int get_releative_time_count(TIMER *timer)
{
	gettimeofday(&(timer->cur_timer),NULL);

	long int sec = timer->cur_timer.tv_sec - timer->last_timer.tv_sec;
	long int usec = timer->cur_timer.tv_usec - timer->last_timer.tv_usec;

	int time_diff = sec * 1000 + usec / 1000;

	return time_diff; //单位ms
}

/**
 * @brief 延时函数
 * 
 */

void delay(unsigned int usec)
{
	usleep(usec);
}

/**
*  @brief 获取滴答
*/
void get_tick_count(timeval *timer)
{
	gettimeofday(timer, NULL);
}
