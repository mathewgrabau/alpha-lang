STD=-std=c++11
CC=g++
TEST_INCLUDE=test/vendor/catch/single_include

all:
	g++ -g alpha.cpp

test.o: test/test.cpp VariableNode.cpp
	$(CC) -c -g $(STD) -o VariableNode.o VariableNode.cpp -I.
	$(CC) -c -g $(STD) -o test.o test/test.cpp -I$(TEST_INCLUDE) -I.

test: test.o
	$(CC) -g $(STD) test.o VariableNode.o -o test.exe
	./test.exe

clean:
	rm -rf *.out *.exe *.o
