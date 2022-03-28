all: main.o functions.o asmfunctions.o MatrixMulFunctions.o MatrixMulSwitch.o
	g++ main.o functions.o asmfunctions.o MatrixMulFunctions.o MatrixMulSwitch.o -o a.out

main.o: main.cpp
	g++ -c -O0 main.cpp

functions.o: functions.cpp
	g++ -c -O0 functions.cpp

asmfunctions.o: asmfunctions.s
	g++ -c -O0 asmfunctions.s

MatrixMulFunctions.o: MatrixMulFunctions.cpp
	g++ -c -O0 MatrixMulFunctions.cpp

MatrixMulSwitch.o: MatrixMulSwitch.cpp
	g++ -c -O0 MatrixMulSwitch.cpp

clean:
	rm -rf *.o a.out