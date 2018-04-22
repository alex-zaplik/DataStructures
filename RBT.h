#pragma once
#include "BST.h"

enum Color
{
	RED, BLACK
};

template <typename t>
struct RBNode : public Node<t>
{
	Color color;

	RBNode(t key) :
		key{ key }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, color{ Color::BLACK } {}

	RBNode(t key, Color color) :
		key{ key }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, color{ color } {}

	RBNode(t key, Node<t>* parent, Node<t>* left, Node<t>* right) :
		key{ key }, parent{ parent }, left{ left }, right{ right }, color{ Color::BLACK } {}

	RBNode(t key, Node<t>* parent, Node<t>* left, Node<t>* right, Color color) :
		key{ key }, parent{ parent }, left{ left }, right{ right }, color{ color } {}
};

template<typename t>
class RBT : public BST<t>
{
private:
};

