#pragma once
#include<iostream>
#include"Time.h" 
using namespace std;
class Event
{
private:
	Time event_time;
	int ID;
public:
	void setEventTime(Time evt);
	void setID(int id);
	Time getEventTime();
	int getID();
	void virtual Execute() = 0;
};