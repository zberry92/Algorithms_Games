#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "d_matrix.h"
#include "d_except.h"

// Dictionary class to handle all word comparison work.
class dictionary{
public:
	dictionary();
	void importWords();
	int binSearch(const vector<string>ourWords, int first, int last, string target);
	int getMaxWordSize() const;
	bool verifyWord(string str);
	void checkWord(string str);

private:
	int maxWordLength, fFlag, rFlag;
	vector<string> words;
};

// Default constructor
dictionary::dictionary()
{
	maxWordLength = 0;
	fFlag = 0;
	rFlag = 0;
}

// importWords() imports all the words from the the dictionary file.
void dictionary::importWords()
{
	ifstream inFile;
	string currWord;
	int numWords = 0;

	inFile.open("dictionary");
	// If the file isn't open.
	if (!inFile) 
	{
		throw fileOpenError("dictionary::importWords() could not open dictionary file.");
	}

	std::cout <<endl <<"Loading words..." <<endl;

	while (inFile >> currWord)
	{
		if (maxWordLength < currWord.size())
		{
			maxWordLength = currWord.size();
		}

		words.push_back(currWord);
		numWords++;
		if ((numWords % 5000) == 0)
		{
			std::cout <<numWords <<" words have been loaded!" <<endl;
		}
	}

	std::cout <<"Loading complete!" <<endl;
	return;
}

int binSearch(const vector<string>ourWords, int first, int last, string target)
{
	int midPoint;
	string midStr;

	while (first < last)
	{
		midPoint = (first + last) / 2;
		midStr = ourWords[midPoint];

		if (target == midStr)
		{
			return midPoint;
		}
		else if (target.compare(midStr) < 0)
		{
			last = midPoint;
		}
		else
		{
			first = midPoint;
		}
	}

	return -1;
}



// setValues() takes values from the grid class and applies them to values in the dictionary class.
int dictionary::getMaxWordSize() const
{
	return maxWordLength;
}

bool dictionary::verifyWord(string str)
{
	string revStr;

	for (int i = 0; i < (int) words.size(); i++)
	{
		if (words[i].compare(0, 5, str) == 0)
		{
				fFlag = 1;
		}
	}

	revStr = string(str.rbegin(), str.rend());
	for (int i = 0; i < (int) words.size(); i++)
	{
		if (words[i].compare(0, 5, revStr) == 0)
		{
				rFlag = 1;
		}
	}

	if (fFlag == 0 && rFlag == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// checkWord() verifies that the word is in the dictionary and prints the word if true.
void dictionary::checkWord(string str)
{	
	string  revStr;

	if (fFlag == 1)
	{
		for (int i = 0; i < (int) words.size(); i++)
		{
			if (str == words[i])
			{
					cout <<str <<endl;
			}
		}
	}

	if (rFlag == 1)
	{
		revStr = string(str.rbegin(), str.rend());
		for (int i = 0; i < (int) words.size(); i++)
		{
			if (revStr == words[i])
			{
					cout <<revStr <<endl;
			}
		}
	}

	return;
}

#endif // DICTIONARY_CLASS
