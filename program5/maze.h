/* 
 * Maze class to handle all maze operations.
 */
#ifndef MAZE_CLASS
#define MAZE_CLASS

#include <limits.h>
#include "graph.h"

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);

      int numRows(){return rows;};
      int numCols(){return cols;};

      int reverseMapIdI(int id);
      int reverseMapIdJ(int id);
      int endId(){return mazeGrid[rows - 1][cols - 1];};

      void printMaze(int currI, int currJ, int goalI, int goalJ);
      bool isLegal(int i, int j);

      void mapMazeToGraph(graph &g);

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<int> mazeGrid;
      vector<int> idI;
      vector<int> idJ;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
  char x;
  int idVal = 0;

  fin >> rows;
  fin >> cols;  
  mazeGrid.resize(rows, cols);

  for (int i = 0; i <= (rows - 1); i++)
  {
    for (int j = 0; j <= (cols - 1); j++)
    {
      fin >> x;
      if (x == 'O')
      {
	mazeGrid[i][j] = idVal;
	idI.push_back(i);
	idJ.push_back(j);
	idVal++;
      }      
      else
      {
	mazeGrid[i][j] = -1;
      }
    }
  }
}

int maze::reverseMapIdI(int id)
{
  return idI[id];
}

int maze::reverseMapIdJ(int id)
{
  return idJ[id];
}

void maze::printMaze(int currI, int currJ, int goalI, int goalJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
  cout << endl;
	
  if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)	
    throw rangeError("Bad value in maze::print");
	
  if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
    throw rangeError("Bad value in maze::print");
	
  for (int i = 0; i <= rows-1; i++)	
  {
    for (int j = 0; j <= cols-1; j++)	
    {	
      if (i == goalI && j == goalJ)	
	cout << "*";
      else
	if (i == currI && j == currJ)
	  cout << "+";
	else
	  if (mazeGrid[i][j] != -1)	
	    cout << " ";	
	  else	
	    cout << "X";    	
    }
    cout << endl;
  }
  cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to occupy cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   if (mazeGrid[i][j] > -1)
     return true;
   else
     return false;
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
  node tempNode;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (isLegal(i, j))
      {
	tempNode.setId(mazeGrid[i][j]);
	g.addNode(tempNode);

	if ((i > 0) && isLegal(i - 1, j))
	{
	  g.addEdge(mazeGrid[i][j], mazeGrid[i - 1][j]);
	  g.addEdge(mazeGrid[i - 1][j], mazeGrid[i][j]);
	}
	if ((j > 0) && isLegal(i, j - 1))
	{
	  g.addEdge(mazeGrid[i][j], mazeGrid[i][j - 1]);
	  g.addEdge(mazeGrid[i][j - 1], mazeGrid[i][j]);
	}
      }
    }
  }

  return;
}
#endif
