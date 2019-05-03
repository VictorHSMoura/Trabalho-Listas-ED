trabalho: main.o lista.o
	gcc main.o lista.o -o trab.exe
	make clean
	clear

main.o: main.c
	gcc -c main.c

lista.o: lista.c lista.h
	gcc -c lista.c

clean:
	rm *.o
