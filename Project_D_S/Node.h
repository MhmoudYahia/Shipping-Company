#pragma once
template<class T>
class Node
{
	T Item;
	Node<T>* Next;
public:
	Node() {
		Next = nullptr;
	};
	~Node() {}
	Node<T>* GetNext() { return Next; }
	void setNext(Node<T>* N) {
		Next = N;
	}
};

