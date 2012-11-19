/* 
 * Zachary Berry and Patrick Willett
 * 11/12/12
 * Project 5b
 * This project will find the shortest solution to the map using 
 * depth-first and breadth-first
 * search.
 */

#include "maze.h"
#include <queue>

using namespace std;

// Depth-first search find the shortest path
void findPathDepth(graph &g, int begin, int end, vector<int> &sol,
		   vector<int> &tempSol)
{
  g.visit(begin);
  tempSol.push_back(begin);

  if (begin == end)
  {
    if(sol.size() > tempSol.size() && !sol.empty())
    {
      sol = tempSol;
    }
    else if(sol.empty())
    {
      sol = tempSol;
    }
  }

  for (int i = 0; i <= end; i++)
  {
    if ((i == begin) || g.isVisited(i) || !g.isEdge(begin, i))
    {
      continue;
    }
    findPathDepth(g, i, end, sol, tempSol);
    tempSol.pop_back();
    g.unVisit(i);
    
  }

  return;
}

// findPathBreadth() will find the shortest path to the goal using breadth
// first search.
bool findPathBreadth(graph &g, int end, vector<int> &s)
{
  queue< vector<int> > pathQueue;
  vector<int> shortPath, tempPath;
	
  pathQueue.push(vector<int>(1, 0));
  g.visit(0);
  
  while(!pathQueue.empty())
  {
    shortPath = pathQueue.front();
    pathQueue.pop();
		
    if (shortPath.back() == end)
    {
      s = shortPath;
      return true;
    }
    
    for (int i = 0; i <= end; i++)
    {
      if ((i == shortPath.back()) || g.isVisited(i) || 
	  !g.isEdge(shortPath.back(), i))
      {
	continue;
      }
      
      tempPath = shortPath;
      tempPath.push_back(i);
      g.visit(i);
      pathQueue.push(tempPath);
    }
  }
  
  return false;
}

// Print instructions to the user.
void printResult(maze &m, vector<int> temp)
{
  int i, prevI, j, prevJ;

  prevI = m.reverseMapIdI(temp[0]);
  prevJ = m.reverseMapIdJ(temp[0]);

  cout <<"To solve the maze from the start: ";

  for (int x = 1; x < (int) temp.size(); x++)
  {
    i = m.reverseMapIdI(temp[x]);
    j = m.reverseMapIdJ(temp[x]);
    
    if (x != 1 && x != temp.size() - 1)
    {
      cout <<"then ";
    }

    if (prevI > i)
    {
      cout <<"move up";
    }
    else if (prevI < i)
    {
      cout <<"move down";
    }
    else if (prevJ > j)
    {
      cout <<"move to the left";
    }
    else if (prevJ < j)
    {
      cout <<"move to the right";
    }

    m.printMaze(i, j, m.numRows() - 1, m.numCols() - 1);

    prevI = i;
    prevJ = j;
  }
} 

int main()
{
   ifstream fin;
   string fileName;
   graph ourGraph; 
   vector<int> depthSolution, breadthSolution, tempDepth;

   cout <<"Please enter the name of the maze file: ";
   cin >>fileName;

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      return 0;
   }

   try
   {
     maze ourMaze(fin); 
     ourMaze.mapMazeToGraph(ourGraph);
     
     // Depth-first shortest path
     cout <<"Depth-first shortest path: " <<endl;
     findPathDepth(ourGraph, 0, ourMaze.endId(), depthSolution, tempDepth);
     if (depthSolution.back() != ourMaze.endId())
     {
       cout <<"There are no solutions to the puzzle" <<endl;
     }
     else
     {
       printResult(ourMaze, depthSolution);
       cout <<"Congratulations! The maze has been solved!" <<endl;
       ourGraph.clearVisit();
     }

     // Bread-first shortest path
     cout <<"Breadth-first shortest path: " <<endl;
     if (!findPathBreadth(ourGraph, ourMaze.endId(), breadthSolution))
     {
       cout <<"There are no solutions to the puzzle" <<endl;
     }
     printResult(ourMaze, breadthSolution);
     cout <<"Congratulations! The maze has been solved!" <<endl;
     ourGraph.clearVisit();
   } 

   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl;
      return 0;
   }

   catch (rangeError &ex)
   {
      cout << ex.what() << endl;
      return 0;
   }

   return 0;
}
