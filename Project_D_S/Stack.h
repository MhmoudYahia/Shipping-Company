#pragma once
#include"Node.h"
#include"StackADT.h"
template<class T>
class Stack :public StackADT<T>
{

	Node<T>* top;
public:
	Stack() {
		top = nullptr;
	}
	bool iSempty()const {
		if (!top)
			return true;
		return false;
	}
	bool push(T val) {
		Node<T>* newnode = new Node<T>();
		newnode->setitem(val);

		/*if (iSempty()) {
			top = newnode;
			return true;
		}*/
		newnode->setnaxt(top);
		top = newnode;
		return true;

	}
	T peak()const {
		if (iSempty())
			return 0;
		return top->getitem();
	}
	bool pop(T& val) {
		if (iSempty())
			return false;
		Node<T>* del = top;
		top = top->getnext();
		val = del->getitem();
		del->setnaxt(nullptr);
		delete del;
		return true;
	}
	Stack(const Stack<T>& s) {
		Node<T>* ptr = s.top, * nptr;
		if (!ptr)
		{
			top = nullptr;
			return;
		}
		Node<T>* newnode = new Node<T>();
		newnode->setitem(ptr->getitem());
		top = newnode;
		nptr = newnode;
		ptr = ptr->getnext();
		while (ptr) {
			Node<T>* newnode = new Node<T>();
			newnode->setitem(ptr->getitem());
			nptr->setnaxt(newnode);
			nptr = nptr->getnext();
			/*push(ptr->getitem());*/
			ptr = ptr->getnext();
		}
		nptr->setnaxt(nullptr);
	}
	~Stack() {}
};

