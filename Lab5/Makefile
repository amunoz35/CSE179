EXEC: MPI_simple
EXEC: MPI_ring
MPICC = mpicc

all :${EXEC}

MPI_simple: MPI_simple.c
	${MPICC} -o hello MPI_simple.c

MPI_ring: MPI_ring.c
	${MPICC} -o ring MPI_ring.c

clean:
	rm -rf *.exe
