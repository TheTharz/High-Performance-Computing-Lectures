mpicc test.c -o test.o
mpirun --allow-run-as-root -np 4 ./test.o

allow root to run openmpi
export OMPI_ALLOW_RUN_AS_ROOT=1
export OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

mpirun -np 4 ./test.o
