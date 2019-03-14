MainProgram: main.o Bignum.o
	g++ main.o Bignum.o -o MainProgram
main.o: main.cpp bignum.h
	g++ -c main.cpp
bignum.h:
bignum.o: bignum.cpp bignum.h
	g++ -c bignum.cpp
