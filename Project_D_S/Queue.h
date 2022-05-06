#pragma once
#include"QueueADT.h"
#include "UIClass.h"
template<class T>
class Queue :public QueueAdt<T>
{
	Node<T>* front, * rear;
	int cnt;
public:
	Queue() {
		front = rear = nullptr;
		cnt = 0;
	}
	void PrintQ(UIClass * PUI) {
		if (!front)
			return;
		Node<T>* temp = front;
		while (temp->getnext()  ) {
		
			PUI->Print(temp->getitem());
			PUI->Printcomma();
			temp = temp->getnext();
		}

		 PUI->Print(temp->getitem());

	}

	bool isEmpty()const {
		if (front == nullptr)
			return true;
		return false;
	}
	bool enqueue(const T& val) {
		Node<T>* newnode = new Node<T>(val);
		if (isEmpty())
		{
			front = newnode;
		}
		else {
			rear->setnext(newnode);
		}
		rear = newnode;
		return true;
	}
	bool dequeue(T& val) {
		if (isEmpty())
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
		if (isEmpty())
			return 0;
		int cnt=0;
		Node<T>* ptr = front;
		while (ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}
	bool peak(T& val)const {
		if (isEmpty())
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

