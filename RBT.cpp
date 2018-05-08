#include "RBT.h"

#include <sstream>

void RBT::left_rotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;

	if (y->left != nullptr)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		BST::root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void RBT::right_rotate(Node* x)
{
	Node* y = x->left;
	x->left = y->right;

	if (y->right != nullptr)
	{
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		BST::root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

void RBT::insert_fixup(Node* x)
{
	Node* xp, * xpp;
	Node* y;

	while (x != root && x->color == Color::RED && x->parent->color == Color::RED)
	{
		xp = x->parent;
		xpp = x->parent->parent;

		if (xp == xpp->left)
		{
			y = xpp->right;

			if (y != nullptr && y->color == Color::RED)
			{
				xpp->color = Color::RED;
				xp->color = Color::BLACK;
				y->color = Color::BLACK;
				x = xpp;
			}
			else
			{
				if (x == xp->right)
				{
					left_rotate(xp);
					x = xp;
					xp = x->parent;
				}

				right_rotate(xpp);

				auto temp = xp->color;
				xp->color = xpp->color;
				xpp->color = temp;
				x = xp;
			}
		}
		else
		{
			y = xpp->left;

			if (y != nullptr && y->color == Color::RED)
			{
				xpp->color = Color::RED;
				xp->color = Color::BLACK;
				y->color = Color::BLACK;
				x = xpp;
			}
			else
			{
				if (x == xp->left)
				{
					right_rotate(xp);
					x = xp;
					xp = x->parent;
				}

				left_rotate(xpp);

				auto temp = xp->color;
				xp->color = xpp->color;
				xpp->color = temp;
				x = xp;
			}
		}
	}

	BST::root->color = Color::BLACK;
}

void RBT::ins(std::string key)
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

	z->color = Color::RED;
	insert_fixup(z);

	node_count++;
}

void RBT::delete_fixup(Node* x)
{
	if (x == nullptr)
	{
		return;
	}

	Node* w;

	while (x != BST::root && x->color == Color::BLACK)
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;

			if (w->color == Color::RED)
			{
				w->color = Color::BLACK;
				x->parent->color = Color::RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == Color::BLACK && w->right->color == Color::BLACK)
			{
				w->color = Color::RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == Color::BLACK)
				{
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					right_rotate(w);
					w = x->parent->right;
				}

				w->color = w->parent->color;
				x->parent->color = Color::BLACK;
				w->right->color = Color::BLACK;
				left_rotate(x->parent);
				x = BST::root;
			}
		}
		else
		{
			w = x->parent->left;

			if (w->color == Color::RED)
			{
				w->color = Color::BLACK;
				x->parent->color = Color::RED;
				right_rotate(x->parent);
				w = x->parent->left;
			}

			if (w->right->color == Color::BLACK && w->left->color == Color::BLACK)
			{
				w->color = Color::RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == Color::BLACK)
				{
					w->right->color = Color::BLACK;
					w->color = Color::RED;
					left_rotate(w);
					w = x->parent->left;
				}

				w->color = w->parent->color;
				x->parent->color = Color::BLACK;
				w->left->color = Color::BLACK;
				right_rotate(x->parent);
				x = BST::root;
			}
		}
	}

	x->color = Color::BLACK;
}

void RBT::del(std::string key)
{
	Node* z = find(root, key);

	if (z == nullptr)
	{
		return;
	}

	Node* x;
	Node* y = z;
	Color y_color = (y) ? y->color : Color::BLACK;

	if (z->left == nullptr)
	{
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == nullptr)
	{
		x = z->left;
		transplant(z, z->left);
	}
	else
	{
		y = min(z->right);
		y_color = y->color;
		x = y->right;

		if (y->parent == z)
		{
			if (x != nullptr)
			{
				x->parent = y;
			}
		}
		else
		{
			transplant(y, y->right);
			y->right = z->right;
			if (y->right != nullptr) y->right->parent = y;
		}

		transplant(z, y);
		y->left = z->left;
		if (y->left != nullptr) y->left->parent = y;
		y->color = z->color;
	}

	if (y_color == Color::BLACK)
	{
		delete_fixup(x);
	}

	node_count--;
}
