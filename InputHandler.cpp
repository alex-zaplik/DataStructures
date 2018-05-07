#include "InputHandler.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

#include "HashTable.h"

InputHandler::InputHandler(Container* cont) : cont{ cont }
{
	init();
}

InputHandler::InputHandler(Container* cont, bool timed) : cont{ cont }, timed{ timed }
{
	init();
}

void InputHandler::init()
{
	start = std::chrono::high_resolution_clock::now();
	
	std::vector<std::string> commands;

	commands.push_back("insert");
	commands.push_back("delete");
	commands.push_back("find");

	commands.push_back("min");
	commands.push_back("max");
	commands.push_back("successor");
	commands.push_back("inorder");

	commands.push_back("load");

	this->func_map["insert"] = [=](std::string key) { return this->ins(key); };
	this->func_map["delete"] = [=](std::string key) { return this->del(key); };
	this->func_map["find"] = [=](std::string key) { return this->find(key); };

	this->func_map["min"] = [=](std::string key) { return this->min(key); };
	this->func_map["max"] = [=](std::string key) { return this->max(key); };
	this->func_map["successor"] = [=](std::string key) { return this->succ(key); };
	this->func_map["inorder"] = [=](std::string key) { return this->inorder(key); };

	this->func_map["load"] = [=](std::string key) { return this->load(key); };

	for (auto i = commands.begin(); i != commands.end(); i++)
	{
		this->func_count[*i] = 0;
		this->func_time[*i] = 0;
	}
}

std::string InputHandler::handle_line(std::string line)
{
	std::string command;
	std::string parameter;

	size_t pos = line.find(' ');
	size_t offset = 0;
	command = line.substr(0, pos);
	parameter = line.substr(pos + 1, line.size() - pos - 1);

	auto it = func_map.find(command);

	if (it != func_map.end())
	{
		func_count[command]++;

		if (!timed)
		{
			return this->func_map[command](parameter);
		}
		else
		{
			std::chrono::steady_clock::time_point s = std::chrono::high_resolution_clock::now();
			std::string res = this->func_map[command](parameter);
			std::chrono::steady_clock::time_point e = std::chrono::high_resolution_clock::now();
			long long exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count();
			func_time[command] += exec_time;
			std::cerr << "Time: " << exec_time << "ns" << std::endl;
			return res;
		}
	}
	return "Unknown command";
}

bool InputHandler::has_order()
{
	return dynamic_cast<const HashTable*>(this->cont) == nullptr;
}

std::string InputHandler::ins(std::string key)
{
	size_t pos = 0;
	size_t offset = 0;

	std::regex left("[A-Za-z].*");
	std::regex right(".*[A-Za-z]");

	if (!std::regex_match(key, left))
	{
		pos++;
		offset++;
	}

	if (!std::regex_match(key, right))
	{
		offset++;
	}

	key = key.substr(pos, key.size() - offset);

	cont->ins(key);
	max_elements = std::max(max_elements, cont->size());

	return "";
}

std::string InputHandler::del(std::string key)
{
	cont->del(key);
	return "";
}

std::string InputHandler::find(std::string key)
{
	return (cont->find(key)) ? "1" : "0";
}

std::string InputHandler::min(std::string key)
{
	if (has_order())
	{
		std::string m = cont->min();
		return (m.size() > 0) ? m : " ";
	}
	return " ";
}

std::string InputHandler::max(std::string key)
{
	if (has_order())
	{
		std::string m = cont->max();
		return (m.size() > 0) ? m : " ";
	}
	return " ";
}

std::string InputHandler::succ(std::string key)
{
	if (has_order())
	{
		std::string s = cont->succ(key, false);
		return (s.size() > 0) ? s : " ";
	}
	return " ";
}

std::string InputHandler::inorder(std::string key)
{
	if (has_order())
	{
		std::vector<std::string> sorted = cont->inorder();
		std::stringstream ss;

		auto i = sorted.begin();
		for ( ; i != sorted.end(); i++)
		{
			ss << *i << " ";
		}

		return ss.str();
	}
	else
	{
		return " ";
	}
}

std::string InputHandler::load(std::string key)
{
	std::ifstream input;
	input.open(key);

	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			func_map["insert"](word);
		}

		input.close();
		return "";
	}

	std::stringstream ss;
	ss << "Unable to open " << key << "!";
	return ss.str();
}

std::string InputHandler::stats()
{
	std::stringstream ss;

	ss << "Total time: ";
	ss << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
	ss << "ns\n";

	for (auto i = func_count.begin(); i != func_count.end(); i++)
	{
		ss << i->first << ": " << i->second;

		if (timed)
		{
			ss << " [Time: " << func_time[i->first] << "ns]";
		}

		ss << "\n";
	}

	ss << "Maximum size: " << max_elements << "\n";
	ss << "Final size: " << cont->size() << "\n";

	return ss.str();
}
