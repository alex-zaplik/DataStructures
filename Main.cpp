#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "BST.h"
#include "RBT.h"
#include "HashTable.h"
#include "InputHandler.h"
#include "BloomFilter.h"

void print_usage()
{
	std::cerr << "Usage: --type [bst|rbt|hmap|bloom]" << std::endl;
}

Container* get_container(const char* arg)
{
	Container* cont = nullptr;

	std::string type(arg);
	if (type == "bst") cont = new BST;
	else if (type == "rbt") cont = new RBT;
	else if (type == "hmap") cont = new HashTable;
	else if (type == "bloom") cont = new BloomFilter;
	
	return cont;
}

void shuffle(std::string key, std::string out)
{
	std::ifstream input;
	std::vector<std::string> words;
	std::srand(unsigned(std::time(0)));

	input.open(key);
	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}

		input.close();

		std::random_shuffle(words.begin(), words.end());

		std::ofstream output;

		output.open(out);
		if (output.is_open())
		{
			for (auto i = words.begin(); i != words.end(); i++)
			{
				output << *i << "\n";
			}

			output.close();
		}
	}
}

void gen_test(int iters, std::string to_load, std::vector<std::string> commands)
{
	std::ofstream output;

	output.open("test.txt");
	if (output.is_open())
	{
		output << (iters * commands.size() + 1) << "\n";
		output << "load " << to_load << "\n";

		for (auto it = commands.begin(); it != commands.end(); it++)
		{
			for (int i = 0; i < iters; i++)
			{
				output << *it << "\n";
			}
		}
		
		output.close();
	}
}

void gen_random_test(int iters, std::string to_load, std::vector<std::string> commands)
{
	std::ifstream input;
	std::vector<std::string> words;
	std::srand(unsigned(std::time(0)));

	input.open(to_load);
	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}

		input.close();

		std::random_shuffle(words.begin(), words.end());

		std::ofstream output;

		output.open("test.txt");
		if (output.is_open())
		{
			output << (iters * commands.size() + 1) << "\n";
			output << "load " << to_load << "\n";

			for (auto it = commands.begin(); it != commands.end(); it++)
			{
				for (int i = 0; i < iters; i++)
				{
					output << *it  << " " << words[i] << "\n";
				}
			}

			output.close();
		}
	}
}

void gen_random_ins_del_test(int iters, std::string to_load)
{
	std::ifstream input;
	std::vector<std::string> words;
	std::srand(unsigned(std::time(0)));

	input.open(to_load);
	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}

		input.close();

		std::random_shuffle(words.begin(), words.end());

		std::ofstream output;

		output.open("test.txt");
		if (output.is_open())
		{
			output << (iters * 2 + 1) << "\n";
			output << "load " << to_load << "\n";

			for (int i = 0; i < iters; i++)
			{
				output << "delete " << words[i] << "\n";
				output << "insert " << words[i] << "\n";
			}

			output.close();
		}
	}
}

void gen_bloom_test()
{
	std::vector<std::string> words;
	std::srand(unsigned(std::time(0)));

	std::ifstream input;
	input.open("aspell_wordlist_two.txt");

	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}
		input.close();

		std::ofstream output;

		output.open("test.txt");
		if (output.is_open())
		{
			output << (words.size() + 1) << "\n";
			output << "load aspell_wordlist_one.txt\n";

			for (auto it = words.begin(); it != words.end(); it++)
			{
				output << "find " << *it << "\n";
			}

			output.close();
		}
	}
}

void gen_tests()
{
	std::vector<std::string> commands;
	commands.push_back("find");
	// commands.push_back("min");
	// commands.push_back("max");
	// commands.push_back("successor");
	// commands.push_back("inorder");


	// shuffle("aspell_wordlist.txt", "aspell_wordlist_shuffle.txt");
	gen_test(500, "aspell_wordlist.txt", commands);
	// gen_random_test(500, "aspell_wordlist_shuffle.txt", commands);
	// gen_random_ins_del_test(500, "aspell_wordlist_shuffle.txt");
}

