/*
* Implementation of a Generic stack in C++
*
* Dependent on "DLinkedList.h"
*/

#pragma once
#ifndef STACK_H
#define STACK_H
#include "DLinkedList.h"

template<class T>
class Stack{
	
	private:
	DLinkedList<T> dl;

	public:
	Stack();
	Stack(const Stack<T>& s);

	Stack<T>& operator=(const Stack<T>& s);
	T pop();
	T top()const;

	void push(const T& el);
	void display()const;
	bool isEmpty() const;
};

/*
Constructor
*/
template<class T>
Stack<T>::Stack(){
}

/*
Copy Constructor
*/
template<class T>
Stack<T>::Stack(const Stack<T>& s){
	dl = s.dl;
}

/*
Assignment operator
Copies the stack, element by element
*/
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s){
	dl = s.dl;
}


/*
Precondition - The stack should not be empty. Call isEmpty() before making the call.
Removes the element that was is the top of the stack and returns its value.
*/
template<class T>
T Stack<T>::pop(){
	T val = dl.removeFromHead();
	return val;
}


/*
Precondition - The stack should not be empty. Call isEmpty() before making the call.
Returns the element at the top of the stack. Does not remove it.
*/

template<class T>
T Stack<T>::top() const{
	T val = dl.peekHead();
	return val;
}


/*
Pushes the element at the top of the stack.
*/
template <class T>
void Stack<T>::push(const T& el){
	dl.addToHead(el);
}


/*
Displays the contents of the stack.
Left end is the top of the stack. Right end is the bottom.
*/
template<class T>
void Stack<T>::display() const{
	dl.display();
}


/*
Checks if the stack is empty.
Returns true if empty.
*/
template<class T>
bool Stack<T>::isEmpty() const{
	return dl.isEmpty();
}

#endif
