all:
	g++ -g alpha.cpp

test.o: test/test.cpp VariableNode.cpp
	gcc -c -g -o VariableNode.o VariableNode.cpp -I.
	gcc -c -g -o test.o test/test.cpp -Itest/vendor -I.

test: test.o
	gcc -g test.o VariableNode.o -o test.exe
	./test.exe

clean:
	rm -rf *.out *.exe *.o
