all: ex1.o ex2.o
	gcc -o ex1 ex1.o
	gcc -o ex2 ex2.o
ex1.o: ex1.c ex1.h
	gcc -c ex1.c
ex2.o: ex2.c ex2.h
	gcc -c ex2.c
clean:
	rm -f *.o ex1 ex2	
