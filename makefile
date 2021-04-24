all: functions main compile clean

compile: functions.o main.o
	g++ -o main main.o functions.o

functions: 
	g++ -c functions.cpp

main: 
	g++ -c main.cpp

clean: main.o functions.o
	rm *.o