/*
Implementation of a generic Singly Linked List in C++
*/
#pragma once
#ifndef SLINKED_LIST_H
#define SLINKED_LIST_H

#include <iostream>

template< class T>
class SLinkedList;


/*
Declaration of the Node
*/
template <class T>
class Node{

	private:
	T elem;
	Node<T> * next;
	public:
	Node():next(0){
	}
	Node( const T& x, Node<T> * n=0):elem(x),next(n){
	}
	friend class SLinkedList<T>;
};

/*
Declaration of the Singly Linked List
*/
template<class T>
class SLinkedList{

	private:
	Node<T> * head;
	Node<T> * tail;
	void reverseList(Node<T> *thead, Node<T> * ttail);

	public:
	class Iterator{
		
		private:
		Node<T> * v;
		Iterator(Node<T> * p){
			v = p;
		}

		public:
		T& operator*();
		bool operator==(const Iterator& p)const;
		bool operator!=(const Iterator& p)const;
		Iterator& operator++();
		
		friend class SLinkedList<T>;
	};

	SLinkedList();
	~SLinkedList();
	SLinkedList(const SLinkedList<T>& s);

	SLinkedList<T>& operator=(const SLinkedList<T>& s);

	Iterator begin()const;
	Iterator end()const;

	void addToHead(const T& t);
	void addToTail(const T& t);
	T removeFromHead();
	T removeFromTail();
	void remove(const T& t);

	T getMin()const;
	T getMax()const;
	
	bool isEmpty() const;
	bool contains(const T&) const;

	void reverse();
	void display() const;
};

/*
Singly Linked List constructor
*/
template<class T>
SLinkedList<T>::SLinkedList():head(0), tail(0){
}

/*
Singly Linked List copy constructor
*/
template<class T>
SLinkedList<T>::SLinkedList(const SLinkedList<T>& s):head(0),tail(0){
	
	for (SLinkedList<T>::Iterator i = s.begin(); i != s.end(); ++i){
		addToTail(*i);

	}
	std::cout << std::endl;
}

/*
Singly linked list assignment operator
*/
template<class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T>& s){
	
	if (this != &s){
		while(!isEmpty()){
			removeFromHead();
		}

		for (SLinkedList<T>::Iterator i = s.begin(); i != s.end(); ++i){
			addToTail(*i);
		}
	}
	return *this;
}

/*
Returns an iterator pointing to the head of the list
*/
template<class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::begin() const{
	return Iterator(head);
}


/*
Returns an iterator pointing to the node netx to the tail. ie null
*/
template<class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::end() const{
	return Iterator(tail->next);
}


/*
Singly Linked List Destructor
Removes all the nodes one by one.
*/
template<class T>
SLinkedList<T>::~SLinkedList(){
	while (!isEmpty()){
		removeFromHead();
	}
}


/*
Adds the given element to the head of the linked list
*/
template<class T>
void SLinkedList<T>::addToHead(const T& t){
	if (head == 0){
		head = new Node<T>(t);
		tail = head;
	}
	else{
		head = new Node<T>(t,head);
	}
}


/*
Adds the given element to the tail of the linked list.
*/
template<class T>
void SLinkedList<T>::addToTail(const T& t){
	
	if (tail == 0){
		tail = new Node<T>(t);
		head = tail;
	}
	else{
		tail->next = new Node<T>(t);
		tail = tail->next;
	}
}


/*
Precondition: list should not be empty.
isEmpty() check to be performed prior to call.
Removes the element from the head and returns it's value.
*/
template<class T>
T SLinkedList<T>::removeFromHead(){
	Node<T> * oldhead = head;
	T val = oldhead->elem;
	if (head == tail){
		head = 0;
		tail = 0;
	}
	else{
		head = head->next;
	}
	delete oldhead;
	return val;
}	


/*
Precondition: list should not be empty.
isEmpty() check to be performed prior to the call.
Removes the element from the tail and returns it's value.
*/
template <class T>
T SLinkedList<T>::removeFromTail(){
	Node<T> * oldtail = tail;
	T val = oldtail->elem;
	if (head == tail){
		head = 0;
		tail = 0;
	}
	else{
		Node<T> *tmp = head;
		while (tmp->next != tail){
			tmp = tmp->next;
		}
		tmp->next = 0;
		tail = tmp;
	}
	delete oldtail;
	return val;
}		


