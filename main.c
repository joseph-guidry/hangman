#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "hangman.h"

int main(int argc, char **argv)
{
    int wrong = 0, match = 0; //win, loss;
    struct stat currentuser;
    
    char again[MAX];
    char guess[MAX];
    char gameAnswer[MAX];
    char outputAnswer[MAX];
    char usedGuess[MAX];
    
    if (argc != 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    //GET PREVIOUS GAME STATS from .hangout   fopen(.hangman, "w+")
    
    printf("user: %s Wins: %d, Losses: %d \n", currentuser.name, currentuser.wins, currentuser.loss);
    
    while(1)
        {
        getAnswer(argv[1], gameAnswer);
        for (int x = 0; x < strlen(gameAnswer); x++)
        {
            outputAnswer[x] = '_';
        }   
        while(1)
        {      
            system("clear");//&& system("cls");
            printBanner();
            printStage(wrong, usedGuess);
            if (wrong == 6)                 //REposition
            {
                printf("You lost\n");
                //loss++;
                break;
                
            }
            
            printf("Answer: %s\nLength: %lu\n", gameAnswer, strlen(gameAnswer));
            printAnswer(gameAnswer, outputAnswer);
            
            if (evaluateGuess(gameAnswer, guess, outputAnswer, usedGuess, &wrong, &match) == 2)
            {
                printf("Update loss stats\n");
                //loss++;
                
                break;
            }
            printf("win: [%d] \n", match);
            if (match)
            {
                //win++;
                
                break;
            }
                
            
        }
        //If user wins OR loses ask to play again.
        printf("Play again? Type 'yes' >  ");
        fgets(again, MAX, stdin);
        again[strlen(again) - 1] = '\0';
        
        if (strcmp(again, "yes") == 0)
        {
            match = 0;
            continue;
        }
        break;
    } 
    //updateStats();
    
    return 0; 
}
int evaluateGuess(char *answer, char *guess, char *output, char *used, int *wrong, int *win)
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
    
    //printf("Answer: [%s] Output: [%s] Guess: [%s]\n", answer, output, guess);
   // printf("compare: %d \n", strcmp(answer, output));
    
    if( strcmp(answer, output) == 0)
    {
        printf("You win!\n");
        //win++;
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
    //printf("x: [%d] \n", correct);
    return correct;
}
