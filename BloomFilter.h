#pragma once

#include "UnorderedContainer.h"

class BloomFilter : public UnorderedContainer
{
private:
	int m, k;
	std::vector<unsigned char> filter;

public:
	BloomFilter();
	BloomFilter(int m, int k);

	virtual void ins(std::string key);
	virtual void del(std::string key);
	virtual bool find(std::string key);
	virtual unsigned long counted_find(std::string key);
	virtual std::string print();
	virtual unsigned int size();
};

