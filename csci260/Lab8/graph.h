/****************************************************************
/*            graph.h
/*            by Gara Pruesse
/*            Oct 5 2009
/*
/*            class that reads a graph in from a file
/*            builds graph, provides graph access routines
/*            
/*********************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <values.h>
#include <vector>   // STL vector, for adjacency list; ability to iterate

using namespace std;

const int NO_EDGE=0;
const int NO_VERTEX = -1;

struct edge {
   int vertex1;
   int vertex2;
   int weight;
};

class graph {
   private:
      int n;
      int default_nonedge;
      vector<edge> *Adj;// array of neighbour-vector
                       // entries are names of neighbours


   public: 
      graph();
      graph(int num); 
	   int graph_read(char *fn);
	   ~graph();
	   int num_vertices() { return n; }
	   int add_edge(int u, int v, int wt);
	   int remove_edge(int u, int v);
	   int adjacent(int u, int v);
	   bool print_graph();
	   bool print_vertex(int v);
	   graph min_spanning_tree(int v);
};


	
