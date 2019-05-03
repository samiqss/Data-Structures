// Sami Al-Qusus                     //
// Lab7 part 2 (csci260 viu)         //
// Nov 12, 2017                      //
// rbtree implementation             //
///////////////////////////////////////


#include "rbtree.h"

bool rbtree::isItLeft(node* x)
//checks if node is left of its parent
{
	if (x==NO_NODE || x->parent->left == NO_NODE) return false;
	if (x->parent->left==x) return true;
	else return false;
}

bool rbtree::isItRight(node* x)
//checks if node is right of its parent
{
	if (x==NO_NODE || x->parent->right == NO_NODE) return false;
	if (x->parent->right==x) return true;
	else return false;
}

bool rbtree::recoloring(node* x)
//checks if both and aunt and parent of new node are red and does recoloring
//returns bool value true if recoloring is done
{
	bool isRight= isItRight(x->parent);
	bool isLeft= isItLeft(x->parent);

	if(isRight)
	{
		if(x->parent->parent->left->red)
		{
			x->parent->red=BLACK;
                        x->parent->parent->left->red=BLACK;
			//only if grandparent is not root change its color because root has to stay black
			if(x->parent->parent!=root) x->parent->parent->red=RED_BOOL;
			return 1;
		}
	}

	if(isLeft)
	{
		if(x->parent->parent->right->red)
		{
			cout<<"doing this"<<endl;
			x->parent->red=BLACK;
			x->parent->parent->right->red=BLACK;
			//only if grandparent is not root change its color because root has to stay black
			if(x->parent->parent!=root) x->parent->parent->red=RED_BOOL;
			return 1;
		}
	}
	return 0;

}

bool rbtree::inLL(node* x)
//does left left case 
//returns bool value true if left left case is done
{
	bool isParentLeft= isItLeft(x->parent);
	bool ISxLeft= isItLeft(x);
	if(isParentLeft && ISxLeft)
	{
		if(x->parent->parent->right->red==BLACK)
		{
			rightRotate(x->parent->parent);
			x->parent->red=BLACK;
			x->parent->right->red=RED_BOOL;
			return 1;
		}
	}
	return 0;
}

bool rbtree::inRR(node* x)
//does right right case 
//returns bool value true if right right case is done
{
	bool isParentRight= isItRight(x->parent);
	bool ISxRight= isItRight(x);
	if(isParentRight && ISxRight)
	{
		if(x->parent->parent->left->red==BLACK)
		{
			leftRotate(x->parent->parent);
			x->parent->red=BLACK;
			x->parent->left->red=RED_BOOL;
			return 1;
		}
	}

	return 0;
}

bool rbtree::inLR(node* x)
//does left right case 
//returns bool value true if left right case is done
{
	bool isParentLeft= isItLeft(x->parent);
	bool ISxRight= isItRight(x);
	if(isParentLeft && ISxRight)
	{
		if(x->parent->parent->right->red==BLACK)
		{
			leftRotate(x->parent);
			inLL(x);
			return 1;
		}	
	}

	return 0;
}

bool rbtree::inRL(node* x)
//does left left case 
//returns bool value true if right left case is done
{
	bool isParentRight= isItRight(x->parent);
	bool ISxLeft= isItLeft(x);
	if(isParentRight && ISxLeft)
	{
		if(x->parent->parent->left->red==BLACK)
		{
			rightRotate(x->parent);
			inRR(x);
			return 1;
		}
	}

	return 0;
}

void rbtree::insertCheckFix(node* x)
//checks if tree needs to be fixed by checking case by case
//once a case is reached the fix is done by that function call 
{
	if(recoloring(x));
	else if(inLL(x));
	else if(inRR(x));
	else if(inLR(x));
	else if(inRL(x));
}

rbtree::rbtree()
{  
   NO_NODE = new node;
   NO_NODE->red= 0;
   NO_NODE->data=INVALID_STRING;
   root = NO_NODE;
}

rbtree::~rbtree()
{
   deallocate(root);
}

void rbtree::deallocate(node* &n)
// delete all nodes in the subtree rooted at n,
//    and set n to null
{
   if (n == NO_NODE) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NO_NODE; 
}

bool rbtree::insert(int k, string d, node* &n)
// insert a new node in the rbtree rooted at n and do fix if needed,
// returning true if successful, false otherwise
// If k is a duplicate of n->key, it will insert the duplicat
// into the left subtree of n
{
   // if we've found the end of a chain,
   //    insert the node here
   if (n == NO_NODE) {
   	n = new node;
	n->left = NO_NODE;
	n->right = NO_NODE;
	n->parent= NO_NODE;
	n->key = k;
	n->data = d;
	n->red=BLACK;
	insertCheckFix(n);
   	return 1;
   }

   if (k <= n->key){
   	if (n->left == NO_NODE) {
		n->left = new node;
         	n->left->left = NO_NODE;
        	n->left->right = NO_NODE;
		n->left->parent= n;
		n->left->key = k;
		n->left->data = d;
		n->left->red=1;
		insertCheckFix(n->left);
		return 1;	
   	}
	else return insert(k,d,n->left);
   }
   else {
   	if (n->right == NO_NODE) {
		n->right= new node;
		n->right->left = NO_NODE;
		n->right->right = NO_NODE;
		n->right->parent= n;
		n->right->key = k;
		n->right->data = d;
		n->right->red=1;
		insertCheckFix(n->right);
		return 1;
   	}
	else return insert(k,d,n->right);
   }

}

