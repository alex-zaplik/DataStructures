#pragma once

#include <vector>

template <typename t>
class Container
{
public:
	virtual void ins(t key) = 0;
	virtual void del(t key) = 0;
	virtual bool find(t key) = 0;
	virtual t min() = 0;
	virtual t max() = 0;
	virtual t succ(t key) = 0;
	virtual t pred(t key) = 0;
	virtual std::vector<t> inorder() = 0;
};
