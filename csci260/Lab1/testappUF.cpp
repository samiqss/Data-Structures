/************************************************/
/************   unionfind.cpp        ************/
/************   by Gara Pruesse      ************/
/************   Sept 2015            ************/
/************************************************/
/************************************************/
/* This is the test application for the Union-Find implementation
/* whose interface is found in unionfind.h
/* The program prompts the user for a file name; opens the file;
/* reads an integer that is the number of elements (n), then the
/* commands of the form "u 4 18" (union the set containing 4 wth the 
/* set containing 6" or "f 6" (find 6). */

#include "unionfind.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
   
   int setSize;
   int p,q; 
   int ending=0;
   string fileName;
   char cmd;
   ifstream ins;

   cout << "Enter the input file name: ";
   /* This file contains data of the form 
      5
      u 3 4
      f 1
      f 3
      u 4 1
      d

      the number at the top of the file is the number of elements in the union-find data
      structure; the d at the bottom is for invoking the debugprint command, dumping
      the data structure contents; and in between are union ("u 3 4") commands and 
      find ("f 3") commands
   */
   cin >> fileName;
   ins.open(fileName.c_str());
   if (ins.fail ())
   {
	   cerr << "*** Error: Cannot open file "<< fileName << endl;
   }

   
   ins >> setSize; // get the number of elements
   unionfind set(setSize);
   //Set.makeSize(n);  // initialize a unionfind set of size n

   ins >> cmd ;  // loop to process commands 'f' or 'u' or 'd'
   while (!ins.eof())
	{
   	switch (cmd) {
      		case 'f': ins >> p ;
			      set.find(p);
			      ins >> cmd;
               break;
      		case 'u': ins >> p >> q;
			      set.merge(p,q);
			      ins >> cmd;
               break;
      		case 'd': cout << "The array data is:" << endl;
               set.debugprint();
			      ins >> cmd;
               break; 
      	   default:  
			      ins >> cmd;
      }
	
   }
   ins.close();
   return 0;
}

