#
#
#

all: main

main: main.c printStage.o getAnswer.o
	gcc -Wall -o main main.c printStage.o getAnswer.o

clean:
	rm *
