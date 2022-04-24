#pragma once
#include<iostream>
#include"Time.h" 
#include "Cargo.h"
using namespace std;
class Event
{
private:
	Time event_time;
	int ID;
public:
	Event(Time, int);
	void setEventTime(Time evt);
	void setID(int id);
	Time getEventTime();
	int getID();
	void virtual Execute() = 0;
};