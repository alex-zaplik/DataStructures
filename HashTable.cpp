#include "HashTable.h"

#include <sstream>
#include <functional>

#include "LinkedList.h"
#include "RBT.h"

HashTable::HashTable() : data_size{ 128 }
{
	init_container();
}

HashTable::HashTable(unsigned int size) : data_size{ size }
{
	init_container();
}

HashTable::HashTable(std::function<int(std::string)> hash_func) : hash_func{ hash_func }, data_size{ 128 }
{
	init_container();
}

HashTable::HashTable(unsigned int size, std::function<int(std::string)> hash_func) : hash_func{ hash_func }, data_size{ size }
{
	init_container();
}

HashTable::HashTable(unsigned int size, unsigned int switch_point) : switch_point{ switch_point }, data_size{ size }
{
	init_container();
}

HashTable::HashTable(std::function<int(std::string)> hash_func, unsigned int switch_point) :
	hash_func{ hash_func }, switch_point{ switch_point }, data_size{ 128 }
{
	init_container();
}

HashTable::HashTable(unsigned int size, std::function<int(std::string)> hash_func, unsigned int switch_point) :
	hash_func{ hash_func }, switch_point{ switch_point }, data_size{ size }
{
	init_container();
}

HashTable::~HashTable()
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		delete data[i];
	}
}

void HashTable::init_container()
{
	for (unsigned int i = 0; i < data_size; i++)
	{
		data.push_back(new LinkedList);
	}
}

int HashTable::hash(std::string key)
{
	return std::hash<std::string>{}(key) / (std::numeric_limits<size_t>::max() / 128);
}

void HashTable::ins(std::string key)
{
	int h;

	if (hash_func != nullptr)
	{
		h = hash_func(key);
	}
	else
	{
		h = hash(key);
	}

	if (data[h] == nullptr)
	{
		data[h] = new LinkedList;
	}

	if (dynamic_cast<const LinkedList*>(data[h]) != nullptr && data[h]->size() >= switch_point)
	{
		std::vector<std::string> l = data[h]->inorder();
		RBT* rbt = new RBT;

		for (unsigned int i = 0; i < l.size(); i++)
		{
			rbt->ins(l[i]);
		}

		delete data[h];
		data[h] = rbt;
	}

	data[h]->ins(key);
}

void HashTable::del(std::string key)
{
	int h;

	if (hash_func != nullptr)
	{
		h = hash_func(key);
	}
	else
	{
		h = hash(key);
	}

	if (data[h] == nullptr)
	{
		return;
	}

	if (dynamic_cast<const RBT*>(data[h]) != nullptr && data[h]->size() <= switch_point + 1)
	{
		std::vector<std::string> l = data[h]->inorder();
		LinkedList* ll = new LinkedList;

		for (unsigned int i = 0; i < l.size(); i++)
		{
			ll->ins(l[i]);
		}

		delete data[h];
		data[h] = ll;
	}

	data[h]->del(key);
}

bool HashTable::find(std::string key)
{
	int h;

	if (hash_func != nullptr)
	{
		h = hash_func(key);
	}
	else
	{
		h = hash(key);
	}

	if (data[h] == nullptr)
	{
		return false;
	}

	return data[h]->find(key);
}

unsigned long HashTable::counted_find(std::string key)
{
	int h;

	if (hash_func != nullptr)
	{
		h = hash_func(key);
	}
	else
	{
		h = hash(key);
	}

	if (data[h] == nullptr)
	{
		return 0;
	}

	return data[h]->counted_find(key);
}

std::string HashTable::print()
{
	std::stringstream ss;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (data[i] != nullptr) ss << "[ " << data[i]->print() << "]\n";
	}

	return ss.str();
}

unsigned int HashTable::size()
{
	unsigned int s = 0;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (data[i] != nullptr) s += data[i]->size();
	}

	return s;
}
