#include <iostream>
#include <ostream>
#include <istream>
//#include "linked_list.h"
using namespace std;

template<typename T> class Node {

private:
	// ******** NODE DATA MEMBERS **********
	T data;	// data part of the node
	Node<T>* next;			// node ptr that points to the next node
	template<typename U> friend class LinkedList;
public:
	Node() : data(0), next(0) {}
	Node(T dataValue) : data(dataValue), next(0) {}
	T & getData()
	{
		return data;
	}
	Node<T>* getNext()
	{
		return next;
	}

};

template<typename T> class LinkedList {

public:
	typedef Node<T>* NodePointer;
private:
	// ******* LINKED LIST DATA MEMBERS **********
	NodePointer first;		// this is the first ptr that points to the first node
	int mySize;				// mySize = size of the list
public:
	LinkedList() : first(0), mySize(0) {} // this initializes the Linked Lists and sets the first = nullptr		

	LinkedList(const LinkedList<T>& origList)
		: first(0), mySize(origList.mySize)
	{

		if (mySize == 0) return;
		LinkedList::NodePointer origPtr, newPtr;	//origPtr is always one step ahead of newPtr
		this->first = new Node<T>(origList.first->data);
		newPtr = this->first;
		origPtr = origList.first->next;
		while (origPtr != nullptr) {
			newPtr->next = new Node(origPtr->data);
			newPtr = newPtr->next;
			origPtr = origPtr->next;
		}
	}

	~LinkedList()		//destructor
	{
		LinkedList<T>::NodePointer prev = this->first, next;
		while (prev != nullptr)
		{
			next = prev->next;
			delete prev;
			prev = next;
		}
		this->first = nullptr;		// setting first to NULL and mySize to 0 after deleting all the nodes
		mySize = 0;
	}
	int getSize()
	{
		return mySize;
	}

	NodePointer getFirst()
	{
		return first;
	}

	bool isEmpty()		// this check to see if first == nullptr
	{
		return first == NULL;
	}


	void erase(int index)	// erase the node at the given index

	{
		if (index < 0 || index > mySize)
		{
			cerr << "******* Invalid index entered ******* " << index << endl;
			return;
		}

		mySize--;
		LinkedList<T>::NodePointer nPtr, predPtr = this->first;
		if (index == 0)
		{
			nPtr = this->first;
			this->first = nPtr->next;
			delete nPtr;
		}
		else
		{
			for (int i = 1; i < index; i++)
			{
				predPtr = predPtr->next;
			}
			nPtr = predPtr->next;
			predPtr->next = nPtr->next;
			delete nPtr;
		}
	}

	int search(T dataVal)	// searches for a specific value
	{
		int loc;
		LinkedList<T>::NodePointer nPtr = this->first;
		for (loc = 0; loc < this->mySize; loc++)
		{
			if (nPtr->data == dataVal)
			{
				return loc;
			}
			else
			{
				nPtr = nPtr->next;
			}
		}
		return -1;
	}


	void insert(T dataVal, int index)

	{
		if (index < 0 || index > mySize)
		{
			cerr << "******* Invalid index entered ******* " << index << endl;
			return;
		}

		mySize++;
		LinkedList<T>::NodePointer newPtr = new Node(dataVal), predPtr = this->first;

		if (index == 0)
		{
			newPtr->next = this->first;
			this->first = newPtr;
		}
		else
		{
			for (int i = 1; i < index; i++)
			{
				predPtr = predPtr->next;
			}
			newPtr->next = predPtr->next;
			predPtr->next = newPtr;
		}
	}											// inserting in any given index

	void push_back(T dataVal)			// inserts element at last position of the list
	{
		NodePointer tempPtr = first, lastPtr;
		lastPtr = tempPtr;
		while (tempPtr != 0)
		{
			lastPtr = tempPtr;
			tempPtr = tempPtr->next;
		}
		if (isEmpty())
		{
			first = new Node<T>(dataVal);
			lastPtr = first;
			mySize++;
			return;
		}
		else
		{
			NodePointer nPtr = new Node<T>(dataVal);
			lastPtr->next = nPtr;
			mySize++;
		}

	}

	const LinkedList<T>& operator = (const LinkedList& rightSide)
	{
		this->mySize = rightSide.mySize;

		if (this->mySize == 0)
		{
			this->~LinkedList();
			return *this;
		}

		if (this != &rightSide)
		{
			this->~LinkedList();	// this deletes the old lists totally
			LinkedList<T>::NodePointer lhsPtr, rhsPtr;
			this->first = new Node<T>(rightSide.first->data);
			lhsPtr = this->first;
			rhsPtr = rightSide.first->next;

			while (rhsPtr != nullptr)
			{
				lhsPtr->next = new Node(rhsPtr->data);
				lhsPtr = lhsPtr->next;
				rhsPtr = rhsPtr->next;
			}
		}
		return *this;
	}		// overriding the = operator

	void display(ostream& out) const
	{

		LinkedList<T>::NodePointer temp = first;
		while (temp != nullptr) {
			out << temp->data << endl;
			temp = temp->next;
		}
	}		// this traverses over the Linked Lists and couts it's elements

	const LinkedList<T> operator + (const LinkedList<T>& rightSide)

	{
		LinkedList<T> l3;
		LinkedList<T>::NodePointer lPtr = this->first,
			rPtr = rightSide.first;
		if (this->mySize == rightSide.mySize)
		{
			for (int i = 0; i < this->mySize; i++)
			{
				l3.insert((lPtr->data + rPtr->data), i);
				lPtr = lPtr->next;
				rPtr = rPtr->next;
			}
		}
		else if (this->mySize > rightSide.mySize)
		{
			for (int i = 0; i < this->mySize; i++)
			{
				if (rPtr)
				{
					l3.insert((lPtr->data + rPtr->data), i);
					rPtr = rPtr->next;
				}
				else
				{
					l3.insert(lPtr->data, i);
				}
				lPtr = lPtr->next;
			}
		}
		else
		{
			for (int i = 0; i < rightSide.mySize; i++)
			{
				if (lPtr)
				{
					l3.insert((lPtr->data + rPtr->data), i);
					lPtr = lPtr->next;
				}
				else
				{
					l3.insert(rPtr->data, i);
				}
				rPtr = rPtr->next;
			}
		}
		return l3;
	}// overloading the + operator

	bool operator > (const LinkedList<T>& rightSide) // overloading the > (greater than operator)
	{
		return this->mySize > rightSide.mySize;
	}

};

