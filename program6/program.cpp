/*
 * Zachary Berry and Patrick Willet
 * 11/27/12
 * Project 6b
 * This project will create a minimum spanning forest of a graph, check 
 * if the graph is connected or cyclic and compare it to our original
 * spanning tree.
 */

#include <limits.h>
#include "graph.h"
#include <queue>
#include <vector>

using namespace std;

int const NONE = -1;  // Used to represent a node that does not exist

// Create a graph sf that contains a spanning forest of the graph g.
void findSpanningForest(graph &g, graph &sf)
{
  for (int i = 0; i < g.numNodes(); i++)
  {
    if (g.allNodesMarked())
    {
      g.clearMark();
      return;
    }

    g.mark(i);

    for (int j = 0; j < g.numNodes(); j++)
    {
      if ((i == j) || g.isMarked(j) || !g.isEdge(i, j))
      {
	continue;
      }
      
      sf.addEdge(i, j, g.getEdgeWeight(i, j));
      sf.addEdge(j, i, g.getEdgeWeight(j, i));
      g.mark(j);
    }
  }
}

// Returns true if the graph g contains a cycle.  Otherwise, returns false.
bool isCyclic(graph &g, int begin = 0, int prevNode = 0)
{
  if (g.isVisited(begin))
  {
    g.clearVisit();
    return true;
  }

  g.visit(begin);
  
  for (int i = 0; i < g.numNodes(); i++)
  {
    if ((i == begin) || !g.isEdge(begin, i) || prevNode == i)
    {
      continue;
    }
    if (isCyclic(g, i, begin))
    {
      return true;
    }
  }
   
  return false;
}  

// Returns true if the graph g is connected.  Otherwise returns false
bool isConnected(graph &g, int begin = 0)
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

// primMinimumSpanning finds the minimum spanning forest. It will also count the number
// of connected components. 
void primMinimumSpanning(graph &g, graph &msf, int &connectedComp)
{
  vector<int> visitNode;
  int tempEdgeWeight, minEdgeWeight, iterNode, 
      tempNode = 0, numConnect = 1;

  g.mark(0);
  visitNode.push_back(0);

  while (!g.allNodesMarked())
  {
    // If we have completed a connected segment, find the next unmarked node and start
    // from there.
    if (tempNode == -1) 
    {
      numConnect++;
      visitNode = vector<int>(1, g.findUnmarkedNode());
    }

    minEdgeWeight = 0;
    tempNode = -1;

    for (vector<int>::iterator iter = visitNode.begin(); iter < visitNode.end(); iter++)
    {
      for (int i = 0; i < g.numNodes(); i++)
      {
	if ((*iter == i) || g.isMarked(i) || !g.isEdge(*iter, i))
	{
	  continue;
	}
	
	tempEdgeWeight = g.getEdgeWeight(*iter, i);
	if (minEdgeWeight == 0 || minEdgeWeight > tempEdgeWeight)
	{
	  minEdgeWeight = tempEdgeWeight;
	  iterNode = *iter;
	  tempNode = i;
	  continue;
	}
      }
    }

    if (tempNode != -1)
    {
      g.mark(tempNode);
      msf.addEdge(iterNode, tempNode, minEdgeWeight);
      msf.addEdge(tempNode, iterNode, minEdgeWeight);
      
      visitNode.push_back(tempNode);
    }
  }

  connectedComp = numConnect;
}

int main()
{
   ifstream fin;
   string fileName;
   bool connected, cyclic;
   int sfCost, msfCost, msfConnectedComp;

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

      cout <<g;

      g.clearVisit();

      connected = isConnected(g);
      g.clearVisit();
      cyclic = isCyclic(g);
      g.clearVisit();

      if (connected)
	cout <<"Graph is connected" <<endl;
      else
	cout <<"Graph is not connected" <<endl;

      if (cyclic)
	cout <<"Graph contains a cycle" <<endl;
      else
	cout <<"Graph does not contain a cycle" <<endl;

      cout <<endl;
      cout <<"Finding spanning forest" <<endl;

      // Initialize an empty graph to contain the spanning forest
      graph sf(g.numNodes());
      findSpanningForest(g, sf);

      cout <<endl;

      cout <<sf;

      sfCost = sf.getTotalEdgeWeight() / 2;

      cout <<"Spanning forest weight: " <<sfCost <<endl;

      sf.clearVisit();
      connected = isConnected(sf);
      sf.clearVisit();
      cyclic = isCyclic(sf);
      sf.clearVisit();

      if (connected)
	 cout <<"Graph is connected" <<endl;
      else
	 cout <<"Graph is not connected" <<endl;

      if (cyclic)
	 cout <<"Graph contains a cycle" <<endl;
      else
	 cout <<"Graph does not contain a cycle" <<endl;

      cout <<endl;

// Initialize an empty graph to contain the minimum spanning forest
      cout <<"Finding the minimum spanning forest" <<endl;

      graph msf(g.numNodes());
      primMinimumSpanning(g, msf, msfConnectedComp);

      cout <<endl;

      cout <<msf;

      msfCost = msf.getTotalEdgeWeight() / 2;

      cout <<"Minimum Spanning forest weight: " <<msfCost <<endl;

      msf.clearVisit();
      connected = isConnected(msf);
      msf.clearVisit();
      cyclic = isCyclic(msf);
      msf.clearVisit();

      if (connected)
	 cout <<"Graph is connected" <<endl;
      else
	 cout <<"Graph is not connected" <<endl;

      if (cyclic)
	 cout <<"Graph contains a cycle" <<endl;
      else
	 cout <<"Graph does not contain a cycle" <<endl;

      cout <<endl;

      cout <<"The total number of connected components is: " 
	   <<msfConnectedComp <<endl;

      cout <<"The total cost of the initial spanning forest was $" 
	   <<sf.getTotalEdgeWeight()/2 <<endl
	   <<"The total cost of our minimum spanning forest was $"
	   <<msf.getTotalEdgeWeight()/2 <<endl
	   <<"The total improved cost is $" <<(sfCost - msfCost) <<endl;
   }    
   catch (indexRangeError &ex) 
   { 
      cout <<ex.what() <<endl; 
   }
   catch (rangeError &ex)
   {
      cout <<ex.what() <<endl; 
   }
}

