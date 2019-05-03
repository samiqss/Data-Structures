//
// ExpressList.cpp
// Author: Gara Pruesse
// Date: September 20, 2015
//
// This ExpressList class implements a dictionary using a linked list and 
// an "express lane" 
//
#include <stdlib.h>
#include <time.h>
#include "ExpressList.h"

ExpressList::ExpressList() 
// Empty list is just a tail with INT_MAX as key; tail point to self
{ 
	n=0; 
	tail=new ListElement; 
	head=new ListElement; 
	head->nextExpress=tail;
	head->next=tail;
	head->key=-1;
	tail->key=INT_MAX;
  	tail->next = tail;
        tail->nextExpress=tail;
	stepsize=2; 
	foundflag=1; 
	numcomparisons=0; 
	
        srand(time(NULL));
}


ExpressList::~ExpressList()
{
	ListElement* temp = head;
	while (temp != tail)
		{
		head=temp;
		temp= temp->next; 
		delete head;
		}
   delete tail;
}

string ExpressList::find(int k )
// returning the string that is the data attached to some element with key k
//
{
	ListElement *temp=head;
	foundflag=0;
	while ((temp->nextExpress->key)<k) 
	{
		temp = temp->nextExpress;
		numcomparisons++;
//		cout<<"im became "<<temp->key<< " "<<endl;
	}
	
	while ((temp->next->key)< k) 
	{
		temp = temp->next;
		numcomparisons++;
//		cout<<"i became "<<temp->key<< " "<<endl;

	}
	temp=temp->next;
	if (temp->key==k)
//		cout<<"found it! "<<endl;
		foundflag=1;
	if (foundflag==1){
//		cout<<"flag = 1 for key "<< k<<" "<<endl;
		return temp->data;
	}
	else
	{
//		cout<<"returning 0 flag for key "<< k<< " "<<endl;
		return std::string();
	}
}

int ExpressList::found()
// 1 if last call to find found the key; 0 otherwise
//
{
	return foundflag;
}


int ExpressList::insert(int k, string d)
//    insert k,data into the dictionary
{
	ListElement *temp, *expresstemp, *back, *el;
	el = new ListElement;
	el->key =k;
	el->data=d;
       

	temp=head;
	expresstemp=head;
	back=head;

	if (head->key > k)
		{
		numcomparisons++;
		el->next = head;
		el->nextExpress = head;
		head = el;
		return 1;
		}

	while ((temp->nextExpress->key < k && temp!=tail))
		{
		numcomparisons++;
		temp=temp->nextExpress;
		}
   expresstemp=temp;
	while ((temp != tail) && (temp->next->key < k))
		{
		numcomparisons++;
		temp=temp->next;
		}
	// replace if back has same key k
	if (k==temp->key) {
		numcomparisons++;
		temp->data = d;
		delete el;
		return 0;
		}
	el->next=temp->next;
   if (rand()%stepsize <1) {
         el->nextExpress = expresstemp->nextExpress;
         expresstemp -> nextExpress = el;
      }
   temp->next = el;
	return 1;
}


void ExpressList::debugprint()
// display the contents of the ExpressList
{
	ListElement* temp = head->nextExpress;
   	cout << "Keys in the Express Lane of the list: ";
	
	while (temp != tail)  
	{
		cout << temp->key << "," ;
		temp = temp->nextExpress;
	}

   	cout << endl<< endl;
   	temp = head->next;
   	cout << "Keys in the milk-run Lane of the list: ";
	while (temp != tail)  
	{
		cout << "[" << temp->key << "]" << temp->data;
		temp = temp->next;
	}
	cout << endl<<"comparisons = "<< numcomparisons <<endl << endl;
}


