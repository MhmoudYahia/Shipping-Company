#include "Event.h"

void Event::setEventTime(pair<int, int> evt)
{
	this->event_time.first = evt.first;
	this->event_time.second = evt.second;
}

void Event::setID(int id)
{
	this->ID = id;
}

pair<int, int> Event::getEventTime()
{
	return this->event_time;
}

int Event::getID()
{
	return this->ID;
}