void test_find_bloom()
{
	Container* cont;

	std::vector<std::string> words;
	unsigned int ones;

	std::ifstream input;
	input.open("aspell_wordlist_one.txt");

	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}
		input.close();

		for (int k = 0; k <= 16; k++)
		{
			std::cout << k << ": " << std::flush;

			if (k == 0)
			{
				std::cerr << " ;";
			}
			else
			{
				std::cerr << k << ";";
			}

			for (unsigned int m = (2 << 7); m <= (2 << 19); m <<= 1)
			{
				std::cout << m << " " << std::flush;

				if (k == 0)
				{
					std::cerr << m << ";";
				}
				else
				{
					cont = new BloomFilter(m, k);
					InputHandler ih(cont);
					ones = 0;

					ih.handle_line("load aspell_wordlist_two.txt");

					for (std::string word : words)
					{
						if (cont->find(word)) ones++;
					}

					std::cerr << ((1 - (double)ones / words.size()) * 100) << ";" << std::flush;

					delete cont;
				}
			}

			std::cout << std::endl;
			std::cerr << std::endl;
		}
	}
}

void test_find(Container* cont, InputHandler &ih, std::string key)
{
	std::ifstream input;
	std::vector<std::string> words;
	std::srand(unsigned(std::time(0)));

	input.open(key);
	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			words.push_back(word);
		}

		input.close();

		std::random_shuffle(words.begin(), words.end());

		std::stringstream ss;
		ss << "load " << key;
		ih.handle_line(ss.str());

		unsigned long max = 0;
		unsigned long min = std::numeric_limits<unsigned long>::max();
		unsigned long long avg = 0;

		for (std::string word : words)
		{
			unsigned long compares = cont->counted_find(word);
			max = std::max(compares, max);
			min = std::min(compares, min);
			avg += compares;
		}

		avg /= words.size();

		std::cerr << "Min: " << min << std::endl;
		std::cerr << "Max: " << max << std::endl;
		std::cerr << "Avg: " << avg << std::endl;
	}
}

