#pragma once
#include"Node.h"
template<class T>
class Queue
{
	Node<T>* front,rear;
public:
	Queue() {
		front = rear = nullptr;
	}
	bool Insert(T item) {}
	~Queue() {}
};

