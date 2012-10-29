/*
 * Zachary Berry & Patrick Willet (berwil)
 * 10/28/12
 * Program 4a
 * This program will load in sudoku boards and print out the boards and their 
 * conflicts if any exist.
 */

#include "board.h"

using namespace std;

// Overloaded output operator for vector class.
ostream &operator<<(ostream &oStr, vector<int> &v)
{
   for (int i = 0; i < v.size(); i++)
   {
	  oStr <<v[i] <<" ";
   }
   
   oStr <<endl;
   return oStr;
}

int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";
   
   fin.open(fileName.c_str());
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

