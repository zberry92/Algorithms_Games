/*
 * Zachary Berry and Patrick Willett (berwil)
 * Project 3-a
 * This project will prompt the user to input a file containing a a scrambled word grid. It will then search
 * the grid for words of 5 characters or more in all directions. It will use a brute force method of finding the 
 * numbers.
 */

#include "dictionary.h"

using namespace std;

// Prototypes
void testSearch(string fileName);
void findMatches(dictionary &wordList, grid &wordGrid);

// testSearch() will initialize our grid and dictionary objects and import the grid and dictionary files accordingly.
// It will then begin the search through the grid.
void testSearch(string fileName)
{
	grid ourGrid(fileName);
	dictionary ourWords;

	ourGrid.importGrid();
	ourWords.importWords();

	findMatches(ourWords, ourGrid);
	
	return;
}

// findMatches() will search through the grid in every direction and oprint the found words.
void findMatches(dictionary &wordList, grid &wordGrid)
{
	// Bring the grid object into the dictionary object. 
	wordList.setValues(wordGrid);
	cout <<"Looking for words. This may take a while..." <<endl;
	cout <<"Found Words:" <<endl;

	cout <<"Searching Horizontally:" <<endl;
	wordList.scanHori();
	cout <<endl <<"Searching Vertically:" <<endl;
	wordList.scanVert();
	cout <<endl <<"Searching Diagonally:" <<endl;
	wordList.scanDiag();

	cout <<"All words have been found!" <<endl;

	return;
}

int main()
{
	string usrValue;

	cout <<"Welcome to the Word Search Solver! Please enter the name of your scrambled grid and we will start solving!"
		 <<endl <<"Grid name: ";
	cin >> usrValue;
	
	try
	{
		// Begin the search.
		testSearch(usrValue);
	}

	// Catch any errors that may be thrown.
	catch (const fileOpenError& re)
	{
		cerr <<re.what() <<endl;
	}

	catch (const indexRangeError& re)
	{
		cerr <<re.what() <<endl;
	}

	system("pause");
	return 0;
}