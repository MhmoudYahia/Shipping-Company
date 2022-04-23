#pragma once
class Time
{
	int HOUR;
	int MINUTE;
public:
	Time();
	void sethour(int h);
	void setminute(int m);
	int gethour();
	int getminute();
	bool operator <= (Time t);
};

