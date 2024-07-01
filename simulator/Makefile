main.out: complex_numbers.o
	gcc main.c complex_numbers.o -o main.out

complex_numbers.o: complex_numbers/complex_numbers.c complex_numbers/complex_numbers.h
	gcc -c complex_numbers/complex_numbers.c -o complex_numbers.o

clean:
	rm -f *.o *.out