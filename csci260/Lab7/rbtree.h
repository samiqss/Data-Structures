// Sami Al-Qusus                     //
// Lab7 part 2 (csci260 viu)         //
// Nov 12, 2017                      //
// rbtree implementation             //
///////////////////////////////////////

#include <string>
#include <iostream>
using namespace std;

const string INVALID_STRING="INVALID STRING";

const bool BLACK=0;
const bool RED_BOOL=1;
class rbtree{
   private:
      // we maintain a pointer to the root of the tree
      struct node {
            node *right, *left, *parent;
            string data;
            int key; 
	    bool red;
      } ;
      node *root;
      node *NO_NODE;
      

      // private, recursive routines
      // (used by the public methods)
      bool isItLeft(node* x);
      bool isItRight(node* x);
      bool recoloring(node* x);
      bool inLL(node* x);
      bool inRR(node* x);
      bool inLR(node* x);
      bool inRL(node* x);
      void insertCheckFix(node* x);
      void deallocate(node* &n);
      bool insert(int k, string d, node* &n);
      bool deleteElement(int k, node* &n);
      string find(int k, node* n);
      void leftRotate(node* n);
      void testLeftRotate(int k, node* n);
      void rightRotate(node* n);
      void print(node *n);
      void debugprint(node *n); 
      void swapElements(node* n, node* m);

   public:
      rbtree();
      ~rbtree();
      void display() { print(root); }
      void debug() { debugprint(root); }
      bool insert(int k, string d) {
           if (insert(k, d, root)) return true;
           else return false; }
      bool deleteElement(int k) {
           if (deleteElement(k, root)) return true;
           else return false; }
      string find( int k) { return(find(k, root)); }
      void testLeftRotate(int k) { testLeftRotate(k, root); } 
};

