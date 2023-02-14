#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define DICT_DELIM "###"
#define WORD_BREAK_DELIM "***"
#define NO_POSSIBLE_BREAK -1

using namespace std;

void get_word_breaks(string s, vector<string>& dictionary, vector<string>& word_breaks, string result = "")
{
	for (int i = 1; i <= s.size(); i++)
	{
		string prefix = s.substr(0, i);
		if (find(dictionary.begin(), dictionary.end(), prefix) != dictionary.end())
		{
			if (i == s.size())
			{
				result += prefix;
				word_breaks.push_back(result);
				return;
			}
			get_word_breaks(s.substr(i, s.size()), dictionary, word_breaks, result + prefix + " ");
		}
	}
}

vector<string> get_dictionary()
{
	vector<string> dictionary;
	string word;
	while (getline(cin, word) && word != DICT_DELIM) 
		dictionary.push_back(word);
	return dictionary;
}

vector<string> get_sentences()
{
	vector<string> sentences;
	string sentence;
	while (getline(cin, sentence))
	{
		sentences.push_back(sentence);
	}
	return sentences;
}

vector<vector<string>> get_all_word_breaks(vector<string> dictionary, vector<string> sentences)
{
	vector<vector<string>> all_word_breaks;
	for (string sentence : sentences)
	{
		vector<string> word_breaks;
		get_word_breaks(sentence, dictionary, word_breaks);
		all_word_breaks.push_back(word_breaks);
	}
	return all_word_breaks;
}

void print_word_breaks(vector<vector<string>> all_word_breaks)
{
	for (vector<string> word_breaks : all_word_breaks)
	{
		if (word_breaks.size() == 0)
			cout << NO_POSSIBLE_BREAK << endl;
		else
		{
			for (string word_break : word_breaks)
				cout << word_break << endl;
		}
		cout << WORD_BREAK_DELIM << endl;
	}
}

int main() {
	vector<string> dictionary = get_dictionary();
	vector<string> sentences = get_sentences();
	vector<vector<string>> all_word_breaks = get_all_word_breaks(dictionary, sentences);

	print_word_breaks(all_word_breaks);

	return 0;
}