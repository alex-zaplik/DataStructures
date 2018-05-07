#pragma once

#include "BST.h"

class RBT : public BST
{
private:
	void left_rotate(Node* x);
	void right_rotate(Node* x);
	void insert_fixup(Node* x);
	void delete_fixup(Node* x);

public:
	virtual void ins(std::string key);
	virtual void del(std::string key);
};
