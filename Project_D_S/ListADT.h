#pragma once
class UIClass;
#include"Node.h"
template<class T>
class ListADT
{
public:
	virtual void Print(UIClass* PUI)=0;
	virtual bool Remove(const T& value) = 0;
	virtual bool IsEmpty() = 0;
	virtual int GetCount() = 0;
};

