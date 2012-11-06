/*
 * Zachary Berry & Patrick Willet (berwil)
 * 10/28/12
 * Program 4b
 * This program will solve the sudoku boards in the sudoku.txt file.
 */

#include "board.h"

using namespace std;

int main()
{
  ifstream fin;
  int count = 0, c2 = 0, totalRecursive = 0;
  string fileName = "sudoku.txt";
  
  // Open the sudoku file
  fin.open(fileName.c_str());
  if (fin == NULL)
  {
    cerr << "Cannot open " << fileName << endl;
    exit(1);
  }
  
  try
  {
    board b1;
    
    while (fin && fin.peek() != 'Z')
    {
      count++;
      c2 = 0; // Reset recurive count
      cout <<"Board " <<count <<endl;
      
      b1.clearConflicts(); //Remove conflicts from the previous board.
      b1.initialize(fin);
      b1.printBoard();
      b1.solveBoard(c2);
      totalRecursive += c2;
    }

    cout <<"All boards have been solved!" <<endl
	 <<"The avergae number of recusrive calls was: " 
	 <<(totalRecursive/96) <<endl;
  }

  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }

  fin.close();
  return 0;
}

