#pragma once

#include <map>
#include <functional>
#include <chrono>

#include "Container.h"

class InputHandler
{
private:
	Container* cont;
	std::map<std::string, std::function<std::string(std::string)> > func_map;

	std::map<std::string, unsigned int> func_count;
	std::map<std::string, unsigned long long> func_time;
	std::chrono::steady_clock::time_point start;
	unsigned int max_elements = 0;
	bool timed = false;

	bool has_order();
	void init();

	std::string ins(std::string key);
	std::string del(std::string key);
	std::string find(std::string key);

	std::string min(std::string key);
	std::string max(std::string key);
	std::string succ(std::string key);
	std::string inorder(std::string key);

	std::string load(std::string key);

public:
	InputHandler(Container* cont);
	InputHandler(Container* cont, bool timed);
	std::string handle_line(std::string line);
	std::string stats();
};

