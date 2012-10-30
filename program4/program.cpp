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
  int i, j, count = 0, choice;
  char k;
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
      cout <<"Board " <<count <<endl;
      
      b1.clearConflicts(); //Remove conflicts from the previous board.
      b1.initialize(fin);
      b1.printBoard();
      b1.printConflicts();
      
      // Check to see if the board is solved. If it is move to next board.
      if (b1.isSolved())
      {
	cout <<"Congratulations! The board has been solved!!" <<endl;
	continue;
      }
      else
      {
	cout <<"The board is not yet solved." <<endl;
      }

      // While loop to add or remove values from the board until the user enters -1.
      while (choice != -1)
      {
	cout <<"Please enter '1' to add a value, '0' to delete a value " <<endl
	     <<"and '-1' to print the next board: ";
	cin >>choice;
	
	// Add a number to the matrix
	if (choice == 1)
	{
	  cout <<"Please enter the value you wish to add: ";
	  cin >>k;
	  cout <<"X-coordinate: ";
	  cin >>i;
	  cout <<"Y-coordinate: ";
	  cin >>j;
	  
	  if (b1.checkConflicts(atoi(&k), i, j, b1.squareNumber(i, j)))
	  {
	    b1.setCell(i, j, k);
	    b1.printBoard();
	    b1.printConflicts();
	    if (b1.isSolved())
	    {
	      cout <<"Congratulations! The board has been solved!!" <<endl;
	      continue;
	    }
	    else
	    {
	      cout <<"The board is not yet solved." <<endl;
	    }
	  }
	  else
	  {
	    cout <<"You cannot place a number there, there is a conflict." <<endl; 
	  }
	}

	// Remove a number from a cell.
	else if (choice == 0)
	{
	  cout <<"Please enter the X-coordinate you wish to delete: ";
	  cin >>i;
	  cout <<"Y-coordinate: ";
	  cin >>j;
	  b1.clearCell(i, j);
	  b1.printBoard();
	  b1.printConflicts();
	}
	else
        {
	  cout <<"Please enter a correct value!" <<endl;
	}
      }
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

