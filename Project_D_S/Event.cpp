#include "Event.h"
#include "Time.h"

Event::Event( Time ET,int ID) {
	setEventTime(ET);
	setID(ID);
}
void Event::setEventTime(Time evt)
{
	this->event_time.sethour(evt.gethour());
	this->event_time.setDAY(evt.getDAY());
}

void Event::setID(int id)
{
	this->ID = id;
}

Time Event::getEventTime()
{
	return this->event_time;
}

int Event::getID()
{
	return this->ID;
}
