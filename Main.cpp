#include <iostream>
#include <string>
#include <vector>

#include "BST.h"
#include "RBT.h"

template<typename t>
void test_tree(BST<t> tree)
{
	std::vector<std::string> sorted, old_sorted;
	std::string min = tree.min();
	std::string max = tree.max();

	std::cout << "::" << min << ":: - ::" << max << "::\n" << std::endl;

	tree.ins("zzz");
	tree.ins("ggg");
	tree.ins("hhh");
	tree.ins("ttt");
	tree.ins("aba");
	tree.ins("hhh");
	tree.ins("aaa");
	tree.ins("iii");

	sorted = tree.inorder();
	old_sorted = sorted;
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting ttt" << std::endl;
	tree.del("ttt");

	sorted = tree.inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting abb" << std::endl;
	tree.del("abb");

	sorted = tree.inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << "\n" << std::endl;

	for (unsigned int i = 0; i < old_sorted.size(); i++)
		std::cout << old_sorted[i] << ": " << ((tree.find(old_sorted[i])) ? "Yes" : "No") << std::endl;

	std::cout << std::endl;
	std::cout << "abb: " << ((tree.find("abb")) ? "Yes" : "No") << std::endl;
	std::cout << std::endl;

	std::cout << "Deleting aaa" << std::endl;
	tree.del("aaa");

	sorted = tree.inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting hhh" << std::endl;
	tree.del("hhh");

	sorted = tree.inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting zzz" << std::endl;
	tree.del("zzz");

	sorted = tree.inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << "\n" << std::endl;

	for (unsigned int i = 0; i < old_sorted.size(); i++)
		std::cout << old_sorted[i] << ": " << ((tree.find(old_sorted[i])) ? "Yes" : "No") << std::endl;

	min = tree.min();
	max = tree.max();

	std::cout << "\n::" << min << ":: - ::" << max << "::\n" << std::endl;

	while (min != tree.null_type())
	{
		std::cout << min << std::endl;
		min = tree.succ(min);
	}
	std::cout << std::endl;

	while (max != tree.null_type())
	{
		std::cout << max << std::endl;
		max = tree.pred(max);
	}
}

int main(int argc, char* argv[])
{
	std::cout << "------------ BST ------------" << std::endl;
	BST<std::string> tree;
	test_tree(tree);

	std::cout << std::endl; 

	std::cout << "------------ RBT ------------" << std::endl;
	RBT<std::string> rb_tree;
	test_tree(tree);

	std::cin.get();
}