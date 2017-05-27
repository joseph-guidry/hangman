#
#
#

all: main

main: main.c printStage.o getAnswer.o getGuess.o 
	gcc -Wall -o hangman main.c printStage.o getAnswer.o getGuess.o 

clean:
	rm *
