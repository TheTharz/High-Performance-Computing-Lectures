mpicc test.c -o test.o
mpirun --allow-run-as-root -np 4 ./test.o
