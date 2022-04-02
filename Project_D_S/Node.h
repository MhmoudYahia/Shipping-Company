#pragma once
template<class T>
class Node
{
	T item;
	Node<T>* next;
public:
	Node() {
		item = 0;
		next = nullptr;
	}
	void setitem(const T& item) {
		this->item = item;
	}
	void setnext(Node<T>* p) {   //really sorry *next*
		next = p;
	}
	Node<T>* getnext() {
		return next;
	}
	T getitem() {
		return item;
	}
	~Node() {}
};

