main.out: complex_numbers.o linear_algebra.o
	gcc main.c complex_numbers.o linear_algebra.o -o main.out

complex_numbers.o: complex_numbers/complex_numbers.c complex_numbers/complex_numbers.h
	gcc -c complex_numbers/complex_numbers.c -o complex_numbers.o

linear_algebra.o: linear_algebra/linear_algebra.c linear_algebra/linear_algebra.h
	gcc -c linear_algebra/linear_algebra.c -o linear_algebra.o

clean:
	rm -f *.o *.out