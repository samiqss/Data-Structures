
testapp:	testapp.o graph.o unionfindQU.o
	g++ -o testapp testapp.o graph.o unionfindQU.o

testapp.o:	graph.h testapp.cpp
	g++ -c testapp.cpp


graph.o:	graph.h unionfind.h graph.cpp
	g++ -c graph.cpp


