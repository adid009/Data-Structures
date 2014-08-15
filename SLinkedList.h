#ifndef SLINKED_LIST_H
#define SLINKED_LIST_H

#include <iostream>

template< class T>
class SLinkedList;

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

template<class T>
class SLinkedList{

	private:
	Node<T> * head;
	Node<T> * tail;
	void reverseList(Node<T> *thead, Node<T> * ttail);

	public:
	SLinkedList();
	~SLinkedList();

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

template<class T>
SLinkedList<T>::SLinkedList():head(0), tail(0){
}

template<class T>
SLinkedList<T>::~SLinkedList(){
	while (!isEmpty()){
		removeFromHead();
	}
}

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
Assumes the List is not empty.
isEmpty() check to be performed prior to call.
Returns the element that was stored in the head.
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
Assumes the List is not empty.
isEmpty() check to be performed prior to the call.
Returns the element that was stored in the tail.
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
Assumes the list is not empty.
isEmpty() check to be performed prior to the removal.
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
Assumes the list is not empty.
isEmpty() check to be performed prior to the removal.
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




template<class T>
void SLinkedList<T>::remove(const T& t){
	if (!isEmpty()){
		if (head == tail){
			if (head->elem == t){
				delete head;
				head = 0;
				tail = 0;
			}
		}
		else{
			if(head->elem == t){
				removeFromHead();
			}
			else if (tail->elem == t){
				removeFromTail();
			}
			else{
				Node<T> *tmp = head->next;
				Node<T> *tmpPrev = head;
				
				while (tmp != tail){
					if (tmp->elem == t){
						tmpPrev->next = tmp->next;
						delete tmp;
						return;
					}
					tmp = tmp->next;
					tmpPrev = tmpPrev->next;
				}
			}
		}
	}
}
			

template <class T>
bool SLinkedList<T>::isEmpty() const{
	return head == 0;
}

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

template<class T>
void SLinkedList<T>::reverse(){
	reverseList(head, tail);
}

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

template<class T>
void SLinkedList<T>::display()const{
	Node<T> * tmp = head;

	while (tmp != 0){
		std::cout << tmp->elem << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}

#endif
