#pragma once
template<class T>
class StackADT
{
public:
	StackADT() {}
	virtual bool pop(T& val) = 0;
	virtual bool push(T val) = 0;
	virtual T peak()const = 0;
	virtual bool iSempty()const = 0;
	~StackADT() {}
};

