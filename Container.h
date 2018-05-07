#pragma once

#include <vector>

class Container
{
public:
	virtual void ins(std::string key) = 0;
	virtual void del(std::string key) = 0;
	virtual bool find(std::string key) = 0;
	virtual unsigned long counted_find(std::string key) = 0;
	virtual std::string min() = 0;
	virtual std::string max() = 0;
	virtual std::string succ(std::string key, bool skip_repeats) = 0;
	virtual std::string pred(std::string key, bool skip_repeats) = 0;
	virtual std::vector<std::string> inorder() = 0;
	virtual std::string print() = 0;
	virtual unsigned int size() = 0;

	std::string null_type() { return ""; }
};