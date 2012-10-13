#ifndef GRID_CLASS
#define GRID_CLASS

#include <iostream>
#include <fstream>
#include <string>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

class grid
{
public:
	grid();
	grid(string fileName);
	void importGrid(string fileName);

private:
	int gridWidth, gridHeight;
	const string gridName;
	matrix<int> gridMatrix;
};

grid::grid()
	:gridName("input15")
{
	gridWidth = 0;
	gridHeight = 0;
}

grid::grid(string fileName)
	:gridName(fileName)
{
	gridWidth = 0;
	gridHeight = 0;
}

// Ryanor Kevin 115

void grid::importGrid(string fileName)
{
	ifstream inFile;
	char s;

	inFile.open(fileName.c_str());
	inFile >> gridHeight;
	inFile >> gridWidth;
	cout<<"Height: "<<gridHeight<<" Width: "<<gridWidth<<endl;
	
	gridMatrix.resize(gridWidth, gridHeight);
	
	for(int j = 0; j < gridHeight; j++)  //j is height
	{
		for(int i = 0; i < gridWidth;i++) //i is width
		{
			if (!(inFile >> s))  //error checking, means has reached the end of the file before supposed to
			{
				cout<<"Problem importing file. Unable to read any more data from file"<<endl;
			}
			gridMatrix[i][j] = s;
			cout<< gridMatrix[i][j] <<" ";
		}
		cout<<endl;

	}




}

#endif // GRID_CLASS