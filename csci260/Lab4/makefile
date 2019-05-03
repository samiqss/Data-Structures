tile: mainTile.o  herringboneTile.o
	g++ -o tile mainTile.o herringboneTile.o

mainTile.o: mainTile.cpp  herringboneTile.h
	g++ -c mainTile.cpp

herringboneTile.o: herringboneTile.cpp  herringboneTile.h
	g++ -c herringboneTile.cpp

clean:
	rm mainTile.o herringboneTile.o 
