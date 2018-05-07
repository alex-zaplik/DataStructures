#pragma once

#include "UnorderedContainer.h"

#include <functional>

class HashTable : public UnorderedContainer
{
private:
	unsigned int data_size;
	unsigned int switch_point = 164;

	std::vector<Container*> data;
	std::function<int(std::string)> hash_func;

	void init_container();
	int hash(std::string);

public:
	HashTable();
	HashTable(unsigned int size);
	HashTable(std::function<int(std::string)>);
	HashTable(unsigned int size, std::function<int(std::string)>);
	HashTable(unsigned int size, unsigned int switch_point);
	HashTable(std::function<int(std::string)>, unsigned int switch_point);
	HashTable(unsigned int size, std::function<int(std::string)>, unsigned int switch_point);
	~HashTable();

	virtual void ins(std::string key);
	virtual void del(std::string key);
	virtual bool find(std::string key);
	virtual unsigned long counted_find(std::string key);
	virtual std::string print();
	virtual unsigned int size();

	unsigned int get_switch_point() { return switch_point; }
};

