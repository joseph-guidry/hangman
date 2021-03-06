#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//
//  FUNCTIONS
//
#define MAX 50

int getGuess(char *guess);
int updateOutput(char *guess, char *answer, char *output);

void printAnswer(char *answer, char *output)
{
    printf("Answer: ");
    for (int x = 0; x < strlen(answer); x++)
    {
        
        printf("%c ", output[x]);
    }
    printf("\n\nEnter a letter or 'quit' to exit >  ");    
}

void printBanner(void)
{
    printf("%31s", "Welcome to Hangman\n");
    printf("%50s", "Guess a letter before time runs out!\n\n");
}
int evaluateGuess(char *answer, char *guess, char *output, int *wrong, int *win)
{
    if (getGuess(guess))    //Get character for guess
    {
        return 1;           // Quitting
    }
    
    if (updateOutput(guess, answer, output))
    {
        (*wrong)++;
        return 0;
    }
  
    if( strcmp(answer, output) == 0)
    {
        (*win)++;           
    }
    
    return 0;
}

int getGuess(char *guess)
{
    fgets(guess, MAX, stdin);
    guess[strlen(guess) - 1] = '\0'; //Take guess to allow user to quit.
    
    if (strcmp(guess, "quit") == 0)
    {
        printf("Quitting");
        return 1;
    }
    
    guess[1] = '\0';   //Take only the first character of the guess
    
    return 0;        
}
int updateOutput(char *guess, char *answer, char *output)
{
    int x, correct = 1;
    for (x = 0; x < strlen(answer); x++)
    {
        if (answer[x] == tolower(*guess))
            {
                output[x] = tolower(*guess);
                correct = 0;
            }
    }
    return correct;
}

