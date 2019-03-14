all: example1 gerdabServer.o web++.o

example1: web++.o gerdabServer.o examples/example1.cpp
		g++ -std=c++11 src/web++.o src/gerdabServer.o examples/example1.cpp -o example1.out

gerdabServer.o: src/gerdabServer.cpp
		g++ -std=c++11 -c src/gerdabServer.cpp -o src/gerdabServer.o

web++.o: src/web++.cpp
		g++ -std=c++11 -c src/web++.cpp -o src/web++.o
