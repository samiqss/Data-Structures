/****************************************************************
/*            graph.cpp
/*                  
/*            by Sami Al-Qusus (initial code provide by Professor Gara Pruesse)
/*            Nov 25, 2017
/*
/*            reads a graph in from a file
/*            builds graph, provides graph access routines
/*            and computes a Minimum Spanning Tree, using a function passed in
/*            
/*********************************************************************/

#include <queue>  // used in first prototype for minSpanningTree 
#include "graph.h"
#include "unionfind.h"

using namespace std;

// int NO_VERTEX=-1;

graph::graph()
{
	n=0;
}

graph::graph(int numverts)
{
   n=numverts;
   Adj = new vector<edge>[n];
}

// There are two ways to build a graph: one is to declare a graph using
// graph(n) and then using add_edge to add all the edges individually.
// The other is to intialize the graph without specifying n, and then 
// using the graph's method graph_read to read data from the file. 
// 5
// 0 1 100
// 3 2 450
// 5 5 5 
// The above is a sample of the contents of a file; in this case, the 
// graph will have five vertices 0, 1, 2, 3, 4, and edges (0,1) of weight 100
// and (2,3) of weight 450.  Any first integer of 5 or greater ends the graph data.
int graph::graph_read(char *fn)
{
   ifstream f;
   int u;
   int v;
   int w;
   edge e;

   f.open(fn);
   if (!f) { 
      cerr<<"File not openable. "<<endl; return 0;
      }
   f >> n;   
   cout << n<< endl; // n is the 
   Adj = new vector<edge>[n];

   f >> u;

   while (u<n && f)
   {
      // FOR YOU TO DO: read the vertex u is adjacent to, and the weight, and put in e
      // e.vertex1=u;
      f >> v;
      // e.vertex2=v;
      f >> w;
      //e.weight=w;
 

      // insert e into u's adjacency list
      // Adj[u].push_back(e);
      add_edge(u,v,w);

      // FOR YOU TO DO:add edge into vertex2's list as well, since G is undirected
      //Adj[v].push_back(e);
      add_edge(v,u,w);
      f >> u; // read the start of the next line
	
   }

   f.close();
   return 1;
}

graph::~graph()
{
   for (int v=0; v<n; v++)
   {
	   Adj[v].clear();
   }
} 
int graph::add_edge(int u, int v, int w)
// adds an edge (u,v) with weight w
{    
	edge e;
	e.vertex1=u;
	e.vertex2=v;
	e.weight=w;
	Adj[u].push_back(e);
	return 1;
}


int graph::remove_edge(int u, int v)
//removes edge (u,v)
{    
	int tester;
	int count=0; //counts position in vector to keep mark on where to erase
	vector<edge>::iterator currneighb1 = Adj[u].begin();
	while (currneighb1 != Adj[u].end())
	{
		tester = (*currneighb1).vertex2;
		if(tester==v){
			Adj[u].erase(Adj[u].begin()+count);
			break;

		}
		count++;
	}

	count=0;
	
	//also erase edge from v
	vector<edge>::iterator currneighb2 = Adj[v].begin();
	while (currneighb2 != Adj[v].end())
	{
		tester = (*currneighb2).vertex2;
		if(tester==u){
			Adj[v].erase(Adj[v].begin()+count);
			break;
		}
		count++;
	}

	return 1;
}

int graph::adjacent(int u, int v)
//checks if u and v are adjacent 
//iff yes return 1
//if no return 0
// not too sure if thats what you want this function to do
{
	int tester;
	vector<edge>::iterator currneighb = Adj[u].begin();
	while (currneighb != Adj[u].end())
	{
		tester = (*currneighb).vertex2;
		if(tester==v){
			return 1;
		}
	}
	
	return 0;	
}

// call print_vertex on each vertexin the graph
bool graph::print_graph()
{
   for (int v=0; v<n; v++)
   {
        print_vertex(v);
   }
   return true;
}

bool graph::print_vertex(int v)
{

   vector<edge>::iterator currneighb = Adj[v].begin();
   cout << v << ": ";
   while (currneighb != Adj[v].end()) 
   {
   	cout << (*currneighb).vertex2<< "  ";
   	currneighb ++;
   }
   cout << endl;
   return true;
}


/**********************************************************
 *             Minimum Spanning Tree 
 *
 **********************************************************/

//PRIMS MST
graph graph::min_spanning_tree(int v)
// Returns a Minimum Spanning Tree; v is the start vertex.  
// For the first prototype of this subprogram, just 
// return a spanning tree -- it does not have to be minimum.
{
   graph T = graph(n);

// if they have same parent then dont add that edge because they will loop.
// declarations
   edge arr[n];
   int tester;
   int testerw;
// NOT MINIMUN SPANNING TREE YET
   unionfind set(n);
   int num_edges = 0;
   int Tweight = 0;

   // consider each edge in turn: all those incident with v, v+1, etc. until n-1 
   // edges have been added or all the vertices have been considered (i.e., all 
   // edges considered.  Let Tweight be the total weight of the tree.

   int temp=10000;
   int count=0;
   int vert = v%n;
   vector<edge>::iterator e_ptr;

   for ( vert=v%n;  (vert != v-1) && num_edges < n-1; vert=(vert+1)%n) {
         
            // ADD EDGES TO T ONLY IF THEY DO NOT FORM A CYCLE.
            // HOW WILL YOU BE ABLE TO TELL IF THE NEXT EDGE YOU
            // ARE CONSIDERING WILL FORM A CYCLE WITH WHAT HAS 
            // HAS ALREADY BEEN ADDED TO T -----> answer: if they have same parent will not add them in new tree!
	e_ptr=Adj[vert].begin();
	
	int done=0;

	//loop goes through all edges in current vert
	while (e_ptr != Adj[vert].end()) 
	{
		
		tester = (*e_ptr).vertex2; //hold values of vertex2
		testerw = (*e_ptr).weight; //holds value of weight
                	
	        if(testerw < temp)
		{

			if(count != 0) arr[count]=arr[count-1];
		       	arr[count-1]= *e_ptr;
			temp= testerw;
		}
		
		else 
		{
			arr[count]= e*_ptr;
		}

		count++;
		e_ptr++;
	}

	num_edges++;
   	if (num_edges == n-1)  break;
   }

  int v1, v2, w;
  for(int i=0; i<count; i++){
	  	
	 	v1= arr[i].vertex1;
		v2= arr[i].vertex2;
		w= arr[i].weight;
		//adds edges of Adj vector to tree unless the edge equals to its self or if it has been added before 
		//or parent of vert == parent of tester becuase adding that edge would cause a loop
		if( set.find(v1)!=set.find(v2) )
		{
			set.merge(v1, v2);//give both vert and tester the same parent so we dont add either again to that path
			T.add_edge(v1, v2, w);//since they dont create a loop add the edge to T
			T.add_edge(v1,v1,w);//adding the edge in vector vert aswell
			tweight= Tweight+w;//not sure if you want total weight of sub tree T or original tree v, currently we get back weight of T
		}	
	}


   if (num_edges<n-1){
      cout << "Graph was not connected. "<<n-num_edges<<" connected components.\n";
   }
   cout << "Tree weight = "<<Tweight<< endl;
   return T;
}


            


         

