/*  Code to implement a Binary Min Heap using an array  */
/*  Code obtained from sanfoundry.com; amended by G. Pruesse  */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;
/* * Class Declaration */

template <class ElementType>
class BinaryHeap
{
   private:
      vector <ElementType> heap;
      int left(int parent);
      int right(int parent);
      int parent(int child);
      void heapifyup(int index);
      void heapifydown(int index);
   public:
      BinaryHeap() {}
      void Insert(ElementType element);
      void DeleteMin();
      ElementType ExtractMin();
      void MakeHeap(vector<ElementType> vals);
      //void DisplayHeap(void (*f)(ElementType));
      int Size();
};

/*
* Return Heap Size
*/
template <class ElementType>
int BinaryHeap<ElementType>::Size()
{
   return heap.size();
}

/*
* Insert Element into a Heap
*/
template <class ElementType>
void BinaryHeap<ElementType>::Insert(ElementType element)
{
   heap.push_back(element);
   heapifyup(heap.size() -1);
}
/*
* Delete Minimum Element
*/
template <class ElementType>
void BinaryHeap<ElementType>::DeleteMin()
{
   if (heap.size() == 0) {
      cout<<"Heap is Empty"<<endl;
      return;
      }

   heap[0] = heap.at(heap.size() - 1);
   heap.pop_back();
   heapifydown(0);
   cout<<"Element Deleted"<<endl;
}

/*
* Extract Minimum Element
*/
template <class ElementType>
ElementType BinaryHeap<ElementType>::ExtractMin()
{
   if (heap.size() == 0) 
      return -1;
   else
      return heap.front();
}

/*
* Make Heap from unordered vector of elements
*/
template <class ElementType>
void BinaryHeap<ElementType>::MakeHeap(vector<ElementType> vals)
{
   heap = vals;
   for (int i=heap.size()/2; i>=0; i--)
      heapifydown(i);
      
}

/*
* Display Heap
*
template <class ElementType>
void BinaryHeap<ElementType>::DisplayHeap(void (*printElement)(ElementType) )
{
   vector<ElementType>::iterator pos = heap.begin();
   cout<<"Heap -->  ";
   while (pos != heap.end()) {
      printElement(&pos);
      pos++;
      }
   cout<<endl;
}

/*
* Return Left Child
*/
template <class ElementType>
int BinaryHeap<ElementType>::left(int parent)
{
   int l = 2 * parent + 1;
   if (l < heap.size())
      return l;
   else
      return -1;
}

/*
* Return Right Child
*/
template <class ElementType>
int BinaryHeap<ElementType>::right(int parent)
{
   int r = 2 * parent + 2;
   if (r < heap.size())
      return r;
   else
      return -1;
}

/*
* Return Parent
*/
template <class ElementType>
int BinaryHeap<ElementType>::parent(int child)
{
   int p = (child - 1)/2;
   if (child == 0)
      return -1;
   else
      return p;
}

/*
* Heapify- Maintain Heap Structure bottom up
*/
template <class ElementType>
void BinaryHeap<ElementType>::heapifyup(int in)
{
   if (in >= 0 && parent(in) >= 0 && heap[parent(in)] > heap[in]) {
      ElementType temp = heap[in];
      heap[in] = heap[parent(in)];
      heap[parent(in)] = temp;
      heapifyup(parent(in));
      }
}

/*
* Heapify- Maintain Heap Structure top down
*/
template <class ElementType>
void BinaryHeap<ElementType>::heapifydown(int in)
{

   int child = left(in);
   int child1 = right(in);
   if (child >= 0 && child1 >= 0 && heap[child] > heap[child1]) {
      child = child1;
      }
   if (child > 0) {
      ElementType temp = heap[in];
      heap[in] = heap[child];
      heap[child] = temp;
      heapifydown(child);
      }
}

/*
* testHeap Contains Menu.  Rename it main and this file is complete 
* and self-contained.
*
void printInt(int x)
{
   cout << x <<" ";
}
int main()
{
   BinaryHeap<int> h;
   while (1)
   {
    cout<<"------------------"<<endl;
    cout<<"Operations on Heap"<<endl;
    cout<<"------------------"<<endl;
    cout<<"[I] Insert Element"<<endl;
    cout<<"[D] Delete Minimum Element"<<endl;
    cout<<"[E] Extract Minimum Element"<<endl;
    cout<<"[M] Make a Heap from a series of integers"<<endl;
    cout<<"[P] Print Heap"<<endl;
    cout<<"[Q] Quit"<<endl;
    int element;
    char choice;
    vector<int> values;
    cout<<"Enter your choice: ";
    cin>>choice;
    choice=toupper(choice);
    switch(choice)
    {
     case 'I':
      cout<<"Enter the element to be inserted: ";
      cin>>element;
      h.Insert(element);
      break;
     case 'D':
      h.DeleteMin();
      break;
     case 'E':
      cout<<"Minimum Element: ";
      if (h.ExtractMin() == -1)
      {
       cout<<"Heap is Empty"<<endl;
      }
      else
       cout<<"Minimum Element:  "<<h.ExtractMin()<<endl;
      break;
     case 'M':
      cout<<"The old heap will be overwritten.\n";
      cout<<"Enter a sequence of positive integers, with -1 marking end of input: \n";
      cin>>element;
      while (element != -1)
      {
        values.push_back(element);
        cin>>element;
      }
      h.MakeHeap(values);
      break;
     case 'P':
      cout<<"Displaying elements of Heap:  ";
      //h.DisplayHeap(printInt);
      break;
     case 'Q':
      exit(1);
     default:
      cout<<"Enter Correct Choice: ";
      cin>>choice;
      cout<<"end"<<endl;
    }
   }
   return 0;
}
/*
                                  ------------------
                                  Operations on Heap
                                  ------------------
                                  1.Insert Element
                                  2.Delete Minimum Element
                                  3.Extract Minimum Element
                                  4.Print Heap
                                  5.Exit
                                  Enter your choice: 
                                  Enter the element to be inserted: 
*/
