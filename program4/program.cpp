/*
 * Zachary Berry & Patrick Willet (berwil)
 * 10/28/12
 * Program 4a
 * This program will load in sudoku boards and print out the boards and their 
 * conflicts if any exist.
 */

#include "board.h"

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   ostr << endl;
   return ostr;
}



int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
	 b1.initialize(fin);
	 b1.print();
	 b1.printConflicts();
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}

