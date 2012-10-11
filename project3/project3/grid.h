#ifndef GRID_CLASS
#define GRID_CLASS

#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

class grid
{
public:
	void importGrid(string fileName);

private:
	int width, height;
	matrix<int> gridMatrix;
};

void grid::importGrid(string fileName)
{
	
	ifstream inFile;
	char s;

	inFile.open(fileName.c_str());
	inFile >> height;
	inFile >> width;
	cout<<"Height: "<<height<<" Width: "<<width<<endl;
	
	gridMatrix.resize(width, height);
	
	for(int j = 0; j < height; j++)  //j is height
	{
		for(int i = 0; i < width;i++) //i is width
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