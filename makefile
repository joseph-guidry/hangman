#
#	Makefile for Hangman Game
#


all : printStage

printStage: printStage.c
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o printStage printStage.c

clean: 
	rm printStage


