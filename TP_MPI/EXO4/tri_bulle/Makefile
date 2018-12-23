EXEC = bulle
MPICC = mpicc

all: ${EXEC}

${EXEC}: ${EXEC}.c
	${MPICC} -o ${EXEC} ${EXEC}.c

clean:
	rm -f ${EXEC}
