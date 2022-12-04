#include <stdio.h>
#include <ostream>
#include <istream>
#include <iostream>
using namespace std;
typedef int T;

#pragma once
class LinkedList {

private:
	class Node {
	public:
		// ******** NODE DATA MEMBERS **********
		T data;	// data part of the node
		Node* next;			// node ptr that points to the next node
		Node() : data(0), next(0) {}
		Node(T dataValue) : data(dataValue), next(0) {}
	};
	// ******* LINKED LIST DATA MEMBERS **********
	typedef Node* NodePointer;
	NodePointer first;		// this is the first ptr that points to the first node
	int mySize;				// mySize = size of the list
public:
	LinkedList();		// this initializes the Linked Lists and sets the first = nullptr

	LinkedList(const LinkedList& origList);	// copy constructor

	~LinkedList();		//destructor

	bool isEmpty();		// this check to see if first == nullptr

	void erase(int index); // erase the node at the given index

	int search(T dataVal);	// searches for a specific value

	//void insertFirst(ElementType newItem);		// this inserts an item into index 0 of the list

	void insert(T dataVal, int index); // inserting in any given index

	void push_back(T dataVal); // inserts element at last position of the list

	const LinkedList& operator = (const LinkedList& rightSide); // overriding the = operator

	void display(ostream& out) const;		// this traverses over the Linked Lists and couts it's elements

	const LinkedList operator + (const LinkedList& rightSide); // overloading the + operator

	bool operator > (const LinkedList& rightSide); // overloading the > (greater than operator)

};

ostream& operator<< (ostream& out, const LinkedList& aList);	// this overloads the output operator

istream& operator >> (istream& in, LinkedList& aList); // overloading the input operator

