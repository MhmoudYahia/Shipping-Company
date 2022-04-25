#include "Event.h"
#include "Time.h"
#include "Company.h"	
Event::Event( Time ET,int ID,Company * C) {
	setEventTime(ET);
	setID(ID);
	Cptr = C;
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
