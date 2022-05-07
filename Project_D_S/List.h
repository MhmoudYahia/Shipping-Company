#pragma once
#include "UIClass.h"
#include"Cargo.h"
#include"Node.h"
//#include "ListADT.h"
class UIClass;
//class Cargo;
template<class T>
class List 
{
    Node<T>* Head;
public:
    List() {
        Head = nullptr;
    }
	void InsertEnd(const T& data) {
		Node<T>* newN = new Node<T>();
		newN->setitem(data);
		newN->setnext(nullptr);
		Node<T>* temp = Head;
		if (temp) {
			while (temp->getnext())
				temp = temp->getnext();
			temp->setnext(newN);
		}
		else Head = newN;
	}
	bool DeleteFirst(T&item) {
		if (!Head)
			return false;
		Node<T>* delptr = Head;
		Head = Head->getnext();
		item = delptr->getitem();
		delptr->setnext(nullptr);
		delete delptr;
		delptr = nullptr;
		return true;
	}
	void Print(UIClass* PUI) {
		Node<T>* temp = Head;
		while (temp->getnext()) {
			PUI->Print(temp->getitem());
			PUI->Printcomma();
			temp = temp->getnext();
		}
		if (temp)
		   PUI->Print(temp->getitem());
	}
	bool isEmpty() {
		return !Head;
	}
	
	int GetCount() {
		if (isEmpty())
			return 0;
		int cnt = 0;
		Node<T>* ptr = Head;
		while (ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}
	bool Remove(int const &id) {
	Node<T>* ptr = Head;
	Node<T>* delptr;

	if (!ptr)
		return false;
	if (id == ptr->getitem()) {
		delptr = Head;
		Head = Head->getnext();
		delptr->setnext(nullptr);
		delete delptr;
		return true;
	}
	Node<T>* prev = Head;
	ptr = ptr->getnext();
	while (ptr) {
		if (ptr->getitem() == id) {
			delptr = ptr;
			ptr = ptr->getnext();
			prev->setnext(ptr->getnext());
			delptr->setnext(nullptr);
			delete delptr;
			return true;
		}
		else {
			prev = ptr;
			ptr = ptr->getnext();
		}
	}
	return false;
    }
    ~List(){
		Node<T>* temp = Head;
		while (Head) {
			temp = Head->getnext();
			delete Head;
			Head = temp;
		}
	}
};
template<>
class List<Cargo*>
{
	Node<Cargo*>* Head;
public:
	List() {
		Head = nullptr;
	}
	void InsertEnd( Cargo* data) {
		Node<Cargo*>* newN = new Node<Cargo*>();
		newN->setitem(data);
		newN->setnext(nullptr);
		Node<Cargo*>* temp = Head;
		if (temp) {
			while (temp->getnext())
				temp = temp->getnext();
			temp->setnext(newN);
		}
		else Head = newN;
	}
	void PrintL(UIClass* PUI) {
		Node<Cargo*>* temp = Head;
		while (temp->getnext()) {
			PUI->Print(temp->getitem());
			PUI->Printcomma();
			temp = temp->getnext();
		}
		if (temp) {
			PUI->Print(temp->getitem());
		}
	}
	
	int GetCount() {
		if (isEmpty())
			return 0;
		int cnt = 0;
		Node<Cargo*>* ptr = Head;
		while (ptr) {
			cnt++;
			ptr = ptr->getnext();
		}
		return cnt;
	}
	bool isEmpty() {
		return !Head;
	}
	bool Remove(int id) {
		Node<Cargo*>* ptr = Head;
		Node<Cargo*>* delptr;

		if (!ptr)
			return false;
		if (id == ptr->getitem()->GetID()) {
				delptr = Head;
				Head = Head->getnext();
				delptr->setnext(nullptr);
				delete delptr;
				return true;
		}
		Node<Cargo*>* prev = Head;
		ptr = ptr->getnext();
		while (ptr) {
			if (ptr->getitem()->GetID() == id) {
				delptr = ptr;
				ptr = ptr->getnext();
				prev->setnext(ptr);
				delptr->setnext(nullptr);
				delete delptr;
				return true;
			}
			else {
				prev = ptr;
				ptr = ptr->getnext();
			}
		}
		return false;
	}
	Node<Cargo*>* PointerToNormalCRGO(int id) {
		Node<Cargo*>* temp = Head;
		while (temp) {
			if (id == temp->getitem()->GetID())
				return temp;
			temp=temp->getnext();
		}
		return nullptr;
	 }
	bool DeleteFirst(Cargo*& item) {
		if (!Head)
			return false;
		Node<Cargo*>* delptr = Head;
		Head = Head->getnext();
		item = delptr->getitem();
		delptr->setnext(nullptr);
		delete delptr;
		delptr = nullptr;
		return true;
	}
	Node<Cargo*>* getHead() {
		return Head;
	}
	void incrementWH() {
		Node<Cargo*>* temp = Head;
		while (temp) {
			temp->getitem()->IncrementWaitingHours();
			temp = temp->getnext();
		}
	}
	~List() {
			Node<Cargo*>* temp = Head;
			while (Head) {
				temp = Head->getnext();
				delete Head;
				Head = temp;
			}
		
	}
};
