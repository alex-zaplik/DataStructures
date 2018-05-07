#pragma once

#include <vector>

#include "Container.h"

enum Color
{
	RED, BLACK
};

struct Node
{
	Node* parent;
	Node* left;
	Node* right;

	std::string key;
	Color color;

	Node(std::string key) :
		key{ key }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, color{ Color::BLACK } {}

	Node(std::string key, Color color) :
		key{ key }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, color{ color } {}

	Node(std::string key, Node* parent, Node* left, Node* right) :
		key{ key }, parent{ parent }, left{ left }, right{ right }, color{ Color::BLACK } {}

	Node(std::string key, Node* parent, Node* left, Node* right, Color color) :
		key{ key }, parent{ parent }, left{ left }, right{ right }, color{ color } {}
};

class BST : public Container
{
protected:
	Node* root;
	int node_count;

	void transplant(Node* u, Node* v);
	Node* find(Node* x, std::string key);
	Node* find(Node* x, std::string key, unsigned long &depth);
	Node* min(Node* x);
	Node* max(Node* x);
	Node* succ(Node* x, bool skip_repeats);
	Node* pred(Node* x, bool skip_repeats);
	void inorder(Node* x, std::vector<std::string> &sorted);
	void postorder_delete(Node* x);
	void print(Node* x, std::stringstream* ss);

public:
	BST() : root{ nullptr }, node_count{ 0 } {}
	~BST();

	virtual void ins(std::string key);
	virtual void del(std::string key);
	bool find(std::string key);
	unsigned long counted_find(std::string key);
	std::string min();
	std::string max();
	std::string succ(std::string key, bool skip_repeats);
	std::string pred(std::string key, bool skip_repeats);
	std::vector<std::string> inorder();
	std::string print();
	virtual unsigned int size();

	void operator delete(void* p);
};