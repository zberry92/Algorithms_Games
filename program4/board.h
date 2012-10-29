/* 
 * Board class to handle all board operations.
 */
#ifndef BOARD_CLASS
#define BOARD_CLASS

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

/* Typedefs */
typedef int ValueType; // The type of the value in a cell

/* Global Variables */
const int Blank = -1;  // Indicates that a cell is blank
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;
int numSolutions = 0;

// Board class to handle all operations regarding the Sudoku board.
class board
{
   public:
      board(int sqSize);
      void clear();
      void initialize(ifstream &fin);
      void setCell(int i, int j,
      ValueType getCell(int, int);
      void print();
      bool isBlank(int i, int j);
      
      int squareNumber(int i, int j);
      
   private:
      // The following matrices go from 1 to BoardSize in each
      // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
      matrix<ValueType> value;
};

// Board Constructor
board::board(int sqSize)
   : value(BoardSize + 1, BoardSize + 1)
{
}

// Clear the board of all values.
void board::clear()
{
  for (int i = 1; i <= BoardSize; i++)
  {
    for (int j = 1; j <= BoardSize; j++)
    {
      setCell(i, j, '0');
    }
  }	
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
	 fin >> ch;

         // If the read char is not Blank
	 if (ch != '.')
	 {
            setCell(i, j, ch-'0');   // Convert char to int
	 }
      }
   }
}

void board::setCell(int i, int j, char val)
{
  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
  {
    value[i][j] = atoi(val);
  }
  else
  {
    throw rangeError("bad value in getCell");
  }
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
  {
    return value[i][j];
  }
  else
  {
    throw rangeError("bad value in getCell");
  }
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
  if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
  {
    throw rangeError("bad value in setCell");
  }
  if (value[i][j] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 1; j <= BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	 if ((j-1) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j) << " ";
	 else
	    cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

int board:: bosquareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

#endif

