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
#include <cstdlib>

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

// Overloaded output operator for vector class.
template <typename T>
ostream &operator<<(ostream &oStr, vector<T> &v)
{
  for (int i = 1; i < v.size(); i++)
  {
    oStr <<v[i] <<" ";
  }
  
  oStr <<endl;
  return oStr;
}

// Board class to handle all operations regarding the Sudoku board.
class board
{
   public:
      board(int sqSize);
      void clear();
      void initialize(ifstream &fin);
      bool checkConflicts(int i, int j, int k, int val);
      void findConflicts();
      void setCell(int i, int j, char val);
      void clearCell(int i, int j);
      ValueType getCell(int, int);
      bool isBlank(int i, int j);
      void printBoard();
      void printConflicts();
      int squareNumber(int i, int j);
      bool isSolved();
      void clearConflicts();
      
   private:
      // The following matrices go from 1 to BoardSize in each
      // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
      matrix<ValueType> value;
      vector<vector<bool> > rowConf;
      vector<vector<bool> > colConf;
      vector<vector<bool> > squConf;

};

// Board Constructor
board::board(int sqSize)
     : value(BoardSize + 1, BoardSize + 1), 
       rowConf(10, vector<bool>(10, false)),
       colConf(10, vector<bool>(10, false)), 
       squConf(10, vector<bool>(10, false))
{
}

// Clear the board of all values.
void board::clear()
{
  for (int i = 1; i <= BoardSize; i++)
  {
    for (int j = 1; j <= BoardSize; j++)
    {
      value[i][j] = -1;
    }
  }	
}

// Read the board in from the input file.
void board::initialize(ifstream &fin)
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
            setCell(i, j, ch);   // Convert char to int
	 }
	 else
	 {
	   value[i][j] = -1;
	 }
      }
   }
}

// checkConflicts will see if the letter is allowed to be placed there.
bool board::checkConflicts(int val, int i, int j, int k)
{
  if (rowConf[i][val] || colConf[j][val] || squConf[k][val])
  {
    return false;
  }
  else
  {
    return true;
  }
}

// setCell will set the value of the cell and update conflicts.
void board::setCell(int i, int j, char val)
{
  int intVal;

  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
  {
    intVal = atoi(&val);
    value[i][j] = intVal;
    rowConf[i][intVal] = true;
    colConf[j][intVal] = true;
    squConf[squareNumber(i, j)][intVal] = true;
  }
  else
  {
    throw rangeError("bad value in setCell");
  }
}

void board::clearCell(int i, int j)
{
  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
  {
    value[i][j] = -1;
  }
  else
  {
    throw rangeError("bad value in setCell");
  }
}

// getCell() returns the value of a cell and throws an exception 
// if bad parameters.
ValueType board::getCell(int i, int j)
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

// isBlack() returns true if a certain cell is empty.
bool board::isBlank(int i, int j)
{
  if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
  {
    throw rangeError("bad value in isBlank");
  }

  if (value[i][j] == -1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// printBoard() prints the sudoku board
void board::printBoard()
{
   for (int i = 1; i <= BoardSize; i++)
   {
     if ((i-1) % SquareSize == 0)
     {
       cout <<" -";
       for (int j = 1; j <= BoardSize; j++)
       {
	 cout <<"---";
       }
       cout <<"-";
       cout <<endl;
     }

     for (int j = 1; j <= BoardSize; j++)
     {
       if ((j-1) % SquareSize == 0)
       {
	 cout << "|";
       }
       if (!isBlank(i,j))
       {
	 cout << " " << getCell(i,j) << " ";
       }
       else
       {
	 cout << "   ";
       }
     }
   
     cout << " -";
     for (int j = 1; j <= BoardSize; j++)
     {
       cout << "---";
     }

     cout << "-";
     cout << endl;
   }
}

void board::printConflicts()
{
  for (int i = 1; i <= BoardSize; i++)
  {
    cout <<"Row " <<i <<" Conflicts:" <<endl 
	 <<"Numbers: 1 2 3 4 5 6 7 8 9" <<endl
	 <<"Values:  ";
    cout <<rowConf[i] <<endl;

    cout <<"Column " <<i <<" Conflicts:" <<endl 
	 <<"Numbers: 1 2 3 4 5 6 7 8 9" <<endl
	 <<"Values:  ";
    cout <<colConf[i] <<endl;

    cout <<"Square " <<i<<" Conflicts:" <<endl 
	 <<"Numbers: 1 2 3 4 5 6 7 8 9" <<endl
	 <<"Values:  ";
    cout <<squConf[i] <<endl;
  }
}

// squareNumber() returns the square number of cell i,j 
// (counting from left to right, top to bottom.
int board::squareNumber(int i, int j)
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  
   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

// isSolved() will return true if the board is solved and false oetherwise.
bool board::isSolved()
{
  int tempInt;

  for (int i = 1; i <= BoardSize + 1; i++)
  {
    for (int j = 1; j <= BoardSize + 1; j++)
    {
      if (i % 3 == 0 && j % 3 == 0)
      {
	tempInt = squareNumber(i, j);
	for (int k = 1; k <= BoardSize; k++)
	{
	  if (!(squConf[tempInt][k]))
	  {
	    return false;
	  }
	}
      }

      if (!(rowConf[i][j]))
      {
	return false;
      }

      if (!(colConf[i][j]))
      {
	return false;
      }
    }
  }
  
  return true;
}

void board::clearConflicts()
{
  for (int i = 1; i <= BoardSize; i++)
  {
    for (int j = 1; j <= BoardSize; j++)
    {
      rowConf[i][j] = false;
      colConf[i][j] = false;
      squConf[i][j] = false;
    }
  }
}

#endif

