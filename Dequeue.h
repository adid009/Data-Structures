/*
* Implementation of a generic double ended queue in C++
*
* Dependent on DLinkedList.h
*/
#pragma once
#ifndef DEQUEUE_H
#define DEQUEUE_H

#include "DLinkedList.h"


/*
Declaration of the Dequeue.
*/
template<class T>
class Dequeue{
	
	private:
	DLinkedList<T> dl;

	public:
	Dequeue();
	Dequeue(const Dequeue<T>& dq);
	Dequeue<T>& operator= (const Dequeue<T>& dq);

	T dequeue();
	void enqueue(const T& el);

	T popFromHead();
	T popFromTail();

	T peekHead()const;
	T peekTail() const;

	void addToTail(const T& el);
	void addToHead(const T& el);

	bool isEmpty() const;
	void display() const;
};

/*
Dequeue constructor
*/
template<class T>
Dequeue<T>::Dequeue(){
}

/*
Dequeue copy constructor
*/
template<class T>
Dequeue<T>::Dequeue(const Dequeue<T>& dq){
	dl = dq.dl;
}


/*
Dequeue Assignment operator.
*/
template<class T>
Dequeue<T>& Dequeue<T>::operator=(const Dequeue<T>& dq){
	dl = dq.dl;
}


/*
Precondition: Queue is not empty. Check this with isEmpty().
Remove the element from the head of the queue and return it's value.
*/
template<class T>
T Dequeue<T>::dequeue(){
	
	T val = dl.removeFromHead();
	return val;
}


/*
Adds the elemet to the tail of the queue.
*/
template<class T>
void Dequeue<T>::enqueue(const T& el){
	dl.addToTail(el);
}


/*
Precondition: Queue is not empty. Check this with isEmpty().
Remove the element from the head of the queue and return its value.
*/
template<class T>
T Dequeue<T>::popFromHead(){
	T val = dl.removeFromHead();
	return val;
}


/*
Precondition: Queue is not empty. Check this with isEmpty().
Remove the element from the tail of the queue and return its value.
*/
template<class T>
T Dequeue<T>::popFromTail(){
        T val = dl.removeFromTail();
        return val;
}


/*
Return the value of the element at the head of the queue.
*/
template<class T>
T Dequeue<T>::peekHead() const{
	return dl.peekHead();
}


/*
Return the value of the element at the tail of the queue.
*/
template<class T>
T Dequeue<T>::peekTail() const{
        return dl.peekTail();
}


/*
Add the new element to the head of the queue.
*/
template<class T>
void Dequeue<T>::addToHead(const T& el){
	dl.addToHead(el);
}


/*
Add new element to the tail of the queue.
*/
template<class T>
void Dequeue<T>::addToTail(const T& el){
	dl.addToTail(el);
}


/*
Return true if the queue is empty.
*/
template<class T>
bool Dequeue<T>::isEmpty() const{
	return dl.isEmpty();
}


/*
Display the value of the elements stored in the queue.
Left end is the head. Right end is the tail.
*/
template<class T>
void Dequeue<T>::display() const{
	dl.display();
}

#endif
