#pragma once
#include<iostream>
#include"Time.h" 
#include "Cargo.h"
class Company;
using namespace std;
class Event
{
private:
	Time event_time;
	
protected:
	Company * Cptr;
	int ID;
public:
	Event(Time, int,Company *);
	void setEventTime(Time evt);
	void setID(int id);
	Time getEventTime();
	int getID();
	void virtual Execute() = 0;
};