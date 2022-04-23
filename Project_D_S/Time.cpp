#include "Time.h"

Time::Time()
{
	this->HOUR = 0;
	this->MINUTE = 0;
}

void Time::sethour(int h)
{
	this->HOUR = (h>0) ? h : 0 ;
}

void Time::setminute(int m)
{
	this->MINUTE = (m > 0) ? m : 0;
}

int Time::gethour()
{
	return this->HOUR;
}

int Time::getminute()
{
	return this->MINUTE;
}

bool Time::operator<=(Time t)
{
	if (this->gethour() < t.gethour())
		return true;
	else if (this->gethour() == t.gethour() && this->getminute() <= t.getminute())
		return true;
	else
		return false;


}
