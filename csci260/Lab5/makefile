
testapp:	testapp.o ExpressList.o
	g++ -o testapp testapp.o ExpressList.o

testapp.o:	ExpressList.h testapp.cpp
	g++ -c testapp.cpp

ExpressList.o:	ExpressList.h ExpressList.cpp
	g++ -c ExpressList.cpp
