EXEC = tpi
MPICC = mpicc -W -Wall

all: ${EXEC}

${EXEC}: ${EXEC}.c
	${MPICC} -o ${EXEC} ${EXEC}.c

clean:
	rm -f ${EXEC}
