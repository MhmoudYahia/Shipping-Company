#pragma once
#include<iostream>
using namespace std;
#include<utility>
class Event
{
private:
	pair<int, int> event_time;
	int ID;
public:
	void setEventTime(pair<int, int> evt);
	void setID(int id);
	pair<int, int> getEventTime();
	int getID();
	void virtual Execute() = 0;
};