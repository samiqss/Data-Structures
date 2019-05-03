//herringboneTile.cpp 
//Implementation provided by [Sami Al-Qusus]
//Date: September 29,2017
//Lab3
//

#include "herringboneTile.h"

herringboneTile::herringboneTile(int dim, int m1, int m2)
{
	missR=m1;
	missC=m2;
	next= 0;
	int k = dim;
	int dimen = pow(2, k);
	numRows = dimen;
	numCols = dimen;
	board = new char*[numRows];
	for(int i=0; i<numRows;i++){
		board[i]= new int[numCols];
		//board is now a numRows x numCols array
	}
	for(int i=0; i<numRows; i++){
		for(int j=0; j<numCols; j++){
			board[i][j]=1;
		}
	}
	board[missR][missC]=0;

}

     
void herringboneTile::tile(int r,int c, int k, int m1, int m2)
{
	int tempq;
	tempq= k/2;
	q1=0;
	q2c=(pow(2, tempq))+1;
	q3r=q2c;
	q4=q3r;


}


herringboneTile::~herringboneTile(void)
{
	for(int i=0; i< numRows; i++){
		delete[] board[i];
	}
	delete[] board;
}

void herringboneTile::printBoard()
{
	for(int i=0; i<numRows; i++){
		for(int j=0; j<numCols; j++){
			cout << board[i][j];
		}
		cout << endl;
	}
}

void herringboneTile::tile(int r,int c, int k, int m1, int m2)
{



}
