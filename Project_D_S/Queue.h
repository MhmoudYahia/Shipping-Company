#pragma once
//#include"UIClass.h"
#include"QueueADT.h"
//#include "UIClass.h"
class UIClass;
template<class T>
class Queue :public QueueAdt<T>
{
	Node<T>* front, * rear;
public:
	Queue() {
		front = rear = nullptr;
	}
	void Print(UIClass* PUI) {
		
		T Cptr;
		while (dequeue(Cptr) && GetCount() != 1)
		 PUI->PrintID(Cptr) << ',';
		if (dequeue(Cptr));
		 PUI->PrintID(Cptr);
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
	int GetCount() {
		if (iSempty())
			return 0;
		int cnt=0;
		Node<T>* ptr = front;
		while (!ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
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

