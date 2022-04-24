#pragma once

#include "ListADT.h"
class UIClass;
template<class T>
class List : public ListADT<T>
{
    Node<T>* Head;
public:
    List() {
        Head = nullptr;
    }

	void Print(UIClass* PUI) {
		Node<T>* temp = Head;
		while (temp->getnext()) {
			PUI->PrintID(temp->getitem()) << ',';
			temp = temp->getnext();
		}
		if (temp)
		   PUI->PrintID(temp->getitem());
	}
	bool isEmpty() {
		return !Head;
	}
	/*int GetCount() {
		if (iSempty())
			return 0;
		int cnt = 0;
		Node<T>* ptr = front;
		while (!ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}*/
	int GetCount() {
		if (isEmpty())
			return 0;
		int cnt = 0;
		Node<T>* ptr = Head;
		while (!ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}
	/*bool Remove(const T& value) {
		Node<T>* temp = Head;
		while (temp) {
			if (temp->getItem() == value)
				break;
			temp = temp->getNext();
		}
		if (!temp)
			return false;
		if (temp == Head)
			this->DeleteFirst();
		else {
			temp->setItem(Head->getItem());
			this->DeleteFirst();
		}
		return true;
	}*/



    ~List(){}
};

