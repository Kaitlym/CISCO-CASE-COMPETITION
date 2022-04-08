all: gp.o
	g++ main.cpp -o gp

gp.o: main.cpp
	g++ -g -Wall -c main.cpp
