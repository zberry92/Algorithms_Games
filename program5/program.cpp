/* 
 * Zachary Berry and Patrick Willett
 * 11/12/12
 * Project 5a
 * This project will find a solution to the map using a recursive and 
 * non-recursive depth-frst search.
 */

#include "maze.h"

using namespace std;

bool findPathRecursive(graph &g, int begin, int end, vector<int> &sol)
{
  g.visit(begin);
  sol.push_back(begin);
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
    if (findPathRecursive(g, i, end, sol))
    {
      return true;
    }
    sol.pop_back();
    g.unVisit(i);
  }

  return false;
}

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

    for (int i = 0; i <= end; i ++)
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



void printResult(vector<int> temp)
{
  cout <<"To solve the maze you go from: ";

  for (int i = 0; i < temp.size(); i++)
  {
    cout <<"node " <<temp[i];
    if (i != temp.size() - 1)
      cout <<" to ";
  }

  cout <<endl <<endl;
} 

int main()
{
   ifstream fin;
   string fileName = "maze1.txt";
   graph ourGraph; 
   vector<int> recSolution, nonRecSolution(1, 0);

   cout <<"Please enter the name of the maze file: ";
   //cin >>fileName;

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      return 0;
   }

   try
   {
     maze ourMaze(fin); 
     ourMaze.printMaze();
     ourMaze.mapMazeToGraph(ourGraph);
     
     // Find a path recursively
     cout <<"Recursive method: " <<endl;
     if (!findPathRecursive(ourGraph, 0, ourMaze.endId(), recSolution))
       cout <<"There are no solutions to the puzzle" <<endl;
     printResult(recSolution);

     // Non-recursively
     cout <<"Non-recursive method: " <<endl;
     findPathNonRecursive(ourGraph, ourMaze.endId(), nonRecSolution);
     printResult(nonRecSolution);
     
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
}
