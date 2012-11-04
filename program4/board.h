/* 
 * Board class to handle all board operations.
 */
#ifndef BOARD_CLASS
#define BOARD_CLASS

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <cstdlib>
#include "d_matrix.h"
#include "d_except.h"

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

// Overloaded output operator to print the conflict vectors.
template <typename T>
ostream &operator<<(ostream &oStr, vector<T> &v)
{
  for (int i = 1; i < v.size(); i++)
  {
    if (v[i])
    {
      oStr <<"T ";
    }
    else
    {
      oStr <<"F ";
    }
  }
  
  oStr <<endl;
  return oStr;
}

// Board class to handle all operations regarding the Sudoku board.
class board
{
   public:
      board();
      void clearBoard();
      void initialize(ifstream &fin);
      bool checkConflicts(int i, int j, int k, int val);
      bool setCell(int i, int j, char val);
      void clearCell(int i, int j);
      ValueType getCell(int i, int j);
      bool isBlank(int i, int j);
      void printBoard();
      void printConflicts();
      int squareNumber(int i, int j);
      bool isSolved();
      void clearConflicts();
      bool findMin(int i, int j, int maxI, int maxJ, int &minI, int &minJ);
      bool solveBoard(int i, int k, int count);
      
   private:
      // The following matrices go from 1 to BoardSize in each
      // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
      matrix<ValueType> value;
      vector<vector<bool> > rowConf;
      vector<vector<bool> > colConf;
      vector<vector<bool> > squConf;
};

// Board Constructor
board::board()
     : value(BoardSize + 1, BoardSize + 1), 
       rowConf(10, vector<bool>(10, false)),
       colConf(10, vector<bool>(10, false)), 
       squConf(10, vector<bool>(10, false))
{
}

// Clear the board of all values.
void board::clearBoard()
{
  for (int i = 1; i <= BoardSize; i++)
  {
    for (int j = 1; j <= BoardSize; j++)
    {
      value[i][j] = -1;
    }
  }

  clearConflicts();
}

// Read the board in from the input file.
void board::initialize(ifstream &fin)
{
   char ch;

   clearBoard();
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
  if (i < 1 && i > BoardSize && j < 1 && j > BoardSize &&
      k < 1 && k > BoardSize && val < 1 && val > BoardSize)
  {
    throw rangeError("bad value in checkConflicts()");
  }

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
bool board::setCell(int i, int j, char val)
{
  int intVal;

  intVal = atoi(&val);

  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize &&
      intVal >= 1 && intVal <= BoardSize)
  {
    if (!(checkConflicts(intVal, i, j, squareNumber(i, j))))
    {
	return false;
    }

    value[i][j] = intVal;
    
    // Set flags of the conflicts
    rowConf[i][intVal] = true;
    colConf[j][intVal] = true;
    squConf[squareNumber(i, j)][intVal] = true;

    return true;
  }
  else
  {
    throw rangeError("bad value in setCell");
  }
}

// clearCell() will clear the value of the cell and update conflicts.
void board::clearCell(int i, int j)
{
  int intVal;

  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
  {
    if (value[i][j] != -1)
    {
      intVal = value[i][j];
      rowConf[i][intVal] = false;
      colConf[j][intVal] = false;
      squConf[squareNumber(i, j)][intVal] = false;
      value[i][j] = -1;
    }
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
  for (int i = 1; i <= 2; i++)
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

// clearConflicts() will reset all of the conflict vectors to false.
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

bool board::solveBoard(int i, int j, int count)
{

  if (j > 9)
  {
    j = 1;
    i++;
  
    if (i > 3)
      {
	cout <<"Pause";
      }

    printBoard();
    if (isSolved())
    {
      printBoard();
      cout <<"The Board has been solved!" <<endl
           <<" The number of recursive calls was: " <<count <<endl;
      return true;
    }
  }

  if (isBlank(i, j))
  {
    for (int n = 1; n < 10; n++)
    {
      if (setCell(i, j, (char)n + '0'))
      {
	printBoard();
	printConflicts();
	cout<<endl <<endl;
	if (solveBoard(i, j + 1, count + 1))
	{
	  return true;
	}
      }
    }
  }
  else
  {
    return (solveBoard(i, j + 1, count + 1));
  }

  clearCell(i, j);
  cout<< rowConf[i] <<endl <<colConf[j] <<endl;
  return false;
}

#endif

