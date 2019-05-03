#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;


int main()
{
   int i;
   srand(time(NULL));
   for (int j=1; j<10; j++)
      cout << rand()%2 << endl;
}
