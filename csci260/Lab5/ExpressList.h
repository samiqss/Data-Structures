#ifndef EXPRESSLIST
#define EXPRESSLIST 1

#include <string>
#include <iostream>
#include <climits>
using namespace std;


class ExpressList{
   private:
	struct ListElement { 
		int key; 
		string data; 
		ListElement *next; 
		ListElement *nextExpress;
		} ;
	ListElement *head, *tail;
	int n;  // size of the list
	int stepsize;  // size of the express list is n/stepsize
	int foundflag; // Did the last searched item get found?
	int numcomparisons; // for purposes of analysis, we will count comparisons

      // private routines
      // (used by the public methods)
      

   public:
		
      ExpressList(); 
      ~ExpressList();
      int getSize() {return n; }
      int getStep() { return stepsize; }
      void setStep(int s) {stepsize = s; }
      void debugprint(); 
      int comparisons();
      int insert(int k, string data);
      string find(int k);
      int found(); // 1 if last "find" was successful, 0 otherwise.
};

#endif
