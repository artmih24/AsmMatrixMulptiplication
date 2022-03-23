all: main.o functions.o asmfunctions.o
	g++ main.o functions.o asmfunctions.o -o a.out

main.o: main.cpp
	g++ -c main.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

asmfunctions.o: asmfunctions.s
	g++ -c asmfunctions.s

clean:
	rm -rf *.o a.out