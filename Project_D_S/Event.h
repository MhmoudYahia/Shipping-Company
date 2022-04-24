#pragma once
#include<iostream>
#include"Time.h" 
#include "Cargo.h"
#include "Company.h"
using namespace std;
class Event
{
private:
	Time event_time;
	int ID;
protected:
	Company* Cptr;
public:
	Event(Time, int,Company *);
	void setEventTime(Time evt);
	void setID(int id);
	Time getEventTime();
	int getID();
	void virtual Execute() = 0;
};