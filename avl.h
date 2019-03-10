
#ifndef __AVL_H_
#define __AVL_H_

# include<iostream>
# include<assert.h>
using namespace std;
template<class T,class K>
class AVLnode
{
public:
	T data;
	K key;
	int balanceFactor;
	AVLnode<T, K>*p;
	AVLnode<T, K>*lc;
	AVLnode<T, K>*rc;
	AVLnode(T t, K k, AVLnode<T, K>*l=NULL, AVLnode<T, K>*r=NULL,AVLnode<T,K>*par=NULL)
	{
		data = t;
		key = k;
		lc = l;
		rc = r;
		p = par;
		balanceFactor = 0;
	}
	AVLnode(T t)
	{
		data = t;
		lc = NULL;
		rc = NULL;
		p = NULL;
		balanceFactor = 0;
	}
	AVLnode()
	{
		lc = NULL;
		rc = NULL;
		p = NULL;
		balanceFactor = 0;
	}
};

template<class T>
class Node
{
public:
	T data;
	Node*next;
	Node()
	{
		next = NULL;
	}
	Node(T d, Node *n = NULL)
	{
		data = d;
		next = n;
	}
};

template<class T>
class stack
{
public:
	Node<T> *top;
	stack()
	{
		top = NULL;
	}

	void push(T x)
	{
		Node<T> *n = new Node<T>(x);
		n->next = top;
		top = n;
	}
	T pop()
	{
		assert(top != NULL);
		Node<T>* n = top;
		top = top->next;
		T t = n->data;
		delete n;
		return t;
	}
	bool is_empty()
	{
		return top == NULL;
	}
};

template<class T>
class node
{
public:
	T data;
	node*next;
	node()
	{
		next = NULL;
	}
	node(T d, node *n = NULL)
	{
		data = d;
		next = n;
	}
};

template<class T>
class queue
{
private:
	node<T>*front;
	node<T>*rear;
public:
	queue()
	{
		front = NULL;
		rear = NULL;
	}
	bool is_empty()
	{
		return front == NULL;
	}
	void Enqueue(T x)
	{
		node<T> *n = new node<T>(x);
		if (is_empty()) front = rear = n;
		else
		{
			rear->next = n;
			rear = n;
		}
	}
	T Dequeue()
	{
		assert(is_empty() == false);
		node<T>*n = front;
		front = front->next;
		T t = n->data;
		delete n;
		return t;
	}
	T front_value()
	{
		assert(front);
		return front->data;
	}
};

#endif //!avl.h

