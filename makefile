all: main.o functions.o asmfunctions.o
	g++ main.o functions.o asmfunctions.o -o a.out

main.o: main.cpp
	g++ -c -O0 main.cpp

functions.o: functions.cpp
	g++ -c -O0 functions.cpp

asmfunctions.o: asmfunctions.s
	g++ -c -O0 asmfunctions.s

clean:
	rm -rf *.o a.out