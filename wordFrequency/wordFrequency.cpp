﻿#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>

using std::string;

struct Stat
{
	string word;
	size_t count;
};

string prepare(const string& word)
{
	string result = "";
	// есть ф-и isalpha, ispunct и т.п. они вам не подойдут?
	string punct = "!@#$%^&*()_-+=\"'|?/\\<>,.;:[]{}“”—…’‘123456789";
	result.resize(word.size());
	std::transform(word.begin(), word.end(), result.begin(), ::tolower);
	long start = 0, end = 0, len = result.length();
	for (start = 0; start < len && punct.find(result[start]) != string::npos; start++);

	// http://www.cplusplus.com/reference/string/string/find_last_not_of/ 
	// http://www.cplusplus.com/reference/string/string/find_first_of/
	for (end = len - 1; end >= 0 && punct.find(result[end]) != string::npos; end--);

	if (end < start)
		result = "";
	else
		result = result.substr(start, end - start + 1);
	return result;
}

/*
лучше не использовать числа в названии переменных,
как вариант first, second или lhs, rhs
*/
bool compare(const Stat& s1, const Stat& s2)
{
	/*
	fixit: просто
	return s2.count < s1.count; 
	*/
	return s2.count < s1.count ? true : false;
}

int main()
{
	string name;
	std::map<string, size_t> dict;

	/*
	кажется, что если использовать do ... while, то можно не дублировать 2 строки кода
	... в следующем цикле та же история
	*/
	std::cout << "Input file name?" << std::endl;
	std::cin >> name;
	std::ifstream file(name);
	while (!file.is_open())
	{
		std::cout << "Input file cannot be opened. Input another one" << std::endl;
		std::cin >> name;
		file = std::ifstream(name);
	}

	std::cout << "Output file name?" << std::endl;
	std::cin >> name;
	std::ofstream output(name);
	while (!output.is_open())
	{
		std::cout << "Output file cannot be created. Input another one" << std::endl;
		std::cin >> name;
		output = std::ofstream(name);
	}
	int numberOfWords;
	std::cout << "Input the ammount of words to output" << std::endl;
	std::cin >> numberOfWords;
	string word;
	while (!file.eof())
	{
		file >> word;
		word = prepare(word);
		if (!word.empty())
			dict[word]++;
	}
	file.close();

	std::vector<Stat> vector;
	vector.reserve(dict.size());
	Stat stat;
	/*
	если написать const auto& it, то не будет производиться лишнее копирование (конструктор копирования) в 
	локальную переменную it
	*/
	for (auto it : dict)
	{
		stat.word = it.first;
		stat.count = it.second;
		vector.push_back(stat);
	}

	std::sort(vector.begin(), vector.end(), compare);
	/*
	int num = std::min(numberOfWords, vector.size());
	*/
	int num = (numberOfWords < vector.size()) ? numberOfWords : vector.size();
	for (int i = 0; i < num; i++)
		output << vector[i].count << '\t' << vector[i].word << std::endl;
	output.close();
    return 0;
}

