#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

struct stats {
    int wins;
    int loss;
    int guess;
    char name[10];
};

//
//  PROTOTYPES
//
void printStage(int s);

void getAnswer(char *filename, char *answer);

void printBanner(void);

void printAnswer(char *answer, char *output);

int evaluateGuess(char *answer, char *guess, char *output, int *wrong, int *win);

int getGuess(char *guess);

int updateOutput(char *guess, char *answer, char *output);

void getStats(struct stats *user);

void updateStats(struct stats *user);

