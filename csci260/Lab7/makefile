
testapp:	testapp.o rbtree.o
	g++ -g -o testapp testapp.o rbtree.o

testapp.o:	rbtree.h testapp.cpp
	g++ -g -c testapp.cpp

bst.o:	bst.h rbtree.cpp
	g++ -g  -c rbtree.cpp

