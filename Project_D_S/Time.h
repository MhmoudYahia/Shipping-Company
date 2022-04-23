#pragma once
#include"Time.h"
class Time
{
	int DAY;
	int HOUR;
public:
	Time();
	Time(int d ,int h);
	void sethour(int h);
	void setDAY(int m);
	int gethour();
	int getDAY();
	bool operator <= (Time t);
	Time operator +(int h);
};

