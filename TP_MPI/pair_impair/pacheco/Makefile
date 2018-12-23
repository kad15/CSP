EXEC = pair_impair
MPICC = mpicc -Wall -W

all: ${EXEC}

${EXEC}: ${EXEC}.c
	${MPICC} -o ${EXEC} ${EXEC}.c

clean:
	rm -f ${EXEC}
