#include "Time.h"

Time::Time()
{
	this->HOUR = 0;
	this->DAY = 0;
}

void Time::sethour(int h)
{
	this->HOUR = (h>0) ? h%24 : 0 ;
	this->setDAY(this->getDAY() + h / 24);
}

void Time::setDAY(int m)
{
	this->DAY = (m > 0) ? m : 0;
}

int Time::gethour()
{
	return this->HOUR;
}

int Time::getDAY()
{
	return this->DAY;
}

bool Time::operator<=(Time t)
{
	if (this->getDAY() < t.getDAY())
		return true;
	else if (this->getDAY() == t.getDAY() && this->gethour() <= t.gethour())
		return true;
	else
		return false;


}

Time Time::operator+(int h)
{
	this->sethour(this->gethour() + h);
	return *this;
}
