#pragma once
#include"Node.h"
template<class T>
class Queue
{
	Node<T>* Front,Rear;
public:
	Queue() {
		Front = Rear = nullptr;
	}
	bool Enqueue(T Item) {}
	bool Dequeue(T &Item){}
	~Queue() {}
};

