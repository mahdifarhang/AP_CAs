all:main.o image.o matrix.o row.o StringTokenizer.o
	g++ main.o image.o matrix.o row.o StringTokenizer.o -o PROGRAM
main.o:main.cpp image.h matrix.h row.h
	g++ -c main.cpp
image.h:matrix.h bitmap_image.h error.h
image.o:image.cpp image.h
	g++ -c image.cpp
matrix.h:row.h error.h
matrix.o:matrix.cpp matrix.h
	g++ -c matrix.cpp 
row.h:error.h
row.o:row.cpp row.h StringTokenizer.h
	g++ -c row.cpp
StringTokenizer.o:StringTokenizer.cpp StringTokenizer.h
	g++ -c StringTokenizer.cpp
clean:
	rm *.o