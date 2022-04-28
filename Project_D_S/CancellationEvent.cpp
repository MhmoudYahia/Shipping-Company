#include"CancellationEvent.h"
#include "Company.h" 
#include"Queue.h" 
CancellationEvent::CancellationEvent(Time ET, int ID, Company * C) :Event(ET, ID, C) {

}
void CancellationEvent::Execute()
{
	Cptr->cancellID(ID);
}