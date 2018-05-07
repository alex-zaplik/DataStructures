#include "BloomFilter.h"

#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>

BloomFilter::BloomFilter() : m{ 524288 }, k{ 6 }
{
	int size = std::ceil(m / 8.0);
	for (int i = 0; i < size; i++)
	{
		filter.push_back(0);
	}
}

BloomFilter::BloomFilter(int m, int k) : m{ m }, k{ k }
{
	int size = std::ceil(m / 8.0);
	for (int i = 0; i < size; i++)
	{
		filter.push_back(0);
	}
}

void BloomFilter::ins(std::string key)
{
	for (int i = 0; i < k; i++)
	{
		std::string h = std::to_string(i) + key + std::to_string(i);
		unsigned int hash = std::hash<std::string>{} (h);
		hash /= (std::numeric_limits<size_t>::max() / m);

		filter[hash / 8] |= 1 << (hash % 8);
	}
}

void BloomFilter::del(std::string key) {}

bool BloomFilter::find(std::string key)
{
	for (int i = 0; i < k; i++)
	{
		std::string h = std::to_string(i) + key + std::to_string(i);
		unsigned int hash = std::hash<std::string>{} (h);
		hash /= (std::numeric_limits<size_t>::max() / m);

		unsigned char a = filter[hash / 8];
		unsigned char b = 1 << (hash % 8);
		unsigned char c = a & b;

		if (c == 0) return false;
	}

	return true;
}

unsigned long BloomFilter::counted_find(std::string key)
{
	return 0;
}

std::string BloomFilter::print()
{
	std::stringstream ss;

	ss << "[";
	for (int i = 0; i < m; i++)
	{
		unsigned char c = filter[i / 8];
		unsigned char d = 1 << (i % 8);
		unsigned int a = (c & d);
		a >>= i % 8;
		ss << a;
	}
	ss << "]";

	return ss.str();
}

unsigned int BloomFilter::size()
{
	unsigned int ones = 0;
	for (int i = 0; i < m; i++)
	{
		ones += (filter[i / 8] & (1 << (i % 8))) >> i % 8;
	}

	return ones;
}
