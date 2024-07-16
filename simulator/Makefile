main.out: main.c complex_numbers.o linear_algebra.o smart_allocation.o
	gcc main.c complex_numbers.o linear_algebra.o smart_allocation.o -o main.out -lm

complex_numbers.o: complex_numbers/complex_numbers.c complex_numbers/complex_numbers.h
	gcc -c complex_numbers/complex_numbers.c -o complex_numbers.o

linear_algebra.o: linear_algebra/linear_algebra.c linear_algebra/linear_algebra.h
	gcc -c linear_algebra/linear_algebra.c -o linear_algebra.o

smart_allocation.o: smart_allocation/smart_allocation.c smart_allocation/smart_allocation.h
	gcc -c smart_allocation/smart_allocation.c -o smart_allocation.o

clean:
	rm -f *.o *.out