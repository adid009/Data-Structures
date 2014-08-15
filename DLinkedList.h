/*
* Implementation of a Generic Doubly LinkedList in C++
*/
#pragma once
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

template<class T>
class DLinkedList;

/*
Node definition
*/
template <class T>
class Node{
	private:
	T elem;
	Node<T> * next;
	Node<T> * prev;

	public:
	Node(const T& el, Node<T> * n=0, Node<T> * p=0);
	Node();
	friend class DLinkedList<T>;
};

/*
Node constructor
*/
template<class T>
Node<T>::Node():next(0),prev(0){
}

/*
Node Constructor
*/
template<class T>
Node<T>::Node(const T& el, Node<T> * n, Node<T> * p):elem(el),next(n),prev(p){
}


/*
Definition for the Doubly Linked List
*/
template <class T>
class DLinkedList{

	private:
	Node<T> * head;
	Node<T> * tail;

	public:
	
	class Iterator{
	
		private:
		Node<T> * v;
		Iterator(Node<T> *u);
		public:
		T& operator*();
		bool operator==(const Iterator& p)const;
		bool operator!=(const Iterator& p)const;
		Iterator& operator++();
		Iterator& operator--();

		friend class DLinkedList<T>;
	
	};


	DLinkedList();
	DLinkedList(const DLinkedList<T>& dl);
	DLinkedList<T>& operator=(const DLinkedList<T>& dl);

	~DLinkedList();
	
	Iterator begin() const;
	Iterator end() const;

	void addToHead(const T& el);
	void addToTail(const T& el);
	void add(const T& el);
	void add(const Iterator& p, const T& el);
	
	T removeFromHead();
	T removeFromTail();
	void remove(const T& el);
	void remove(const Iterator& p);

	void reverse();

	T getMax() const;
	T getMin() const;

	T peekHead() const;
	T peekTail() const;

	bool isEmpty() const;
	void display() const;
};


/*
Doubly Linked List Constructor
*/
template<class T>
DLinkedList<T>::DLinkedList():head(0),tail(0){
}


/*
Doubly Linked List Copy Constructor
*/
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& dl):head(0),tail(0){
	if (!dl.isEmpty()){
		for (DLinkedList<T>::Iterator i = dl.begin(); i != dl.end(); ++i){
			addToTail(*i);
		}
	}	
}


/*
Doubly Linked List assignment operator
*/
template<class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& dl){ 
	if (this == &dl){
		return *this;
	}
	else{
		while (!isEmpty()){
			removeFromHead();
		}
		for (DLinkedList<T>::Iterator i = dl.begin(); i != dl.end(); ++i){
			addToTail(*i);
		}
		return *this;
	}
}

/*
Doubly Linked List Destructor
*/
template<class T>
DLinkedList<T>::~DLinkedList(){
	while( !isEmpty()){
		removeFromHead();
	}
}


/*
Returns an iterator pointing to the head of the list.
*/
template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::begin() const{
	return Iterator(head);
}


/*
Returns an iterator pointing to the node after the tail of the list.
*/
template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::end() const{
	return Iterator(tail->next);
}


/*
Adds the element to the head of the list.
*/
template <class T>
void DLinkedList<T>::addToHead(const T& el){
	
	
	if (isEmpty()){
		head = new Node<T>(el);
		tail = head;
	}
	else{
		Node<T> * oldhead = head;
		head = new Node<T>(el,oldhead);
		oldhead->prev = head;
	}
}


/*
Adds the element to the tail of the list.
*/
template <class T>
void DLinkedList<T>::addToTail(const T& el){
	
	if (isEmpty()){
		tail = new Node<T>(el);
		head = tail;
	}

	else{
		Node<T> * oldtail = tail;
		oldtail->next = new Node<T>(el,0,oldtail);
		tail = oldtail->next;
	}
}

/*
Adds the element to the head of the list
*/
template<class T>
void DLinkedList<T>::add(const T& el){
	addToHead(el);
}		


/*
Adds the element to the position behind the position being pointed to by the iterator
*/
template<class T>
void DLinkedList<T>::add(const DLinkedList<T>::Iterator& p, const T& el){
	Node<T> * tmp = p.v;
	if (tmp == head){
		addToHead(el);
	}
	else if (tmp == 0){
		addToTail(el);
	}
	else{
		Node<T>* newNode = new Node<T>(el,tmp,tmp->prev);
		tmp->prev->next = newNode;
		tmp->prev = newNode;
	}
}


/*
Precondition: The list is not empty.
Removes the value from the head of the list and returns it's value.
*/
template <class T>
T DLinkedList<T>::removeFromHead(){
	Node<T> * oldhead = head;
	T val = oldhead->elem;

	if (head == tail){
		head = 0;
		tail = 0;
	}
	else{
		head = oldhead->next;
		head->prev = 0;
	}
	delete oldhead;
	return val;
}



