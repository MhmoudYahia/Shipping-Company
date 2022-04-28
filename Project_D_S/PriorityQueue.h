#pragma once
#include"Node.h"

#include"PriorityQueueAdt.h"
template<class T>
class PriorityQueue:public PriorityQueueAdt<T>
{
	Node<T>* front, * rear;
public:
	//int cnt=0;
	/*void PrintPriQ(UIClass* PUI) {
		int Cptr;
		while (dequeue(Cptr) && GetCount() != 1) {
			cout<<;
			cout << ',';
		}
		if (dequeue(Cptr));
		PUI->Print(Cptr);
	}*/
	PriorityQueue() {
		front = rear = nullptr;
		//cnt = 0;
	}
	int GetCount() {
		if (iSempty())
			return 0;
		int cnt = 0;
		Node<T>* ptr = front;
		while (ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}
	//int GetCount() {
	//	return cnt;
	//}

	bool enqueue(const T& item,double par) {
		Node<T>* temp = front;
		Node<T>* newnode = new Node<T>();
		if (!newnode)
			return false;
		newnode->setitem(item);
		newnode->SetPriority(par);
		if (!front) {
			front = rear = newnode;
			//cnt++;
			return true;
		}
		if (front->GetPriority() < par) {
			newnode->setnext(front);
			front = newnode;
			//cnt++;
			return true;
		}
		//while (temp->getnext()&&temp->getnext()->GetPriority()>par) {

		//	temp = temp->getnext();

		//}
		//// 
		while (temp->getnext() ) {
			if (temp->getnext()->GetPriority() < par) {
				//temp is now in the position
					newnode->setnext(temp->getnext());
					temp->setnext(newnode);
					//cnt++;
					return true;
			}
			temp = temp->getnext();
			}
		rear->setnext(newnode);
		rear = newnode;
		//cnt++;
		return true;
	}
	bool iSempty()const {
		return !front;
	}
	bool dequeue(T& val) {
		if (iSempty())
			return false;
		Node<T>* tobeDeleted = front; 
		val = front->getitem();
		front = front->getnext();
		if (tobeDeleted == rear) {
			rear = nullptr;
		}
		delete tobeDeleted;
	//	cnt--;
		return true;
	}
	bool peak(T& val)const {
		if (iSempty())
			return false;
		val = front->getitem();
		return true;
	}
	PriorityQueue(const PriorityQueue<T>& q) {
		Node<T>* ptr = q.front;
		if (!ptr) {
			front = rear = nullptr;
			return;
		}
		Node<T>* newnode = new Node<T>();
		newnode->setitem(ptr->getitem());
		newnode->SetPriority(ptr->GetPriority());
		ptr = ptr->getnext();
		front = rear = newnode;
		while (ptr) {
			//enqueue(ptr->getitem());
			Node<T>* newnode = new Node<T>();
			newnode->setitem(ptr->getitem());
			newnode->SetPriority(ptr->GetPriority());
			rear->setnext(newnode);
			rear = rear->getnext();
			ptr = ptr->getnext();
		}
	}
	~PriorityQueue() {}
};

