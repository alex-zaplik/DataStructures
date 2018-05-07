#pragma once
#include "Container.h"
class UnorderedContainer : public Container
{
public:
	virtual std::string min() { return ""; }
	virtual std::string max() { return ""; }
	virtual std::string succ(std::string key, bool skip_repeats) { return ""; }
	virtual std::string pred(std::string key, bool skip_repeats) { return ""; }
	virtual std::vector<std::string> inorder()
	{
		std::vector<std::string> res;
		res.push_back("");
		return res;
	}
};

