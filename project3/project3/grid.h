#ifndef GRID_CLASS
#define GRID_CLASS

#include "dictionary.h"

using namespace std;

//grid class to handle the grid of scrambled letters.
class grid
{
public:
	grid();
	grid(string fileName);
	void importGrid();
	void scanHori(dictionary &ourDict);
	void scanVert(dictionary &ourDict);
	void scanDiag(dictionary &ourDict);

private:
	int gridWidth, gridHeight;
	matrix<char> gridMatrix;
	const string gridName;
};

// Default constructor
grid::grid()
	:gridName("input15")
{
	gridWidth = 0;
	gridHeight = 0;
}

// Constructor with the user providing the filename.
grid::grid(string fileName)
	:gridName(fileName)
{
	gridWidth = 0;
	gridHeight = 0;
}

// importGrid() imports the grid from the file inputted by the user.
void grid::importGrid()
{
	ifstream inFile;
	char tile;

	inFile.open(gridName.c_str());
	// If the file could not be opened.
	if (inFile == NULL)
	{
		throw fileOpenError("grid::importGrid() could not open the grid.");
	}

	inFile >> gridHeight;
	inFile >> gridWidth;

	cout <<"The grid of " <<gridName.c_str() <<":" <<endl;
	cout <<"Height: " <<gridHeight <<" Width: " <<gridWidth<<endl;
	
	gridMatrix.resize(gridWidth, gridHeight);
	
	// Fill the matrix with the values from the grid.
	for (int j = 0; j < gridHeight; j++)  
	{
		for (int i = 0; i < gridWidth;i++)
		{
			if (inFile >> tile)
			{
				gridMatrix[i][j] = tile;
				cout <<gridMatrix[i][j] <<" ";
			}
		}
		cout<<endl;
	}

	return;
}

// scanHori() will scan for all horizontal words from left-to-right and right-to-left
void grid::scanHori(dictionary &ourDict)
{
	string testStr = "";
	int tempCount;
	int wordSize = ourDict.getMaxWordSize();

	// Scan the grid from left-to-right.
	for (int j = 0; j < gridHeight; j++)
	{
		for (int i = 0; i < gridWidth; i++)
		{
			testStr = gridMatrix[i][j];
			tempCount = i;

			// Increment the number as long as it isn't the end of the grid.
			if (tempCount != (gridWidth - 1))
			{
				tempCount++;
			}
			else
			{
				tempCount = 0;
			}

			testStr += gridMatrix[tempCount][j];

			while (tempCount != i) // While we have not looped comletely around.
			{
				if ((int) testStr.length() > wordSize)
				{
					break;
				}

				// Increment the number as long as it isn't the end of the grid.
				if (tempCount != (gridWidth - 1))
				{
					tempCount++;
				}
				else
				{
					tempCount = 0;
				}
				
				// Be sure the word is at least five characters long.
				if (testStr.length() < 5)
				{
					testStr += gridMatrix[tempCount][j];
				}
				else
				{
					// Check to see if the word is in the dictionary.
					ourDict.checkWord(testStr);
					testStr += gridMatrix[tempCount][j];
				}
			}
		}
	}

	return;
}

// scanVert() will scan the list from up-to-down and down-to-up.
void grid::scanVert(dictionary &ourDict)
{
	string testStr = "";
	int tempCount;
	int wordSize = ourDict.getMaxWordSize();

	// Scan the grid from left-to-right.
	for (int j = 0; j < gridHeight; j++)
	{
		for (int i = 0; i < gridWidth;i++)
		{
			testStr = gridMatrix[i][j];
			tempCount = j;

			// Increment the number as long as it isn't the end of the grid.
			if (tempCount != (gridHeight - 1))
			{
				tempCount++;
			}
			else
			{
				tempCount = 0;
			}

			testStr += gridMatrix[i][tempCount];

			while (tempCount != j) 
			{
				if ((int) testStr.length() > (wordSize))
				{
					break;
				}

				// Increment the number as long as it isn't the end of the grid.
				if (tempCount != (gridWidth - 1))
				{
					tempCount++;
				}
				else
				{
					tempCount = 0;
				}
				
				//Be sure the word is at least five characters long.
				if (testStr.length() < 5)
				{
					testStr += gridMatrix[i][tempCount];
				}
				else
				{
					// Check to see if the word is in the dictionary.
					ourDict.checkWord(testStr);
					testStr += gridMatrix[tempCount][j];
				}
			}
		}
	}

	return;
}