string rbtree::find(int k, node* n)
// Find a node with key k
// return the data associated with the first occurence of key k
// encountered.
{
     if (n == NO_NODE) return INVALID_STRING;
     if (k == n->key) return n->data;
     if (k > n->key) return find(k,n->right);
     else return find(k,n->left);
}

bool rbtree::deleteElement(int k, node* &n)
// if the subtree rooted at n contains a node whose key
//    matches k then remove it from the subtree, and return true,
//    otherwise return 
{
	if (n==NO_NODE) return 0;
	if (n->key == k) {
		if (n->left==NO_NODE) {
			node* temp = n->right;
        	        temp->parent = n->parent;
	 		delete n;
			n = temp;
			return 1;
		}
		if (n->right == NO_NODE) {
			node* temp = n->left;
        	        temp->parent = n->parent;
			delete n;
			n= temp;
			return 1;
		}
		node* victim = n->right;
		while (victim->left!=NO_NODE) {
			victim = victim->left;
		}
		swapElements(victim, n);
	 	if (victim == victim->parent->right) 
			victim->parent->right = victim->right;
		else victim->parent->left = victim->right;
		delete victim;
		return 1;
		}
	else if (k< n->key) return deleteElement(k,n->left);
	else return deleteElement(k,n->right);
}

void rbtree::print(node *n)
// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
{
   if (n == NO_NODE) return;
   print(n->left);
   cout << n->key << ":" << n->data << ":" << n->red  << endl;
   print(n->right);
}

void rbtree::debugprint(node *n)
// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
{
   string colstring[2] = {"B","R"};
   if (n == NO_NODE) return;
   cout << n->key << ":" << n->data << ":" << colstring[n->red]<<" (";
   if (n->left != NO_NODE) cout << n->left->key;
   else cout << "N";
   if (n->parent!=NO_NODE) cout << "<-left " << n->parent->key << " right->";
   else cout << "<-left N right->";
   if (n->right!= NO_NODE) cout << n->right->key;
   else cout << "N";
   cout << ") ";

   debugprint(n->left);
   debugprint(n->right);
}

void rbtree::swapElements(node* n, node* m)
{
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;
}

void rbtree::leftRotate(node* x)
//does left rotate on grandparent
//parent becomes grandparent
//grandparent becomes left child of parent
//grandparent takes on left child of parent as its right child
{

   if (x == NO_NODE) return; 
   if (x->right== NO_NODE) return;
   //keep track of original x
   node* xoriginal=x;
   //use temp pointer to not deallocatel non temp  pointers by mistake
   node* temp = x->right;
   x->right=temp->left;
   temp->left=x;
   temp->parent=x->parent;
   x->parent=temp;
   //give temp right child its parent right now which is temp and not what it pointed to before temp became its parent
   if(temp->right->parent!=NO_NODE) temp->right->parent=temp;
   //give x right child its parent right now which is x not what it pointed to before x became its parent
   if (x->right->parent!=NO_NODE) x->right->parent=x;
   //update x old parent children not be x but its new children  
   node* parenttemp = xoriginal->parent;
   if( parenttemp->right == xoriginal)
   {
	   parenttemp->right=temp;
   }
   else
   {
	   parenttemp->left=temp;
   }
}


void rbtree::testLeftRotate(int k, node* n)
{
     if (n == NO_NODE) return;
     if (k < n->key) testLeftRotate(k,n->left);
     else if (k > n->key) testLeftRotate(k,n->right);
     else  leftRotate(n);
}

void rbtree::rightRotate(node* x)
{
//does right rotate on x
////parent becomes grandparent
////grandparent becomes right child of parent
////grandparent takes on right child of parent as its left child
   if (x == NO_NODE) return;
   if (x->left== NO_NODE) return;
   //keep track of original x
   node* xoriginal=x;
   //use temp pointer to not deallocatel non temp  pointers by mistake
   node* temp = x->left;
   x->left=temp->right;
   temp->right=x;
   temp->parent=x->parent;
   x->parent=temp;
   //give temp right child its parent right now which is temp and not what it pointed to before temp became its parent
   if(temp->left->parent!=NO_NODE) temp->left->parent=temp;
   //give x right child its parent right now which is x not what it pointed to before x became its parent
   if (x->left->parent!=NO_NODE) x->left->parent=x;
   //update x old parent children not be x but its new children 
   node* parenttemp = xoriginal->parent;
   if( parenttemp->left == xoriginal)
   {
	   parenttemp->left=temp;
   }
   else
   {
	   parenttemp->right=temp;
   }
}


