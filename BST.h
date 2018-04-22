#pragma once

#include <vector>

#include "Container.h"

template <typename t>
struct Node
{
	Node<t>* parent;
	Node<t>* left;
	Node<t>* right;

	t key;

	Node(t key) : 
		key{ key }, parent { nullptr }, left{ nullptr }, right{ nullptr } {}

	Node(t key, Node<t>* parent, Node<t>* left, Node<t>* right) :
		key{ key }, parent{ parent }, left{ left }, right{ right } {}
};

template <typename t>
class BST : public Container<t>
{
protected:
	Node<t>* root;

	virtual void transplant(Node<t>* u, Node<t>* v);
	virtual Node<t>* find(Node<t>* x, t key);
	virtual Node<t>* min(Node<t>* x);
	virtual Node<t>* max(Node<t>* x);
	virtual Node<t>* succ(Node<t>* x);
	virtual Node<t>* pred(Node<t>* x);
	virtual void inorder(Node<t>* x, std::vector<t> &sorted);
	virtual void postorder_delete(Node<t>* x);

public:
	BST() : root{ nullptr } {}
	~BST();

	virtual void ins(t key);
	virtual void del(t key);
	virtual bool find(t key);
	virtual t min();
	virtual t max();
	virtual t succ(t key);
	virtual t pred(t key);
	virtual std::vector<t> inorder();

	t null_type() { return nullptr; }

	void operator delete(void* p);
};

std::string BST<std::string>::null_type() { return ""; }
template class BST<std::string>;