/*
Precondition: list is not empty.
isEmpty() check to be performed prior to the removal.
Returns the minimum value present in the list.
*/
template <class T>
T SLinkedList<T>::getMin()const{
	if (head == tail){
		return head->elem;
	}
	else{
		Node<T> * minNode = head;
		Node<T> * tmp = head;
		
		while (tmp != 0){
			if (tmp->elem < minNode->elem){
				minNode = tmp;
			}
			tmp = tmp->next;
		}
		return minNode->elem;
	}
}		



/*
Precondition: List is not empty.
isEmpty() check to be performed prior to the removal.
Returns the maximum value present in the List.
*/
template <class T>
T SLinkedList<T>::getMax()const{
        if (head == tail){
                return head->elem;
        }
        else{
                Node<T> * maxNode = head;
                Node<T> * tmp = head;

                while (tmp != 0){
                        if (tmp->elem > maxNode->elem){
                                maxNode = tmp;
                        }
                        tmp = tmp->next;
                }
                return maxNode->elem;
        }
}


/*
Removes all the elements equal to the value  specified in the argument.
*/
template<class T>
void SLinkedList<T>::remove(const T& t){
	if (!isEmpty()){
		
		Node<T> * tmp = head;
		Node<T> * prevTmp;
		while (tmp != 0){
			if (tmp->elem == t && tmp == head){
				removeFromHead();
				tmp = head;
			}
			else if (tmp->elem == t && tmp == tail){
				removeFromTail();
				tmp = tail->next;
			}
			else if (tmp->elem == t){
				prevTmp->next = tmp->next;
				delete tmp;
				tmp = prevTmp->next;
			}
			else{
				prevTmp=tmp;
				tmp = tmp->next;
			}
		}
	}
}

			
/*
Returns true if the list is empty.
*/
template <class T>
bool SLinkedList<T>::isEmpty() const{
	return head == 0;
}


/*
Returns true if the list contains the element specified in the argument
*/
template <class T>
bool SLinkedList<T>::contains(const T& t) const{
		
	Node<T> * tmp = head;
	while (tmp != 0){
		if (tmp->elem == t){
			return true;
		}
		tmp = tmp->next;
	}
	
	return false;
}


/*
Reverses the sequence of elements stored in the list.
*/
template<class T>
void SLinkedList<T>::reverse(){
	reverseList(head, tail);
}

/*
Helper private method to reverse the list.
*/
template<class T>
void SLinkedList<T>::reverseList(Node<T> * thead, Node<T> * ttail){
	if (ttail == thead){
		return;
	}
	else if (thead->next == ttail){
		T tmpData = thead->elem;
		thead->elem = ttail->elem;
		ttail->elem = tmpData;
		return;
	}
	else{
		T tmpData = thead->elem;
		thead->elem = ttail->elem;
		ttail->elem = tmpData;
		Node<T> *tmp = thead;
		while (tmp->next != ttail){
			tmp = tmp->next;
		}
		reverseList(thead->next,tmp);
	}
}

/*
Display the elements stored in the list.
*/
template<class T>
void SLinkedList<T>::display()const{
	Node<T> * tmp = head;

	while (tmp != 0){
		std::cout << tmp->elem << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;

}

/*
Iterator methods
*/

/*
Returns the value stored in the node that the iterator points to.
*/
template<class T>
T& SLinkedList<T>::Iterator::operator*(){
	return v->elem;
}


/*
Returns true if the two iterators point to the same node.
*/
template<class T>
bool SLinkedList<T>::Iterator::operator==(const SLinkedList<T>::Iterator& p)const{
	return v == p.v;
}


/*
Returns true if the two iterators point to different nodes.
*/
template<class T>
bool SLinkedList<T>::Iterator::operator!=(const SLinkedList<T>::Iterator& p) const{
	return v != p.v;
}


/*
Iterator increment operator
*/
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++(){

	v = v->next;
	return *this;
	
}


#endif
