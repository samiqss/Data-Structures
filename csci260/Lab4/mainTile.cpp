/**********************************************************/
/*****        Lab 3  mainTile ****************************/
/*****        CSCI 260         ****************************/
/*****        Sept 25 2017       ****************************/
/**********************************************************/
#include "herringboneTile.h"
#include <iostream>
#include <cstdlib>    // atoi()
using namespace std;


int main(int argc, char *argv[]) {

   int missrow, misscol,k;
   if (argc < 4) {
      cout << "Enter the power k, making a chessboard of dimensions 2^k x 2^k: ";
      cin >> k;
      cout << "Enter the row and column of the missing square, seperated by a space: ";
      cin >> missrow >> misscol;
   }
   else {
      k= atoi(argv[1]);
      missrow = atoi(argv[2]);
      misscol = atoi(argv[3]);
   }

  // initialize board
  herringboneTile b(k,missrow,misscol);
  b.printBoard();
}
  

