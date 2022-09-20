q2: q2.o
	gcc -no-pie -o q2 q2.o
q2.o:q2.asm
	yasm -f elf64 -o q2.o q2.asm
