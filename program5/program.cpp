/* 
 * Zachary Berry and Patrick Willett
 * 11/12/12
 * Project 5a
 * This project will find a solution to the map using a recursive and 
 * non-recursive depth-frst search.
 */

#include "maze.h"

using namespace std;

// Depth-first search find the shortest path
bool findPathDepth(graph &g, maze &m, int begin, int end, vector<int> &sol)
{
  g.visit(begin);
  sol.push_back(begin);

  m.printMaze(m.reverseMapIdI(begin), m.reverseMapIdJ(begin), 
  m.numRows() - 1, m.numCols() - 1);

  if (begin == end)
  {
    return true;
  }

  for (int i = 0; i <= end; i++)
  {
    if ((i == begin) || g.isVisited(i) || !g.isEdge(begin, i))
    {
      continue;
    }
    if (findPathDepth(g, m, i, end, sol))
    {
      return true;
    }
    sol.pop_back();
    g.unVisit(i);
  }

  return false;
}

bool findPathBreadth(graph &g, maze &m, int end, vector<int> &s)
{
	queue< vector<int> > pathQueue;
	vector<int> shortPath, tempPath;
	
	pathQueue.push(vector<int>(1, 0));
	g.vist(0);
	
	while(!q.empty())
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
			if ((i == path.back()) || g.isVisited(i) || !g.isEdge(shortPath.back(), i))
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

// Non-recursive depth-first search ***Not in use for 5b***
void findPathNonRecursive(graph &g, int end, vector<int> &sol)
{
  int begin = 0;
  bool nextSteps;

  cout <<end;

  g.visit(begin);
  
  while (true)
  {
    nextSteps = false;
    if (sol.empty())
    {
      begin = 0;
    }
    else
    {
      begin = sol.back();
    }

    if (begin == end)
      return;

    for (int i = 0; i <= end; i++)
    {
      if ((i == begin) || g.isVisited(i) || !g.isEdge(begin, i) || g.isMarked(i))
		continue;
      sol.push_back(i);
      g.visit(i);
      nextSteps = true;
      break;
    }

    if (!nextSteps)
    {
      sol.pop_back();
      g.mark(begin);
      g.unVisit(begin);
    }
  }
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

    if (x != temp.size() - 1)
    {
      cout <<", then ";
    }

    prevI = i;
    prevJ = j;
  }

  cout <<endl <<endl;
} 

int main()
{
   ifstream fin;
   string fileName;
   graph ourGraph; 
   vector<int> recSolution, nonRecSolution(1, 0);

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
     // ourMaze.printMaze();
     ourMaze.mapMazeToGraph(ourGraph);
     
     // Find a path recursively
     cout <<"Recursive method: " <<endl;
     if (!findPathDepth(ourGraph, ourMaze, 0, ourMaze.endId(), recSolution))
     {
       cout <<"There are no solutions to the puzzle" <<endl;
     }
     else
     {
       printResult(ourMaze, recSolution);
       ourGraph.clearVisit();
     }

     // Non-recursively
     cout <<"Non-recursive method: " <<endl;
     findPathNonRecursive(ourGraph, ourMaze.endId(), nonRecSolution);
     printResult(ourMaze, nonRecSolution);
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
