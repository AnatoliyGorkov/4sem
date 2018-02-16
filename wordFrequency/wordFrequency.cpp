#include <iostream>
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
	string punct = "!@#$%^&*()_-+=\"'|?/\\<>,.;:[]{}“”—…’‘";
	result.resize(word.size());
	std::transform(word.begin(), word.end(), result.begin(), ::tolower);
	long start = 0, end = 0, len = result.length();
	for (start = 0; start < len && punct.find(result[start]) != string::npos; start++);

	for (end = len - 1; end >= 0 && punct.find(result[end]) != string::npos; end--);

	if (end < start)
		result = "";
	else
		result = result.substr(start, end - start + 1);
	return result;
}

bool compare(const Stat& s1, const Stat& s2)
{
	return s2.count < s1.count ? true : false;
}

int main()
{
	string name;
	std::map<string, size_t> dict;

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
		std::cout << "Output file cannot be opened. Input another one" << std::endl;
		std::cin >> name;
		output = std::ofstream(name);
	}

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
	for (auto it : dict)
	{
		stat.word = it.first;
		stat.count = it.second;
		vector.push_back(stat);
	}

	std::sort(vector.begin(), vector.end(), compare);

	for (auto stat : vector)
		output << stat.count << '\t' << stat.word << std::endl;
	output.close();
    return 0;
}

