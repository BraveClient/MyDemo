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
*@brief ��ʱ���Ƿ�ʱ
*/
bool timer::is_timer_up()
{
	gettimeofday(&_cur_timer,NULL);

	long int sec = _cur_timer.tv_sec - _last_timer.tv_sec;
	long int usec = _cur_timer.tv_usec - _last_timer.tv_usec;
	double time_diff = sec * 1000 + usec / 1000.0;

	if (time_diff >= _period)
	{
		/*���¼�����*/
		_last_timer.tv_sec = _cur_timer.tv_sec;
		_last_timer.tv_usec = _cur_timer.tv_usec;
		return 1;
	}
	return 0;
}

/**
 * @brief ��ȡ���ʱ��
 * 
 */
int get_releative_time_count(TIMER *timer)
{
	gettimeofday(&(timer->cur_timer),NULL);

	long int sec = timer->cur_timer.tv_sec - timer->last_timer.tv_sec;
	long int usec = timer->cur_timer.tv_usec - timer->last_timer.tv_usec;

	int time_diff = sec * 1000 + usec / 1000;

	return time_diff; //��λms
}

/**
 * @brief ��ʱ����
 * 
 */

void delay(unsigned int usec)
{
	usleep(usec);
}

/**
*  @brief ��ȡ�δ�
*/
void get_tick_count(timeval *timer)
{
	gettimeofday(timer, NULL);
}
