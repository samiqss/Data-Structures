#ifndef UNIONFIND 
#define UNIONFIND 1

#include <string>
#include <iostream>
#include <climits>
using namespace std;


class unionfind{
   private:
	   int n;
	   int* parent; // Defines the data structure used for set identification
	   int* rank;   // Auxiliary information used and changed in the union (merge) operation

   public:
      unionfind(int k);
      ~unionfind(void);
      void debugprint(); 
      int  find(int p);
      void merge(int p, int q);
};


#endif
