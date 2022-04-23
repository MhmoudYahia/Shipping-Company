#pragma once
#include"UIClass.h"
#include"Node.h"
template<class T>
class ListADT
{
public:
	void Print(UIClass* PUI)=0;
	bool DeleteNode(const T& value) = 0;
};

