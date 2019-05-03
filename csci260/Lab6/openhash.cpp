/*****************************************************************/
/**        openhash.C                                            */
/**        Modified by Sami Al-Qusus                             */
/**        Used some of G. Pruesse's (closed hashing) code       */
/**        Oct 27, 2017                                          */
/*****************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <list>
#include <stdlib.h>
using namespace std;

// print some extra info while in debugging mode
const bool DEBUG = false;

// can change keytype and datatype to anything 
//     as long as the generators and hash functions
//     are updated appropriately
typedef string keytype;
typedef float datatype;

// define what the contents of a record look like
// next is pointer for linkedlist
struct record {
   keytype key;
   datatype data;
   //pointer that will keep track of list
   record *next;
};

//for ease we can define record* tp recordPtr
typedef record* recordPtr; 

// define a hash table of record pointers,
//    with methods to insert a new record into the table
//    and lookup a record based on its key
//    longest is to keep track of longest list
class hashtable {
   private:
      recordPtr *table;
      int tsize;
      int hash(keytype k, int i);
      int longest;
      int entries;
   public:
      hashtable(int sz = 0);
      ~hashtable();
      bool insert(recordPtr r);
      recordPtr lookup(keytype k);  
      keytype nextkey();
};

// ------------- methods dependent on the key type --------------

// the hash function relies on knowledge of the keytype,
//     here assumed to be a string
//
// we're using a rotating hash function, 
// where, on processing each character, we:
//    make a copy of the current hash value
//         and shift it 12 bits
//    make another copy of the hash value
//         and shift it 6 bits
//    take the exclusive-or of the two shifted
//         values and the next key character
int hashtable::hash(keytype k,int offset)
{
   int length = k.length();
   int hash = length;
   for (int i = 0; i < length; i++) {
       if (DEBUG) {
          int h1 = hash << 12;
          int h2 = hash << 6;
          int h3 = k[i];
          cout << h1 << "^" << h2 << "^" << h3 << "=" << hash << endl;
       }
       hash = (hash << 12) ^ (hash <<  6) ^ k[i];
   }
   if (hash < 0) hash = -hash;
   return ((hash + offset)  % tsize  );
}

// generate random key
keytype hashtable::nextkey()
{
   keytype k;
   // here we rely on the actual datatype of the key,
   //      currently known to be a string,
   // we'll generate a random string of length 4..12
   int length = 4 + (random() % 8);
   for (int i = 0; i < length; i++) {
       char c = (random() % 26) + 'a';
       k += c;
   }
   return k;
}

// ------------- methods independent of the key type ------------

// the constructor allocates a table with sz lists of records,
//     and remembers the size of the table
hashtable::hashtable(int sz)
{
   if (sz < 0) sz = 0;
   table =new recordPtr[sz];
   if (!table) tsize = 0;
   else tsize = sz;
   // initialize the random number generator
   srandom((unsigned int)(time(NULL)));
   //no lists so far so longest =0
   longest = 0;
	
}

// the destructor deallocates each record in each list
//     in the table
// and also computes the number of collisions in the 
//     hash table and the length of the largest chain   
hashtable::~hashtable()
{ 
   //j counts the linkedlist as we go in it
   int j=0;
   //print the length of the list in each table
   cout<<"The number of lists of a given length are as follows:"<<endl;
   if (table) {

	   //going through table
	   for (int i = 0; i < tsize; i++) {
		//reset counter j
		j=0;
		//check if table[i] is a linked list 
		if (table[i]!=NULL){
			// one is the length of linkedlist so far
			j++;
			//make a temp pointer for ease of pointer deletion 
			recordPtr temp=new record;
			temp=table[i];
			//go in while if we are not at end of the list yet
			while(temp->next!=NULL){
				//make a temp2 to delete the space that we are done with as we proceed to next 
				recordPtr temp2=new record;
				j++;
				temp2=temp;
				temp=temp2->next;
				//delete previous record in the list we dont need it and its information anymore
				delete temp2;
		        }	
			//output list number and its final size
		      	cout<<i<<": "<<j<<endl;
			//now delete final pointer
		      	delete temp;

	      }
	      //go in else if table is not a linked list
	      else{
		      //if table[i] is not a list output its list length is 0
		      cout<<i<<": "<<"0"<<endl;
	      }
      }
      //output the longest list 
      cout<<"Longest list length is "<<longest<<endl;
      delete table;
   }
}

// insert calls the hash function to find where to insert the 
//    record, and pushes the record into the back of that list
bool hashtable::insert(recordPtr r)
{
   //increment interies as insert is called
   entries++;  
   if (!r) return false;
   if (!table) return false;	
   int i;
   int pos = hash(r->key,i=0);
   //return false if position doesnt exist
   if ((pos < 0) || (pos >= tsize)) {
	   cout << "Hash generated position " << pos << " on " << r->key << endl;
	   return false;
   }
   //j is to count the linkedlist after all the inserts done since this is an insert list size it atleast 1
   int j=1;
   //use a temp pointer to not miss around with the actual table[pos]
   recordPtr temp=new record; 
   //check if table[pos] is empty 
   if(table[pos]==NULL){
	   //if empty create a list and insert r to its head
	   table[pos] =new record;
	   table[pos]=r;
   }
   else{
	 //table[pos] is not empty and is already a list 
	 //check if table[pos] just has one element 
	 if(table[pos]->next==NULL) {
		 // since list just has one element in head then insert r to head's next
		 table[pos]->next=r;
		 //j bellow says so far list size is two
		 j=2;
	 }
	 //if list at pos has more than just the head go in else
	 else{
		//since table[pos] has more than one element 
		//set table[pos] to temp and go through the list to find end to insert to it
		//j bellow says so far list size is two
		 j=2;	
		temp=table[pos]->next;
	 	while(temp->next!=NULL){
			
			temp=temp->next;
			j++;
			cout<<"this is j: "<<j<<endl;
	 	}
		//now that we know whats the end of the list insert r to it
		temp->next=r;
	 }
   }

   //now that we did the insert output which pos in table we are inserting to and where on that list
   cout << "inserting " << setw(2) << r->key << ":" << r->data;
   cout << " in hash row " << pos << " on "<< j<<"th of list. "<< endl;
   // if list we just added to is the longest, change longest to it
   if (j>longest) longest = j;
   //reset j
   j=0;
   return true;
}

// lookup calls the hash function to find which list should 
//    contain the record with the specified key,
//    then searches that list and returns the record found
// (or null if no matching record is found)
recordPtr hashtable::lookup(keytype k)
{

   if (!table)
   {
	   //if has nothing return NULL
	   return NULL;
   }

 
   //check pos for key
   int i;
   int pos = hash(k,i=0);
   if ((pos < 0) || (pos >= tsize)) return NULL;

   //again created a temp pointer to go through the linkedlist without risking changing the value in table[pos]
   recordPtr temp=new record;
   temp = table[pos];

   //go through list and see if key exists 
   while (temp->key != k) {
	   temp=temp->next;
   }
   //check if we got a key, if so return it
   if (temp->key == k){
	   return table[pos];
   }
   //return NULL if key isnt in table
   else{
	   return NULL;
   }
}


// the main routine generates a bunch of records with
//     random key values, makes note of what key values they had,
//     and inserts them in the hash table
// it then goes through its list of key values and tests the
//     hash table to see if it can find them
int main()
{
   int size = 0;
   int numtests = 0;
   string entry;

   // allow the user to select the size of the table
   cout << "How large a table would you like to work with?" << endl;
   cout << "(e.g. a prime number about the size of ";
   cout << "your planned number of data entries)" << endl;
   do {
      cin >> entry;
      if (atoi(entry.c_str()) < 1) {
         cout << entry << " is not a positive integer value, ";
         cout << endl << "please try again" << endl;
      } else size = atoi(entry.c_str());
   } while (size < 1);

   // allow the user to select the number of test records
   cout << "How many test values would you like to insert?" << endl;
   do {
      cin >> entry;
      if (atoi(entry.c_str()) < 1) {
         cout << entry << " is not a positive integer value, ";
         cout << endl << "please try again" << endl;
      } else numtests = atoi(entry.c_str());
   } while (numtests < 0 || numtests > size);

   // allocate the hash table, quit if it fails
   hashtable *H = new hashtable(size);
   if (H == NULL) {
      cout << "unable to allocate sufficient table space, sorry!" << endl;
      return 1;
   }

   // allocate space for the test records, quit if it fails
   keytype *keyvals = new keytype[size];
   if (keyvals == NULL) {
      cout << "unable to allocate sufficient test data, sorry!" << endl;
      delete H;
      return 2;
   }

   // create the desired number of test records,
   //    each with a random key,
   // remember their key values in the keyvals array,
   //    and insert them in the hash table
   cout << "Creating records with random keys and inserting in hash table" << endl;
   for (int i = 0; i < numtests; i++) {
       keyvals[i] = H->nextkey();
       record *r = new record;
       if (!r) continue;
       r->key = keyvals[i];
       r->data = i;
       H->insert(r);


   }

 
   // go through the list of remembered keys and try to
   //    retrieve each of them from the hash table
   cout << endl << "Looking for the records we created" << endl;
   recordPtr s = new record;
   for (int j = 0; j < numtests; j++) {
       s = H->lookup(keyvals[j]);

       if (s==NULL){
	       cout << "Could not find record " << keyvals[j] << endl;
       }
       else {
	       cout << setw(2) << s->key << ":" << s->data;
	       cout << " found successfully" << endl;
       }
   }


   // deallocate the hash table and the storage
   //    for remembered keys
   delete H;
   return 0;
}



