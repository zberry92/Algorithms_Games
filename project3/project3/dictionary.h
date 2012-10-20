#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS

#include <vector>
#include "grid.h"

// Dictionary class to handle all word comparison work.
class dictionary{
public:
	dictionary();
	void importWords();
	void setValues(grid tempGrid);
	
	void checkWord(string str);

private:
	int width, height, maxWordLength;
	vector<string> words;
};

// Default constructor
dictionary::dictionary()
{
	width = 0;
	height = 0;
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

// setValues() takes values from the grid class and applies them to values in the dictionary class.
void dictionary::setValues(grid tempGrid)
{
	width = tempGrid.getWidth();
	height = tempGrid.getHeight();
}



// checkWord() verifies that the word is in the dictionary and prints the word if true.
void dictionary::checkWord(string str)
{	
	for (int i = 0; i < (int) words.size(); i++)
	{
		if (str == words[i])
		{
				cout <<str <<endl;
		}
	}
}

#endif // DICTIONARY_CLASS
