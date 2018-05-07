#pragma once

#include "Container.h"

#include <list>

class LinkedList : public Container
{
private:
	std::list<std::string> data;

public:
	virtual void ins(std::string key);
	virtual void del(std::string key);
	virtual bool find(std::string key);
	virtual unsigned long counted_find(std::string key);
	virtual std::string print();
	virtual unsigned int size();

	virtual std::string min() { return ""; }
	virtual std::string max() { return ""; }
	virtual std::string succ(std::string key, bool skip_repeats) { return ""; }
	virtual std::string pred(std::string key, bool skip_repeats) { return ""; }
	virtual std::vector<std::string> inorder();
};

