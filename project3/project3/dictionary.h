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
	int partition(vector<string> &ourWords, int left, int right);
	void quickSort(vector<string> &ourWords, int left, int right);
	int binSearch(const vector<string> &ourWords, int first, int last, string target);
	int getMaxWordSize() const;
	void checkWord(string str);
	void bubbleSort();

private:
	int maxWordLength, totalWords;
	vector<string> words;
};

// Default constructor
dictionary::dictionary()
{
	maxWordLength = 0;
	totalWords = 0;
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
		if (maxWordLength < (int) currWord.size()) // Find the maximum size of the words in our dictionary.
		{
			maxWordLength = currWord.size();
		}
		
		if (currWord.length() >= 5)
		{
			words.push_back(currWord);
			numWords++;
			if ((numWords % 5000) == 0)
			{
				std::cout <<numWords <<" words have been loaded!" <<endl;
			}
		}
	}

	totalWords = numWords;
	std::cout <<"Loading complete!" <<endl;

	std::cout <<"Sorting the words now..." <<endl;
	quickSort(words, 0, totalWords - 1); //sort our words.
	std::cout <<"List has now been sorted alphabetically!" <<endl;
	return;
}

// Partition function needed for quicksort algorithm
int dictionary::partition(vector<string> &ourWords, int left, int right)
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

// quickSort worked extremely well compared to our bubble sort alternative. Since the words are very unsorted, quickSort
// should be close to its average time of nlog(n). It would only reach the same time of n^2 if the list was mostly sorted.
void dictionary::quickSort(vector<string> &ourWords, int left, int right)
{
  int p;

  if (left < right)
  {
      p = partition(ourWords, left, right);
      quickSort(ourWords, left, p - 1);
      quickSort(ourWords, p + 1, right);
  }
}

int dictionary::binSearch(const vector<string> &ourWords, int first, int last, string target)
{
	int midPoint;
	string midStr;

	while (first <= last)
	{
		midPoint = (first + last) / 2;
		midStr = ourWords[midPoint];
		 
		if (target == midStr)
		{
			return midPoint;
		}
		else if (target.compare(midStr) < 0)
		{
			last = midPoint - 1;
		}
		else
		{
			first = midPoint + 1;
		}
	}

	return -1;
}



// setValues() takes values from the grid class and applies them to values in the dictionary class.
int dictionary::getMaxWordSize() const
{
	return maxWordLength;
}

// checkWord() verifies that the word is in the dictionary and prints the word if true.
void dictionary::checkWord(string str)
{	
	string  revStr;
	int match;

	match = binSearch(words, 0, totalWords - 1, str);
	if (match != -1)
	{
		cout <<str <<endl;
	}

	revStr = string(str.rbegin(), str.rend());
	match = binSearch(words, 0, totalWords - 1, revStr);
	if (match != -1)
	{
		cout <<revStr <<endl;
	}

	return;
}

/*
 * This function was found to be incredibly slow, especially compared to Quicksort. This is a
 * n^2 function, which makes it take much longer than the nlogn quicksort.
 * Therefore, it can be seen that this is an incredibly inneficcient function to use,
 * and shoudln't be used in the future.
 */
void dictionary::bubbleSort()
{
	int left = 0;
	int right = totalWords - 1;
    int j = 0;
    string s;

	bool flag = true;  //flag to say when the number has been swapped
    while (flag) 
	{
            flag = false;
            j++;

            for (int i = 0; i < right - left; i++) {
                  if (words[i] > words[i + 1]) 
				  {
                        s = words[i];  //temp copy swap
                        words[i] = words[i + 1]; //switch
                        words[i + 1] = s;
                        flag = true;  //set flag true
                  }
            }
      }


}

#endif // DICTIONARY_CLASS