// scanDiag() will scan all possible diagonals.
void grid::scanDiag(dictionary &ourDict)
{
	int tempI, tempJ;
	string testStr = "";
	int wordSize = ourDict.getMaxWordSize();

	// Scan in the south-east, north-west diagonal directions.
	for (int j = 0; j < gridHeight; j++)
	{
		for (int i = 0; i < gridWidth;i++)
		{
			testStr = gridMatrix[i][j];
			tempI = i;
			tempJ = j;

			if (tempI != (gridWidth - 1) && tempJ != (gridHeight - 1))
			{
				tempI++;
				tempJ++;
			}
			else if (tempI == (gridWidth - 1) && tempJ == (gridHeight - 1))
			{
				tempI = 0;
				tempJ = 0;
			}
			else if (tempI == (gridWidth - 1))
			{
				tempI = 0;
				tempJ++;
			}
			else if (tempJ == (gridHeight - 1))
			{
				tempJ = 0;
				tempI++;
			}

			testStr += gridMatrix[tempI][tempJ];

			while (tempI != i && tempJ != j) 
			{
				if ((int) testStr.length() > wordSize)
				{
					break;
				}

				// Increment the number as long as it isn't the end of the grid.
				if (tempI != (gridWidth - 1) && tempJ != (gridHeight - 1))
				{
					tempI++;
					tempJ++;
				}
				else if (tempI == (gridWidth - 1) && tempJ == (gridHeight - 1))
				{
					tempI = 0;
					tempJ = 0;
				}
				else if (tempI == (gridWidth - 1))
				{
					tempI = 0;
					tempJ++;
				}
				else if (tempJ == (gridHeight - 1))
				{
					tempJ = 0;
					tempI++;
				}

				//Be sure the word is at least five characters long.
				if (testStr.length() < 5)
				{
					testStr += gridMatrix[tempI][tempJ];
				}
				else
				{
					// Check to see if the word is in the dictionary.
					ourDict.checkWord(testStr);
					testStr += gridMatrix[tempI][tempJ];
				}
			}	
		}
	}

	// Scans for words in the north-east direction.
	for (int j = 0; j < gridHeight; j++)
	{
		for (int i = 0; i < gridWidth;i++)
		{
			testStr = gridMatrix[i][j];
			tempI = i;
			tempJ = j;

			if (tempI != (gridWidth - 1) && tempJ != 0)
			{
				tempI++;
				tempJ--;
			}
			else if (tempI == (gridWidth - 1) && tempJ == 0)
			{
				tempI = 0;
				tempJ = gridHeight - 1;
			}
			else if (tempI == (gridWidth - 1))
			{
				tempI = 0;
				tempJ--;
			}
			else if (tempJ == 0)
			{
				tempJ = 0;
				tempI++;
			}

			testStr += gridMatrix[tempI][tempJ];

			while (tempI != i && tempJ != j) 
			{
				if (testStr.length() != wordSize)
				{
					break;
				}

				// Increment the number as long as it isn't the end of the grid.
				if (tempI != (gridWidth - 1) && tempJ != 0)
				{
					tempI++;
					tempJ--;
				}
				else if (tempI == (gridWidth - 1) && tempJ == 0)
				{
					tempI = 0;
					tempJ = (gridHeight - 1);
				}
				else if (tempJ == 0)
				{
					tempI++;
					tempJ = (gridHeight - 1);
				}
				else if (tempI == (gridWidth - 1))
				{
					tempI = 0;
					tempJ--;
				}

				//Be sure the word is at least five characters long.
				if (testStr.length() < 5)
				{
					testStr += gridMatrix[tempI][tempJ];
				}
				else
				{
					// Check to see if the word is in the dictionary.
					ourDict.checkWord(testStr);
					testStr += gridMatrix[tempI][tempJ];
				}
			}	
		}
	}

	return;
}

#endif // GRID_CLASS
