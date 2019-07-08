all: bogoinsert

bogoinsert: main.o
	g++ -o bogoinsert main.o


main.o: main.cpp
	g++ -c -o main.o main.cpp

clean: 
	rm -f main.o
	rm -f bogoinsert