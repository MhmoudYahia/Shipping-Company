#include "PromotionEvent.h"
#include "Company.h"
void PromotionEvent::setExtraMoney(int exm)
{
	this->ExtraMoney = exm;
}

int PromotionEvent::getExtraMoney()
{
	return this->ExtraMoney;
}
//void PromotionEvent::Execute() {
//	Cptr->UpdatetoVIP(getID());
//}
VIPCargo* PromotionEvent::getVIPCargo() {
	return VCargoptr;
}

void PromotionEvent::Execute()
{

	Cargo *Nptr= Cptr->GetNormalCargo(ID);
	if (Nptr) {
		Nptr->SetCost(Nptr->getCost() + getExtraMoney());
		Cptr->AddCargotoVIPWaiting(Nptr);
		Cptr->CancellationID(ID);
	}
	else {
		Cargo* c = Cptr->PromotionExceeded(ID);
		if (c) {
			c->SetCost(c->getCost() + getExtraMoney());
			Cptr->AddToVIPexceeded(c);
		}
	}
}

PromotionEvent::PromotionEvent(Time ET, int ID, int exm , Company * C) :Event(ET, ID,C) {
	setExtraMoney(exm);
}
