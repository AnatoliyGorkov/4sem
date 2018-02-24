#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <cwctype>
#include <vector>
#include <clocale>

using std::string;
using std::wstring;

struct Stat
{
	wstring word;
	size_t count;
};

wstring prepare(const wstring& word)
{
	wstring result;
	result.resize(word.size());
	std::transform(word.begin(), word.end(), result.begin(), ::tolower);
	long start = 0, len = result.length(), end = len - 1;
	/*
		Непонятная штука в первой версии была создана, потому что
		isalpha не работал (вылезали ошибки)
		Debug Assertion Failed!

		Program: D:\Prog\4sem\wordFrequency\Debug\wordFrequency.exe
		File: minkernel\crts\ucrt\src\appcrt\convert\isctype.cpp
		Line: 36

		Expression: c >= -1 && c <= 255
		Поэтому пришлось переделывать на wstring
	*/
	while (start < len && !std::iswalpha(result[start]))
		start++;
	while (end >= 0 && !std::iswalpha(result[end]))
		end--;

	if (end < start)
		result = L"";
	else
		result = result.substr(start, end - start + 1);
	return result;
}

bool compare(const Stat& lhs, const Stat& rhs)
{
	return rhs.count < lhs.count;
}

int main()
{
	std::setlocale(LC_ALL, ".utf8");
	string name;
	std::map<wstring, size_t> dict;

	string message = "Input file name?";
	std::wifstream input;
	do
	{
		std::cout << message << std::endl;
		std::cin >> name;
		input = std::wifstream(name);
		message = "Input file cannot be opened. Input another one";
	} while (!input.is_open());

	message = "Output file name?";
	std::wofstream output;
	do
	{
		std::cout << message << std::endl;
		std::cin >> name;
		output = std::wofstream(name);
		message = "Output file cannot be created. Input another one";
	} while (!output.is_open());

	int numberOfWords;
	std::cout << "Input the ammount of words to output" << std::endl;
	std::cin >> numberOfWords;
	wstring word;
	while (!input.eof())
	{
		input >> word;
		word = prepare(word);
		if (!word.empty())
			dict[word]++;
	}
	input.close();

	std::vector<Stat> vector;
	vector.reserve(dict.size());
	Stat stat;
	for (auto& it : dict)
	{
		stat.word = it.first;
		stat.count = it.second;
		vector.push_back(stat);
	}

	std::sort(vector.begin(), vector.end(), compare);
	int num = std::min(numberOfWords, (int) vector.size());
	for (int i = 0; i < num; i++)
		output << vector[i].count << '\t' << vector[i].word << std::endl;
	output.close();
	return 0;
}
