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
	if(p==parent[p])  return p;
	else{
		parent[p]=find(parent[p]);
		return parent[p];
	}
// return 0;
}


void unionfind::merge(int p, int q)
//    merge the set containing p with the set containing q 
{
	int pp=find(p);
	int pq=find(q);
	if(rank[pp]==rank[pq]){
		rank[pp]++;
		parent[pq]=parent[pp];
	}
	else if(rank[pq]>rank[pp])
	{
		parent[pp]=parent[pq];
	}

	else
	{
		parent[pq]=parent[pp];
	}
	
}


void unionfind::debugprint()
// display the contents and structure of parent array
{
	for (int i=0; i<n; i++){ 
		if(find(i)==i){
			cout << "[" << i << "]";
			for(int j=0; j<n; j++){
				if(find(j)==i){
					cout << " "<< j;
				}
			}
			cout << endl << endl;	
		}		
	}

}


