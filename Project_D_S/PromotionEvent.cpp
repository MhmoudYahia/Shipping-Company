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

	NormalCargo *Nptr= Cptr->GetNormalCargo(ID);
	if (Nptr) {
		VIPCargo* temp = new VIPCargo;
		temp->SetCost(Nptr->getCost() + this->getExtraMoney());
		temp->SetDdes(Nptr->getDdes());
		temp->SetID(Nptr->GetID());
		temp->SetLT(Nptr->getLT());
		temp->setPT(Nptr->getPT().getDAY(), Nptr->getPT().gethour());
		Cptr->AddCargotoWaiting(temp);
	}
}

PromotionEvent::PromotionEvent(Time ET, int ID, int exm , Company * C) :Event(ET, ID,C) {
	setExtraMoney(exm);
}
