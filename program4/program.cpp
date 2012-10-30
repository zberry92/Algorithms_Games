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
  int i, j, k, count = 1, choice;
  
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
      b1.clearConflicts();
      cout <<"Board " <<count <<endl;
      b1.initialize(fin);
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
      count++;
      
      cout <<"Please enter '1' to add a value, '0' to delete a value " <<endl
	   <<"and '-1' to print the next board: ";
      cin >>choice;

      if (choice == 1)
      {
	cout <<"Please enter the value you wish to add: ";
	cin >>k;
        cout <<"X-coordinate: ";
        cin >>i;
	cout <<"Y-coordinate: ";
	cin >>j;

	if (b1.checkConflicts(k, i, j, b1.squareNumber(i, j)))
	{
	  b1.setCell(i, j, k);
	}
	else
	{
	  cout <<"You cannot place a number there, there is a conflict." <<endl;
	}
	b1.printBoard();
	b1.printConflicts();
      }
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
	continue;
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

