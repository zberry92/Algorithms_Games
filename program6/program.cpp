/*
 * Zachary Berry and Patrick Willet
 * 11/27/12
 * Project 6a
 * This project will create a spanning forest of a graph and check if the
 * graph is connected or cyclic.
 */

#include <limits.h>
#include "graph.h"
#include <queue>
#include <vector>

using namespace std;

int const NONE = -1;  // Used to represent a node that does not exist

// Create a graph sf that contains a spanning forest on the graph g.
void findSpanningForest(graph &g, graph &sf)
{
}

// Returns true if the graph g contains a cycle.  Otherwise, returns false.
bool isCyclic(graph &g, int begin)
{
  if (g.isVisited(begin))
  {
    return true;
  }

  g.visit(begin);
  
  for (int i = 0; i < g.numNodes(); i++)
  {
    if ((i == begin) || !g.isEdge(begin, i))
    {
      continue;
    }
    if (isCyclic(g, i))
    {
      return true;
    }
  }
   
  return false;
}  

// Returns true if the graph g is connected.  Otherwise returns false
bool isConnected(graph &g, int begin)
{
  g.visit(begin);

  if (g.allNodesVisited())
  {
    return true;
  }

  for (int i = 0; i < g.numNodes(); i++)
  {
    if ((begin == i) || g.isVisited(i) || !g.isEdge(begin, i))
    {
      continue;
    }
    if (isConnected(g, i))
    {
      return true;
    }
  }

  return false;
}

int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;
   bool connected, cyclic;

   cout <<"Enter filename: ";
   cin >>fileName;
   
   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr <<"Cannot open " <<fileName <<endl;
   }

   try
   {
      cout <<"Reading graph" <<endl;
      graph g(fin);

      cout << g;

      connected = isConnected(g, 0);
      g.clearVisit();
      cyclic = isCyclic(g, 0);
      g.clearVisit();

      if (connected)
	 cout << "Graph is connected" << endl;
      else
	 cout << "Graph is not connected" << endl;

      if (cyclic)
	 cout << "Graph contains a cycle" << endl;
      else
	 cout << "Graph does not contain a cycle" << endl;

      cout << endl;
      cout << "Finding spanning forest" << endl;

      // Initialize an empty graph to contain the spanning forest
      graph sf(g.numNodes());
      findSpanningForest(g, sf);

      cout << endl;

      cout << sf;

      cout << "Spanning forest weight: " << sf.getTotalEdgeWeight()/2 << endl;

      connected = isConnected(sf, 0);
      sf.clearVisit();
      cyclic = isCyclic(sf, 0);
      sf.clearVisit();

      if (connected)
	 cout << "Graph is connected" << endl;
      else
	 cout << "Graph is not connected" << endl;

      if (cyclic)
	 cout << "Graph contains a cycle" << endl;
      else
	 cout << "Graph does not contain a cycle" << endl;

      cout << endl;
   }    
   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; 
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; 
   }
}

