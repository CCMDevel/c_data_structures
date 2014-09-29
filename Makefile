HEADERS = Array.h examples.h Heap.h

default: main

main: 
	gcc -o0 -g3 -Wall -c -o ./Debug/ArrayInteger.o ArrayInteger.c
	gcc -o0 -g3 -Wall -c -o ./Debug/main.o main.c
	gcc -o0 -g3 -Wall -c -o ./Debug/Heap.o Heap.c
	gcc -o0 -g3 -Wall -c -o ./Debug/examples.o examples.c
	gcc -o c_data_structures.exe ./Debug/main.o ./Debug/examples.o ./Debug/Heap.o ./Debug/ArrayInteger.o

clean:
	-rm -f ./Debug/main.o
	-rm -f ./Debug/examples.o
	-rm -f ./Debug/Heap.o
	-rm -f ./Debug/ArrayInteger.o
	-rm -f c_data_structures.exe


