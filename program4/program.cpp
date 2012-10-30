/*
 * Zachary Berry & Patrick Willet (berwil)
 * 10/28/12
 * Program 4a
 * This program will load in sudoku boards and print out the boards and their 
 * conflicts if any exist.
 */

#include "board.h"

using namespace std;

int main()
{
  ifstream fin;
  
  // Read the sample grid from the file.
  string fileName = "sudoku.txt";
  
  fin.open(fileName.c_str());
  
  if (fin == NULL)
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
      b1.printBoard();
      b1.printConflicts();
    }
  }
  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }

  fin.close();
  return 0;
}

