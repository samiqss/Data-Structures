
testappQU:	testappUF.o unionfindQU.o
	g++ -o testappQU testappUF.o unionfindQU.o

testappUF.o:	unionfind.h testappUF.cpp
	g++ -c testappUF.cpp

unionfindQU.o:	unionfind.h unionfindQU.cpp
	g++ -c unionfindQU.cpp

