#pragma once
#include"QueueADT.h"
template<class T>
class Queue :public QueueADT<T>
{
	Node<T>* front, * rear;
public:
	Queue() {
		front = rear = nullptr;
	}
	bool iSempty()const {
		if (front == nullptr)
			return true;
		return false;
	}
	bool enqueue(const T& val) {
		Node<T>* newnode = new Node<T>();
		newnode->setitem(val);
		if (!rear)
		{
			front = rear = newnode;


		}
		else {
			rear->setnext(newnode);
			rear = rear->getnext();

		}
		newnode->setnext(nullptr);
		return true;
	}
	bool dequeue(T& val) {
		if (iSempty())
			return false;
		if (front == rear) {
			val = rear->getitem();
			delete rear;
			rear = front = nullptr;

			return true;
		}
		Node<T>* delptr = front;
		front = front->getnext();
		val = delptr->getitem();
		delete delptr;

		return true;
	}
	bool peak(T& val)const {
		if (iSempty())
			return false;
		val = front->getitem();
		return true;
	}
	Queue(const Queue<T>& q) {
		Node<T>* ptr = q.front;
		if (!ptr) {
			front = rear = nullptr;
			return;
		}
		Node<T>* newnode = new Node<T>();
		newnode->setitem(ptr->getitem());
		ptr = ptr->getnext();
		front = rear = newnode;
		while (ptr) {
			//enqueue(ptr->getitem());
			Node<T>* newnode = new Node<T>();
			newnode->setitem(ptr->getitem());
			rear->setnext(newnode);
			rear = rear->getnext();
			ptr = ptr->getnext();
		}
	}
	~Queue() {}
};

