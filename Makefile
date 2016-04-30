all:
	gcc *.c *.h -lm -Wall -O3 --std=c11 -fopenmp
