/************************************************/
/************   testapp.cpp - for expresslist        ************/
/************   by Gara Pruesse      ************/
/************   Sept 2015            ************/
/************************************************/
/************************************************/

#include "ExpressList.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

char getcommand();
bool processcommand(char cmd);


int main()
{
   
   int num;
   int k;
   string datastring;
   int ending=0;
   string fileName;
   char cmd;
   ifstream ins;

   cout << "Enter the input file name: ";
   cin >> fileName;
   ins.open(fileName.c_str());
   if (ins.fail ())
   {
	cerr << "*** Error: Cannot open file "<< fileName << endl;
   }

   
   ExpressList S;

   ins >> num;
   if (num>=0) 
	S.setStep(num); // set the step size, 2 is default

int count=0;
   ins >> cmd ;

   while (!ins.eof())
	{
	cout<< "at count" <<count<<" " <<endl;
	count++;
   	switch (cmd) {
      		case 'f': ins >> k ;
			      datastring = S.find(k);
			      if (S.found()) 
			    	   cout << "[" << k << "]" << datastring<<" "<< endl;
			      else
                  		   cout << k << " not found.\n";
			      ins >> cmd;
               		      break;
      		case 'i': ins >> k >> datastring;
			      S.insert(k,datastring); 
			      ins >> cmd;
			      cout<<"did an insertion"<<endl;
              		      break;
      		case 'd': cout << "The dictionary data is:" << endl;
              		      S.debugprint();
			      ins >> cmd;
              		      break; 
      		default:  
			      ins >> cmd;
   		}
	
   	}
   ins.close();
   return 1;
}

