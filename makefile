all: p1 p2
p1: 
	gcc -o p1 FIFO-1.c
p2: 
	gcc -o p2 FIFO-2.c

