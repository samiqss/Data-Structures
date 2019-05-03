//
// unionfind.cpp
// Stubs provided by: Gara Pruesse
// Implementation provided by: [Sami Al-Qusus]
// Date: September 2017
//
// This unionfind class implements disjoint sets as an array of integers 
// The implmentation is the classic "Quick-Find" implementation,
// wherein the name of the set containing each element is stored 
// in the "parent" array indexed by element name -- thus 
// to find the set containing element 5, look up parent[5]
//  
// Merge (union) involves renaming the parent of all the elements of 
// one set to have the name of the other set (always the one with the smaller
// element-name).
//
#include "unionfind.h"


unionfind::unionfind(int k)
{
	n = k;
	parent = new int[k];
	rank = new int[k];
	for(int i=0; i<k; i++){
		parent[i]=i;
		rank[i]=0;
	}
}


unionfind::~unionfind(void)
{
	delete[] parent;
	delete[] rank;
}


int unionfind::find(int p )
// returning the integer representing the set containing element p
//
{
	int name;
	name = parent[p]

	return name;

}


void unionfind::merge(int p, int q)
//    merge the set containing p with the set containing q 
{
	int pparent=parent[p];
	int qparent=parent[q];

	if(pparent<qparent){
		for (int i=0; i<n;i++){
			if(parent[i]==parent[qparent]){
				parent[i]=parent[pparent];
			}

		}
	}
	else
	{
		for(int i=0; i<n; i++){
			if(parent[i]==parent[pparent]){
				parent[i]=parent[qparent];
			}
		}
	}

	
}


void unionfind::debugprint()
// display the contents and structure of parent array
{
	for (int i=0; i<n; i++){ 
		cout << "[" << i << "]" << parent[i];
		cout << endl << endl;
	}

}