template<typename T>
ostream& operator<< (ostream& out, const LinkedList<T>& aList)
{	// passing the out and LL by reference

	aList.display(out);
	return out;
}// this overloads the output operator

template<typename T>
istream& operator >> (istream& in, LinkedList<T>& aList)

{
	int temp, ind;
	cout << "Please enter a number: ";
	cin >> temp;
	cout << "Please enter an index: ";
	cin >> ind;
	aList.insert(temp, ind);
	return in;
}// overloading the input operator

//template<typename ElementType>
//LinkedList<ElementType>::LinkedList() : first(0), mySize(0) {}

//template<typename ElementType>
//LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& origList) : first(0), mySize(origList.mySize)
//{
//
//	if (mySize == 0) return;
//	LinkedList::NodePointer origPtr, newPtr;	//origPtr is always one step ahead of newPtr
//	this->first = new Node(origList.first->data);
//	newPtr = this->first;
//	origPtr = origList.first->next;
//	while (origPtr != nullptr) {
//		newPtr->next = new Node(origPtr->data);
//		newPtr = newPtr->next;
//		origPtr = origPtr->next;
//	}
//}

//template<typename ElementType>
//LinkedList<ElementType>::~LinkedList()
//{
//	LinkedList<ElementType>::NodePointer prev = this->first, next;
//	while (prev != nullptr)
//	{
//		next = prev->next;
//		delete prev;
//		prev = next;
//	}
//	this->first = nullptr;		// setting first to NULL and mySize to 0 after deleting all the nodes
//	mySize = 0;
//}

//template<typename ElementType>
//bool LinkedList<ElementType>::isEmpty() {
//	return first == NULL;
//}

//template<typename ElementType>
//NodePointer LinkedList<ElementType>::begin()
//{
//	return first;
//}

//
//template<typename ElementType>
//void LinkedList<ElementType>::erase(int index)
//{
//	if (index < 0 || index > mySize)
//	{
//		cerr << "******* Invalid index entered ******* " << index << endl;
//		return;
//	}
//
//	mySize--;
//	LinkedList<ElementType>::NodePointer nPtr, predPtr = this->first;
//	if (index == 0)
//	{
//		nPtr = this->first;
//		this->first = nPtr->next;
//		delete nPtr;
//	}
//	else
//	{
//		for (int i = 1; i < index; i++)
//		{
//			predPtr = predPtr->next;
//		}
//		nPtr = predPtr->next;
//		predPtr->next = nPtr->next;
//		delete nPtr;
//	}
//}

//template<typename ElementType>
//void LinkedList<ElementType>::insert(ElementType dataVal, int index)
//{
//	if (index < 0 || index > mySize)
//	{
//		cerr << "******* Invalid index entered ******* " << index << endl;
//		return;
//	}
//
//	mySize++;
//	LinkedList<ElementType>::NodePointer newPtr = new Node(dataVal), predPtr = this->first;
//
//	if (index == 0)
//	{
//		newPtr->next = this->first;
//		this->first = newPtr;
//	}
//	else
//	{
//		for (int i = 1; i < index; i++)
//		{
//			predPtr = predPtr->next;
//		}
//		newPtr->next = predPtr->next;
//		predPtr->next = newPtr;
//	}
//}

