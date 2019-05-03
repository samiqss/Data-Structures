
testappUF:	testappUF.o unionfind.o
	g++ -o testappUF testappUF.o unionfind.o

testapp.o:	unionfind.h testappUF.cpp
	g++ -c testapp.cpp

unionfind.o:	unionfind.h unionfind.cpp
	g++ -c unionfind.cpp
