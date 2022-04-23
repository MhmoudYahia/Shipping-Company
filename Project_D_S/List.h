#pragma once

#include "ListADT.h"
template<class T>
class List :
    public ListADT
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
	bool DeleteNode(const T& value) {
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
	}



    ~List(){}
};

