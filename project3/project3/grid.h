#ifndef GRID_CLASS
#define GRID_CLASS

#include <iostream>
#include <fstream>
#include <string>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

//grid class to handle the grid of scrambled letters.
class grid
{
public:
	grid();
	grid(string fileName);
	void importGrid();
	void scanHori();
	void scanVert();
	void scanDiag();

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
void dictionary::scanHori()
{
	string testStr = "";
	int tempCount;

	// Scan the grid from left-to-right.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width;i++)
		{
			testStr = grid.getChar(i, j);
			tempCount = i;

			while (testStr.length() != maxWordSize)
			{
				// Increment the number as long as it isn't the end of the grid.
				if (tempCount != width - 1)
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
					testStr += grid.getChar(tempCount, j);
				}
				else
				{
					// Check to see if the word is in the dictionary.
					checkWord(testStr);
					testStr += grid.getChar(tempCount, j);
				}
			}
			checkWord(testStr);
		}
	}

	// Scan the grid from right-to-left
	for (int j = 0; j < height; j++)  //j is height
	{
		for (int i = 0; i < width;i++) //i is width
		{
			testStr = gird.getChar(i, j);
			tempCount = i;

			while (testStr.length() != maxWordSize)
			{
				if (tempCount != 0)
				{
					tempCount--;
				}
				else
				{
					tempCount = width - 1;
				}

				if (testStr.length() < 5)
				{
					testStr += grid.getChar(tempCount, j);
				}
				else
				{
					checkWord(testStr);
					testStr += grid.getChar(tempCount, j);
				}
			}
			checkWord(testStr);
		}
	}

	return;
}

// scanVert() will scan the list from up-to-down and down-to-up.
void dictionary::scanVert()
{
	string testStr = "";
	int tempCount;

	// Up-to-down
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width;i++)
		{
			testStr = grid.getChar(i, j);
			tempCount = j;

			while (testStr.length() != maxWordSize)
			{
				if (tempCount != height - 1)
				{
					tempCount++;
				}
				else
				{
					tempCount = 0;
				}

				if (testStr.length() < 5)
				{
					testStr += grid.getChar(i, tempCount);
				}
				else
				{
					checkWord(testStr);
					testStr += grid.getChar(i, tempCount);
				}
			}
			checkWord(testStr);
		}
	}

	// Down-to-up
	for (int j = 0; j < height; j++)  
	{
		for (int i = 0; i < width;i++) 
		{
			testStr = grid.getChar(i, j);
			tempCount = j;

			while (testStr.length() != maxWordSize)
			{
				if (tempCount != 0)
				{
					tempCount--;
				}
				else
				{
					tempCount = height - 1;
				}

				if (testStr.length() < 5)
				{
					testStr += grid.getChar(i, tempCount);
				}
				else
				{
					checkWord(testStr);
					testStr += grid.getChar(i, tempCount);
				}
			}
			checkWord(testStr);
		}
	}

	return;
}

// scanDiag() will scan all possible diagonals.
void dictionary::scanDiag()
{
	int tempI, tempJ;
	string testStr = "";

	// Scan in the south-east diagonal direction.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width;i++)
		{
			testStr = ourWords[i][j];
			tempI = i;
			tempJ = j;
			while (testStr.length() != maxWordSize)
			{
				// Check for all position possibilities and increment accordingly.
				if (tempI != (width - 1) && tempJ != (height - 1))
				{
					tempI++;
					tempJ++;
				}
				// If at the end of the row
				else if (tempI == (width - 1))
				{
					tempI = height - tempJ - 1;
					tempJ = 0;
				}
				// If at the end of the column.
				else if (tempJ == (height - 1))
				{
					tempJ = width - tempI - 1;
					tempI = 0;
				}

				if (testStr.length() < 5)
				{
					testStr += ourWords[tempI][tempJ];
				}
				else
				{
					checkWord(testStr);
					testStr += ourWords[tempI][tempJ];
				}
			}
			checkWord(testStr);
		}
	}

	// Scans for words in the north-east direction.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width;i++) 
		{
			testStr = ourWords[i][j];
			tempI = i;
			tempJ = j;
			while (testStr.length() != maxWordSize)
			{
				if (tempI != (width - 1) && tempJ != 0)
				{
					tempI++;
					tempJ--;
				}
				else if (tempI == (width - 1))
				{
					tempI = tempJ;
					tempJ = height - 1;
				}
				else if (tempJ == 0)
				{
					tempJ = tempI;
					tempI = 0;
				}

				if (testStr.length() < 5)
				{
					testStr += ourWords[tempI][tempJ];
				}
				else
				{
					checkWord(testStr);
					testStr += ourWords[tempI][tempJ];
				}
			}
			checkWord(testStr);
		}
	}

	// Scans for words in the north-west direction.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width;i++)
		{
			testStr = ourWords[i][j];
			tempI = i;
			tempJ = j;
			while (testStr.length() != maxWordSize)
			{
				if (tempI != 0 && tempJ != 0)
				{
					tempI--;
					tempJ--;
				}
				else if (tempI == 0)
				{
					tempI = width - tempJ - 1;
					tempJ = height - 1;
				}
				else if (tempJ == 0)
				{
					tempJ = width - tempI - 1;
					tempI = width - 1;
				}

				if (testStr.length() < 5)
				{
					testStr += ourWords[tempI][tempJ];
				}
				else
				{
					checkWord(testStr);
					testStr += ourWords[tempI][tempJ];
				}
			}
			checkWord(testStr);
		}
	}

	// Scans for words in the south-west direction.
	for (int j = 0; j < height; j++) 
	{
		for (int i = 0; i < width;i++)
		{
			testStr = ourWords[i][j];
			tempI = i;
			tempJ = j;
			while (testStr.length() != maxWordSize)
			{
				if (tempI != 0 && tempJ != (height - 1))
				{
					tempI--;
					tempJ++;
				}
				else if (tempI == 0)
				{
					tempI = tempJ;
					tempJ = 0;
				}
				else if (tempJ == height - 1)
				{
					tempJ = tempI;
					tempI = width - 1;
				}

				if (testStr.length() < 5)
				{
					testStr += ourWords[tempI][tempJ];
				}
				else
				{
					checkWord(testStr);
					testStr += ourWords[tempI][tempJ];
				}
			}
			checkWord(testStr);
		}
	}
}

#endif // GRID_CLASS
