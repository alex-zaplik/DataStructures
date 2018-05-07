#include "LinkedList.h"

#include <sstream>

std::vector<std::string> LinkedList::inorder()
{
	std::vector<std::string> res{ std::begin(data), std::end(data) };
	return res;
}

void LinkedList::ins(std::string key)
{
	data.push_back(key);
}

void LinkedList::del(std::string key)
{
	for (auto it = data.begin(); it != data.end(); it++)
	{
		if (*it == key)
		{
			data.erase(it);
			break;
		}
	}
}

bool LinkedList::find(std::string key)
{
	for (auto it = data.begin(); it != data.end(); it++)
	{
		if (*it == key)
		{
			return true;
		}
	}

	return false;
}

unsigned long LinkedList::counted_find(std::string key)
{
	unsigned long compares = 0;

	for (auto it = data.begin(); it != data.end(); it++)
	{
		compares++;

		if (*it == key)
		{
			return compares;
		}
	}

	return false;
}

std::string LinkedList::print()
{
	std::stringstream ss;

	for (auto it = data.begin(); it != data.end(); it++)
	{
		ss << *it << " ";
	}

	return ss.str();
}

unsigned int LinkedList::size()
{
	return data.size();
}
