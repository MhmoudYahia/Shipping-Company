#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
class PromotionEvent :public Event
{
	int ExtraMoney;
public:
	void setExtraMoney(int exm);
	int getExtraMoney();
	VIPCargo* Execute(NormalCargo* & ptr);
};

