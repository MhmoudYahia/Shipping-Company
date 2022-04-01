#pragma once
template<class T>
class Node
{
	T Item;
	Node<T>* next;
public:
	Node() {
		next = nullptr;
	};
	~Node() {}
};

