#pragma once
#include"Node.h"
template<class T>
class PriorityQueueAdt
{
public:
	PriorityQueueAdt() {}
	virtual bool enqueue(const T& val,int p) = 0;
	virtual bool dequeue(T& val) = 0;
	virtual bool iSempty()const = 0;
	virtual bool peak(T& val)const = 0;
	~PriorityQueueAdt() {}

};