//template<typename ElementType>
//void LinkedList<ElementType>::push_back(ElementType dataVal)
//{
//	NodePointer tempPtr = first, lastPtr;
//	lastPtr = tempPtr;
//	while (tempPtr != 0)
//	{
//		lastPtr = tempPtr;
//		tempPtr = tempPtr->next;
//	}
//	if (isEmpty())
//	{
//		first = new Node(dataVal);
//		lastPtr = first;
//		mySize++;
//		return;
//	}
//	else
//	{
//		NodePointer nPtr = new Node(dataVal);
//		lastPtr->next = nPtr;
//		mySize++;
//	}
//
//}

//template<typename ElementType>
//int LinkedList<ElementType>::search(ElementType dataVal)
//{
//	int loc;
//	LinkedList<ElementType>::NodePointer nPtr = this->first;
//	for (loc = 0; loc < this->mySize; loc++)
//	{
//		if (nPtr->data == dataVal)
//		{
//			return loc;
//		}
//		else
//		{
//			nPtr = nPtr->next;
//		}
//	}
//	return -1;
//}

//template<typename ElementType>
//int LinkedList::getSize()
//{
//	return mySize;
//}

//template<typename ElementType>
//const LinkedList<ElementType>& LinkedList<ElementType>::operator = (const LinkedList<ElementType>& rightSide)
//{
//	this->mySize = rightSide.mySize;
//
//	if (this->mySize == 0)
//	{
//		this->~LinkedList();
//		return *this;
//	}
//
//	if (this != &rightSide)
//	{
//		this->~LinkedList();	// this deletes the old lists totally
//		LinkedList<ElementType>::NodePointer lhsPtr, rhsPtr;
//		this->first = new Node(rightSide.first->data);
//		lhsPtr = this->first;
//		rhsPtr = rightSide.first->next;
//
//		while (rhsPtr != nullptr)
//		{
//			lhsPtr->next = new Node(rhsPtr->data);
//			lhsPtr = lhsPtr->next;
//			rhsPtr = rhsPtr->next;
//		}
//	}
//	return *this;
//}

//template<typename ElementType>
//const LinkedList<ElementType> LinkedList<ElementType>::operator + (const LinkedList<ElementType>& rightSide)
//{
//	LinkedList<ElementType> l3;
//	LinkedList<ElementType>::NodePointer lPtr = this->first,
//		rPtr = rightSide.first;
//	if (this->mySize == rightSide.mySize)
//	{
//		for (int i = 0; i < this->mySize; i++)
//		{
//			l3.insert((lPtr->data + rPtr->data), i);
//			lPtr = lPtr->next;
//			rPtr = rPtr->next;
//		}
//	}
//	else if (this->mySize > rightSide.mySize)
//	{
//		for (int i = 0; i < this->mySize; i++)
//		{
//			if (rPtr)
//			{
//				l3.insert((lPtr->data + rPtr->data), i);
//				rPtr = rPtr->next;
//			}
//			else
//			{
//				l3.insert(lPtr->data, i);
//			}
//			lPtr = lPtr->next;
//		}
//	}
//	else
//	{
//		for (int i = 0; i < rightSide.mySize; i++)
//		{
//			if (lPtr)
//			{
//				l3.insert((lPtr->data + rPtr->data), i);
//				lPtr = lPtr->next;
//			}
//			else
//			{
//				l3.insert(rPtr->data, i);
//			}
//			rPtr = rPtr->next;
//		}
//	}
//	return l3;
//}

//template<typename ElementType>
//bool LinkedList<ElementType>::operator > (const LinkedList<ElementType>& rightSide)
//{
//	return this->mySize > rightSide.mySize;
//}

//template<typename ElementType>
//void LinkedList<ElementType>::display(ostream& out) const {
//
//	LinkedList<ElementType>::NodePointer temp = first;
//	while (temp != nullptr) {
//		out << temp->data << endl;
//		temp = temp->next;
//	}
//}

//template<typename ElementType>
//ostream& operator<< (ostream& out, const LinkedList<ElementType>& aList) {	// passing the out and LL by reference
//
//	aList.display(out);
//	return out;
//}

//template<typename ElementType>
//istream& operator >> (istream& in, LinkedList<ElementType>& aList)
//{
//	int temp, ind;
//	cout << "Please enter a number: ";
//	cin >> temp;
//	cout << "Please enter an index: ";
//	cin >> ind;
//	aList.insert(temp, ind);
//	return in;
//}
