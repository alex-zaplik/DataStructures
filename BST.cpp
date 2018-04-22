#include "BST.h"

#include <vector>

template<typename t>
bool BST<t>::find(t key)
{
	return find(root, key) != nullptr;
}

template<typename t>
t BST<t>::min()
{
	if (root == nullptr)
	{
		return null_type();
	}

	Node<t>* x = min(root);
	return (x != nullptr) ? x->key : null_type();
}

template<typename t>
t BST<t>::max()
{
	if (root == nullptr)
	{
		return null_type();
	}

	Node<t>* x = max(root);
	return (x != nullptr) ? x->key : null_type();
}

template<typename t>
t BST<t>::succ(t key)
{
	Node<t>* x = find(root, key);
	x = succ(x);
	return (x != nullptr) ? x->key : null_type();
}

template<typename t>
t BST<t>::pred(t key)
{
	Node<t>* x = find(root, key);
	x = pred(x);
	return (x != nullptr) ? x->key : null_type();
}

template<typename t>
void BST<t>::inorder(Node<t>* x, std::vector<t> &sorted)
{
	if (x != nullptr)
	{
		inorder(x->left, sorted);
		sorted.push_back(x->key);
		inorder(x->right, sorted);
	}
}

template<typename t>
void BST<t>::postorder_delete(Node<t>* x)
{
	if (x != nullptr)
	{
		postorder_delete(x->left);
		postorder_delete(x->right);
		delete x;
	}
}

template<typename t>
BST<t>::~BST()
{
	if (root != nullptr)
	{
		postorder_delete(root->left);
		postorder_delete(root->right);
		delete root;
	}
}

template<typename t>
void BST<t>::ins(t key)
{
	Node<t>* x = root;
	Node<t>* y = nullptr;

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

	Node<t>* z = new Node<t>(key, y, nullptr, nullptr);

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
}

template<typename t>
void BST<t>::del(t key)
{
	Node<t>* z = find(root, key);

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
		Node<t>* y = min(z->right);
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
}

template<typename t>
std::vector<t> BST<t>::inorder()
{
	std::vector<t> sorted;
	inorder(root, sorted);
	return sorted;
}

template<typename t>
void BST<t>::operator delete(void * p)
{
	((BST<t>*)p)->postorder_delete(((BST<t>*)p)->root);
	free(p);
}

template<typename t>
void BST<t>::transplant(Node<t>* u, Node<t>* v)
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

template<typename t>
Node<t>* BST<t>::find(Node<t>* x, t key)
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

template<typename t>
Node<t>* BST<t>::min(Node<t>* x)
{
	while (x->left != nullptr)
	{
		x = x->left;
	}

	return x;
}

template<typename t>
Node<t>* BST<t>::max(Node<t>* x)
{
	while (x->right != nullptr)
	{
		x = x->right;
	}

	return x;
}

template<typename t>
Node<t>* BST<t>::succ(Node<t>* x)
{
	if (x == nullptr)
	{
		return nullptr;
	}

	if (x->right != nullptr)
	{
		return min(x->right);
	}

	Node<t>* y = x->parent;

	while (y != nullptr && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

template<typename t>
Node<t>* BST<t>::pred(Node<t>* x)
{
	if (x == nullptr)
	{
		return nullptr;
	}

	if (x->left != nullptr)
	{
		return max(x->left);
	}

	Node<t>* y = x->parent;

	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}