/*
Precondition: The list is not empty.
Removes the element from the tail of the list and returns it's value.
*/
template<class T>
T DLinkedList<T>::removeFromTail(){
	Node<T> * oldtail = tail;
	T val = oldtail->elem;

	if (head == tail){
		head = 0;
		tail = 0;
	}
	else{
		tail = oldtail->prev;
		tail->next = 0;
	}
	delete oldtail;
	return val;
}

/*
Removes all the nodes from the list whose value equals the value in the argument.
*/
template <class T>
void DLinkedList<T>::remove(const T& el){
	
	
	if (!isEmpty()){
		Node<T> * tmp = head;
		while(tmp != 0){
			if (tmp->elem == el && tmp == head){
				removeFromHead();
				tmp = head;
			}
			else if (tmp->elem == el && tmp == tail){
				removeFromTail();
				tmp = tail->next;
			}	
			else if (tmp->elem == el){
				Node<T> * oldtmp = tmp;
				oldtmp->prev->next = oldtmp->next;
				oldtmp->next->prev = oldtmp->prev;
				tmp = oldtmp->next;
				delete oldtmp;
			}
			else{
				tmp = tmp->next;
			}
		}
	}
}


/*
Removes the node pointed to by the iterator from the list.
*/
template<class T>
void DLinkedList<T>::remove(const DLinkedList<T>::Iterator& p){
	Node<T> * oldNode = p.v;
	oldNode->prev->next = oldNode->next;
	oldNode->next->prev = oldNode->prev;

	delete oldNode;
}

/*
Reverses the sequence of the values stored in the linked list.
*/
template <class T>
void DLinkedList<T>:: reverse(){
	Node<T> * thead = head;
	Node<T> * ttail = tail;

	if (!isEmpty()){
		while (ttail != thead && ttail->next != thead){
		
			T tval = thead->elem;
			thead->elem = ttail->elem;
			ttail->elem = tval;
			
			thead = thead->next;
			ttail = ttail->prev;
		}
	}
}

/*
Precondition: the Linked List is not empty.
Returns the maximum value contained in the Linked List.
*/
template <class T>
T DLinkedList<T>::getMax() const{
	Node<T> * tmp = head;
	T max = tmp->elem;
	while (tmp != 0){
		if (tmp->elem > max){
			max = tmp->elem;
		}
		tmp = tmp->next;
	}
	return max;
}


/*
Precondition: the Linked List is not empty.
Returns the minimum value contained in the Linked List.
*/
template <class T>
T DLinkedList<T>::getMin() const{
        Node<T> * tmp = head;
        T min = tmp->elem;
        while (tmp != 0){
                if (tmp->elem < min){
                        min = tmp->elem;
                }
                tmp = tmp->next;
        }
        return min;
}


/*
Precondition: the Linked List is not empty.
Returns the value stored at the head of the Linked List.
*/
template<class T>
T DLinkedList<T>::peekHead() const{
	return head->elem;
}


/*
Precondition: the Linked List is not empty.
Returns the value stored at the tail of the Linked List
*/
template<class T>
T DLinkedList<T>::peekTail() const{
	return tail->elem;
}

/*
Returns true if the linked list is empty.
*/
template <class T>
bool DLinkedList<T>::isEmpty() const{
	return head == 0;
}

/*
Displays the values of the elements stored in the Linked List.
*/
template<class T>
void DLinkedList<T>::display() const{
	Node<T> *tmp = head;

	while (tmp != 0){
		std::cout << tmp->elem << " ";
		tmp = tmp->next;
	}
	std::cout << "\n";
}

/*
The Iterator functions are defined below.
*/

/*
Iterator constructor.
*/
template<class T>
DLinkedList<T>::Iterator::Iterator(Node<T> * u){
	v = u;
}


/*
Returns the element stored in the node pointed to by the iterator.
*/
template<class T>
T& DLinkedList<T>::Iterator::operator*(){
	return v->elem;
}


/*
Returns true if the two iterators point to the same node.
*/
template<class T>
bool DLinkedList<T>::Iterator::operator==(const Iterator& p) const{
	return v == p.v;
}


/*
Returns true if the two iterators point to different nodes.
*/
template<class T>
bool DLinkedList<T>::Iterator::operator!=(const Iterator& p) const{
	return v != p.v;
}


/*
Increment operator for the iterator.
*/
template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++(){
	v = v->next;
	return *this;
}


/*
Decrement operator for the Iterator.
*/
template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator--(){
	v = v->prev;
	return *this;
}

#endif
