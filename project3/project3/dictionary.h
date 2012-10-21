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
	int partition(vector<string> ourWords, int left, int right);
	void quickSort(vector<string> ourWords, int left, int right);
	int binSearch(const vector<string> ourWords, int first, int last, string target, int compFlag);
	int getMaxWordSize() const;
	bool verifyWord(string str);
	void checkWord(string str);

private:
	int maxWordLength, totalWords, fFlag, rFlag;
	vector<string> words;
};

// Default constructor
dictionary::dictionary()
{
	maxWordLength = 0;
	totalWords = 0;
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
		if (maxWordLength < (int) currWord.size())
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

	totalWords = numWords;
	std::cout <<"Loading complete!" <<endl;

	std::cout <<"Sorting the words now..." <<endl;
	quickSort(words, 0, totalWords - 1);
	std::cout <<"List has now been sorted alphabetically!" <<endl;
	return;
}

int dictionary::partition(vector<string> ourWords, int left, int right)
{
  int position;
  string str;

  str = ourWords[left];
  position = left;
  
  for (int i = position + 1; i <= right; i++)
  {
	if (ourWords[i].compare(str) < 0)
	{
	  swap(ourWords[position + 1], ourWords[i]);
	  swap(ourWords[position], ourWords[position + 1]);
	  position++;
	}
  }

  return position;
}

void dictionary::quickSort(vector<string> ourWords, int left, int right)
{
  int p;

  if (left < right)
  {
      p = partition(ourWords, left, right);
      quickSort(ourWords, left, p - 1);
      quickSort(ourWords, p + 1, right);
  }
}

int dictionary::binSearch(const vector<string> ourWords, int first, int last, string target, int compFlag)
{
	int midPoint;
	string midStr;

	while (first < last)
	{
		midPoint = (first + last) / 2;
		midStr = ourWords[midPoint];
		if (compFlag)
		{
		  if (midStr.compare(0, 5, target) == 0)
		    {
		      return 1;
		    }
		}
		 
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

        if (binSearch(words, 0, totalWords, str, 1) == 1)
	{
	       fFlag = 1;
	}

	revStr = string(str.rbegin(), str.rend());
	if (binSearch(words, 0, totalWords, revStr, 1) == 1)
	{
	       rFlag = 1;
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
	int match;

	if (fFlag == 1)
	{
	        match = binSearch(words, 0, totalWords, str, 0);
	        if (match != -1)
	        {
		                       cout <<str <<endl;
	        }
	}

	if (rFlag == 1)
	{
		revStr = string(str.rbegin(), str.rend());
	        match = binSearch(words, 0, totalWords, revStr, 0);
	        if (match != -1)
	        {
		                       cout <<revStr <<endl;
	        }
	}

	return;
}

#endif // DICTIONARY_CLASS
