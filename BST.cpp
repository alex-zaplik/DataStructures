#include "BST.h"

#include <vector>
#include <sstream>

bool BST::find(std::string key)
{
	return find(root, key) != nullptr;
}

unsigned long BST::counted_find(std::string key)
{
	unsigned long compares = 0;
	find(root, key, compares);
	return compares;
}

std::string BST::min()
{
	if (root == nullptr)
	{
		return null_type();
	}

	Node* x = min(root);
	return (x != nullptr) ? x->key : null_type();
}

std::string BST::max()
{
	if (root == nullptr)
	{
		return null_type();
	}

	Node* x = max(root);
	return (x != nullptr) ? x->key : null_type();
}

std::string BST::succ(std::string key, bool skip_repeats)
{
	Node* x = find(root, key);
	x = succ(x, skip_repeats);
	return (x != nullptr) ? x->key : null_type();
}

std::string BST::pred(std::string key, bool skip_repeats)
{
	Node* x = find(root, key);
	x = pred(x, skip_repeats);
	return (x != nullptr) ? x->key : null_type();
}

void BST::inorder(Node* x, std::vector<std::string> &sorted)
{
	if (x != nullptr)
	{
		inorder(x->left, sorted);
		sorted.push_back(x->key);
		inorder(x->right, sorted);
	}
}

void BST::postorder_delete(Node* x)
{
	if (x != nullptr)
	{
		postorder_delete(x->left);
		postorder_delete(x->right);
		delete x;
	}
}

void BST::print(Node* x, std::stringstream* ss)
{
	if (x != nullptr)
	{
		*ss << "(" << x->key << " " << ((x->color == Color::BLACK) ? "B" : "R") << " ";
		print(x->left, ss);
		print(x->right, ss);
		*ss << ") ";
	}
	else
	{
		*ss << "*";
	}
}

BST::~BST()
{
	if (root != nullptr)
	{
		postorder_delete(root->left);
		postorder_delete(root->right);
		delete root;
	}
}

void BST::ins(std::string key)
{
	Node* x = root;
	Node* y = nullptr;

	while (x != nullptr)
	{
		y = x;

		if (key < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	Node* z = new Node(key, y, nullptr, nullptr);

	if (root == nullptr)
	{
		root = z;
	}
	else if (key < y->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}

	node_count++;
}

void BST::del(std::string key)
{
	Node* z = find(root, key);

	if (z == nullptr)
	{
		return;
	}

	if (z->left == nullptr)
	{
		transplant(z, z->right);
	}
	else if (z->right == nullptr)
	{
		transplant(z, z->left);
	}
	else
	{
		Node* y = min(z->right);
		if (y->parent != z)
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}

	node_count--;
}

std::vector<std::string> BST::inorder()
{
	std::vector<std::string> sorted;
	inorder(root, sorted);
	return sorted;
}

std::string BST::print()
{
	std::stringstream ss;
	print(root, &ss);
	return ss.str();
}

unsigned int BST::size()
{
	return node_count;
}

void BST::operator delete(void * p)
{
	((BST*)p)->postorder_delete(((BST*)p)->root);
	free(p);
}

void BST::transplant(Node* u, Node* v)
{
	if (u->parent == nullptr)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v != nullptr)
	{
		v->parent = u->parent;
	}
}

Node* BST::find(Node* x, std::string key)
{
	while (x != nullptr && x->key != key)
	{
		if (x->key > key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	return x;
}

Node* BST::find(Node* x, std::string key, unsigned long &depth)
{
	while (x != nullptr && x->key != key)
	{
		depth += 2;

		if (x->key > key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	depth++;

	return x;
}

Node* BST::min(Node* x)
{
	while (x->left != nullptr)
	{
		x = x->left;
	}

	return x;
}

Node* BST::max(Node* x)
{
	while (x->right != nullptr)
	{
		x = x->right;
	}

	return x;
}

Node* BST::succ(Node* x, bool skip_repeats)
{
	if (x == nullptr)
	{
		return nullptr;
	}

	if (x->right != nullptr)
	{
		Node* right_min = min(x->right);

		if (skip_repeats && right_min != nullptr && right_min->key == x->key)
		{
			return succ(right_min, skip_repeats);
		}

		return right_min;
	}

	Node* y = x->parent;

	while (y != nullptr && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	if (skip_repeats && y != nullptr && y->key == x->key)
	{
		return succ(y, skip_repeats);
	}

	return y;
}

Node* BST::pred(Node* x, bool skip_repeats)
{
	if (x == nullptr)
	{
		return nullptr;
	}

	if (x->left != nullptr)
	{
		Node* left_max = max(x->left);

		if (skip_repeats && left_max != nullptr && left_max->key == x->key)
		{
			return pred(left_max, skip_repeats);
		}

		return left_max;
	}

	Node* y = x->parent;

	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	if (skip_repeats && y != nullptr && y->key == x->key)
	{
		return pred(y, skip_repeats);
	}

	return y;
}
