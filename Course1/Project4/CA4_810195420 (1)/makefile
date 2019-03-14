MainProgram: bill.o commands.o customer.o food.o main.o mystrlib.o restaurant.o strTokenizer.o
	g++ bill.o commands.o customer.o food.o main.o mystrlib.o restaurant.o strTokenizer.o -o MainProgram
bill.o: bill.cpp bill.h mystrlib.h
	g++ -c bill.cpp
commands.h: mystrlib.h restaurant.h strTokenizer.h customer.h food.h
commands.o: commands.cpp commands.h
	g++ -c commands.cpp
customer.h: bill.h
customer.o: customer.cpp customer.h strTokenizer.h mystrlib.h
	g++ -c customer.cpp
food.o: food.cpp food.h strTokenizer.h mystrlib.h
	g++ -c food.cpp
main.o: main.cpp commands.h restaurant.h strTokenizer.h customer.h food.h
	g++ -c main.cpp
mystrlib.o: mystrlib.cpp mystrlib.h
	g++ -c mystrlib.cpp
restaurant.h: food.h
restaurant.o: restaurant.cpp restaurant.h strTokenizer.h mystrlib.h
	g++ -c restaurant.cpp
strTokenizer.o: strTokenizer.cpp strTokenizer.h
	g++ -c strTokenizer.cpp
clean:
	rm *.o
