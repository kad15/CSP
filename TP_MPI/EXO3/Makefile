EXEC = mpi_exo3
MPICC = mpicc

all: ${EXEC}

${EXEC}: ${EXEC}.c
	${MPICC} -o ${EXEC} ${EXEC}.c

clean:
	rm -f ${EXEC}
