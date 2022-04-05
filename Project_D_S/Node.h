#pragma once
template<class T>
class Node
{
	T item;
	double priority;
	Node<T>* next;
public:
	Node() {
		item = 0;
		next = nullptr;
		priority = 0;
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
	double GetPriority() {
		return priority;
	}
	void SetPriority(double a) {
		priority = a;
	}
	~Node() {}
};