void test_tree(Container* tree)
{
	std::vector<std::string> sorted, old_sorted;
	std::string min = tree->min();
	std::string max = tree->max();

	std::cout << "::" << min << ":: - ::" << max << "::\n" << std::endl;

	tree->ins("aaa");
	tree->ins("aba");
	tree->ins("abc");
	tree->ins("abc");
	tree->ins("ggg");
	tree->ins("hah");
	tree->ins("hhh");
	tree->ins("iii");
	tree->ins("lda");
	tree->ins("ttt");
	tree->ins("yup");
	tree->ins("zza");
	tree->ins("zzz");
	std::cout << tree->print() << std::endl;

	sorted = tree->inorder();
	old_sorted = sorted;
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting ttt" << std::endl;
	tree->del("ttt");

	sorted = tree->inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting abb" << std::endl;
	tree->del("abb");

	sorted = tree->inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << "\n" << std::endl;

	for (unsigned int i = 0; i < old_sorted.size(); i++)
		std::cout << old_sorted[i] << ": " << ((tree->find(old_sorted[i])) ? "Yes" : "No") << std::endl;

	std::cout << std::endl;
	std::cout << "abb: " << ((tree->find("abb")) ? "Yes" : "No") << std::endl;
	std::cout << std::endl;

	std::cout << "Deleting aaa" << std::endl;
	tree->del("aaa");
	std::cout << tree->print() << std::endl;

	sorted = tree->inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting hhh" << std::endl;
	tree->del("hhh");
	std::cout << tree->print() << std::endl;

	sorted = tree->inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::cout << "Deleting zzz" << std::endl;
	tree->del("zzz");
	std::cout << tree->print() << std::endl;

	sorted = tree->inorder();
	for (unsigned int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";

	std::cout << "\n" << tree->print() << "\n" << std::endl;

	for (unsigned int i = 0; i < old_sorted.size(); i++)
		std::cout << old_sorted[i] << ": " << ((tree->find(old_sorted[i])) ? "Yes" : "No") << std::endl;

	min = tree->min();
	max = tree->max();

	std::cout << "\n::" << min << ":: - ::" << max << "::\n" << std::endl;

	while (min != tree->null_type())
	{
		std::cout << min << std::endl;
		min = tree->succ(min, true);
	}
	std::cout << std::endl;

	while (max != tree->null_type())
	{
		std::cout << max << std::endl;
		max = tree->pred(max, true);
	}
}

void test_hash(Container* hash)
{
	hash->ins("aaa");
	hash->ins("aba");
	hash->ins("abc");
	hash->ins("abc");
	hash->ins("ggg");
	hash->ins("hah");
	hash->ins("hhh");
	hash->ins("iii");
	hash->ins("lda");
	hash->ins("ttt");
	std::cout << hash->print() << std::endl;

	hash->ins("yup");
	hash->ins("zza");
	hash->ins("zzz");
	std::cout << hash->print() << std::endl;

	hash->del("aaa");
	hash->del("abc");
	std::cout << hash->print() << std::endl;

	hash->del("ttt");
	std::cout << hash->print() << "\n" << std::endl;

	std::cout << "aaa" << ": " << ((hash->find("aaa")) ? "Yes" : "No") << std::endl;
	std::cout << "aba" << ": " << ((hash->find("aba")) ? "Yes" : "No") << std::endl;
	std::cout << "abc" << ": " << ((hash->find("abc")) ? "Yes" : "No") << std::endl;
	std::cout << "abc" << ": " << ((hash->find("abc")) ? "Yes" : "No") << std::endl;
	std::cout << "ggg" << ": " << ((hash->find("ggg")) ? "Yes" : "No") << std::endl;
	std::cout << "hah" << ": " << ((hash->find("hah")) ? "Yes" : "No") << std::endl;
	std::cout << "hhh" << ": " << ((hash->find("hhh")) ? "Yes" : "No") << std::endl;
	std::cout << "iii" << ": " << ((hash->find("iii")) ? "Yes" : "No") << std::endl;
	std::cout << "lda" << ": " << ((hash->find("lda")) ? "Yes" : "No") << std::endl;
	std::cout << "ttt" << ": " << ((hash->find("ttt")) ? "Yes" : "No") << std::endl;
	std::cout << "yup" << ": " << ((hash->find("yup")) ? "Yes" : "No") << std::endl;
	std::cout << "zza" << ": " << ((hash->find("zza")) ? "Yes" : "No") << std::endl;
	std::cout << "zzz" << ": " << ((hash->find("zzz")) ? "Yes" : "No") << std::endl;

	std::cout << std::endl;

	hash->del("abc");
	std::cout << hash->print() << "\n" << std::endl;

	std::cout << "aaa" << ": " << ((hash->find("aaa")) ? "Yes" : "No") << std::endl;
	std::cout << "aba" << ": " << ((hash->find("aba")) ? "Yes" : "No") << std::endl;
	std::cout << "abc" << ": " << ((hash->find("abc")) ? "Yes" : "No") << std::endl;
	std::cout << "abc" << ": " << ((hash->find("abc")) ? "Yes" : "No") << std::endl;
	std::cout << "ggg" << ": " << ((hash->find("ggg")) ? "Yes" : "No") << std::endl;
	std::cout << "hah" << ": " << ((hash->find("hah")) ? "Yes" : "No") << std::endl;
	std::cout << "hhh" << ": " << ((hash->find("hhh")) ? "Yes" : "No") << std::endl;
	std::cout << "iii" << ": " << ((hash->find("iii")) ? "Yes" : "No") << std::endl;
	std::cout << "lda" << ": " << ((hash->find("lda")) ? "Yes" : "No") << std::endl;
	std::cout << "ttt" << ": " << ((hash->find("ttt")) ? "Yes" : "No") << std::endl;
	std::cout << "yup" << ": " << ((hash->find("yup")) ? "Yes" : "No") << std::endl;
	std::cout << "zza" << ": " << ((hash->find("zza")) ? "Yes" : "No") << std::endl;
	std::cout << "zzz" << ": " << ((hash->find("zzz")) ? "Yes" : "No") << std::endl;
}

void test_bloom(int m, int k)
{
	BloomFilter b(m, k);

	b.ins("aaa");
	std::cout << b.print() << std::endl;
	b.ins("aba");
	std::cout << b.print() << std::endl;

	std::cout << std::endl;
	std::cout << "aaa: " << b.find("aaa") << std::endl;
	std::cout << "aba: " << b.find("aba") << std::endl;
	std::cout << "abc: " << b.find("abc") << std::endl;
	std::cout << "ggg: " << b.find("ggg") << std::endl;
	std::cout << "hah: " << b.find("hah") << std::endl;
	std::cout << "hhh: " << b.find("hhh") << std::endl;
	std::cout << "iii: " << b.find("iii") << std::endl;
	std::cout << "lda: " << b.find("lda") << std::endl;
	std::cout << "ttt: " << b.find("ttt") << std::endl;
	std::cout << "yup: " << b.find("yup") << std::endl;
	std::cout << "zza: " << b.find("zza") << std::endl;
	std::cout << "zzz: " << b.find("zzz") << std::endl;
	std::cout << std::endl;

	b.ins("abc");
	std::cout << b.print() << std::endl;
	b.ins("abc");
	std::cout << b.print() << std::endl;
	b.ins("ggg");
	std::cout << b.print() << std::endl;
	b.ins("hah");
	std::cout << b.print() << std::endl;

	std::cout << std::endl;
	std::cout << "aaa: " << b.find("aaa") << std::endl;
	std::cout << "aba: " << b.find("aba") << std::endl;
	std::cout << "abc: " << b.find("abc") << std::endl;
	std::cout << "ggg: " << b.find("ggg") << std::endl;
	std::cout << "hah: " << b.find("hah") << std::endl;
	std::cout << "hhh: " << b.find("hhh") << std::endl;
	std::cout << "iii: " << b.find("iii") << std::endl;
	std::cout << "lda: " << b.find("lda") << std::endl;
	std::cout << "ttt: " << b.find("ttt") << std::endl;
	std::cout << "yup: " << b.find("yup") << std::endl;
	std::cout << "zza: " << b.find("zza") << std::endl;
	std::cout << "zzz: " << b.find("zzz") << std::endl;
	std::cout << std::endl;

	b.ins("hhh");
	std::cout << b.print() << std::endl;
	b.ins("iii");
	std::cout << b.print() << std::endl;
	b.ins("lda");
	std::cout << b.print() << std::endl;
	b.ins("ttt");
	std::cout << b.print() << std::endl;
	b.ins("yup");
	std::cout << b.print() << std::endl;

	std::cout << std::endl;
	std::cout << "aaa: " << b.find("aaa") << std::endl;
	std::cout << "aba: " << b.find("aba") << std::endl;
	std::cout << "abc: " << b.find("abc") << std::endl;
	std::cout << "ggg: " << b.find("ggg") << std::endl;
	std::cout << "hah: " << b.find("hah") << std::endl;
	std::cout << "hhh: " << b.find("hhh") << std::endl;
	std::cout << "iii: " << b.find("iii") << std::endl;
	std::cout << "lda: " << b.find("lda") << std::endl;
	std::cout << "ttt: " << b.find("ttt") << std::endl;
	std::cout << "yup: " << b.find("yup") << std::endl;
	std::cout << "zza: " << b.find("zza") << std::endl;
	std::cout << "zzz: " << b.find("zzz") << std::endl;
	std::cout << std::endl;

	b.ins("zza");
	std::cout << b.print() << std::endl;
	b.ins("zzz");
	std::cout << b.print() << std::endl;

	std::cout << std::endl;
	std::cout << "aaa: " << b.find("aaa") << std::endl;
	std::cout << "aba: " << b.find("aba") << std::endl;
	std::cout << "abc: " << b.find("abc") << std::endl;
	std::cout << "ggg: " << b.find("ggg") << std::endl;
	std::cout << "hah: " << b.find("hah") << std::endl;
	std::cout << "hhh: " << b.find("hhh") << std::endl;
	std::cout << "iii: " << b.find("iii") << std::endl;
	std::cout << "lda: " << b.find("lda") << std::endl;
	std::cout << "ttt: " << b.find("ttt") << std::endl;
	std::cout << "yup: " << b.find("yup") << std::endl;
	std::cout << "zza: " << b.find("zza") << std::endl;
	std::cout << "zzz: " << b.find("zzz") << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		print_usage();
		return 1;
	}

	Container* cont = get_container(argv[2]);
	InputHandler ih(cont);

	int T;
	std::cin >> T;
	std::cin.get();

	std::string line;
	for (int i = 0; i < T; ++i)
	{
		std::getline(std::cin, line);
		line = ih.handle_line(line);

		if (line.size() != 0) std::cout << line << std::endl;
	}

	std::cerr << ih.stats() << std::endl;

	return 0;
}