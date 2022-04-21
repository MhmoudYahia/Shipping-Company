#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"Stack.h"
#include "Node.h"
class CancellationEvent :public Event
{
public:

	void virtual Execute();

};

