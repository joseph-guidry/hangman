#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "hangman.h"

void checkAnswer(char *filename, char *answer);

int main(int argc, char **argv)
{
    FILE *game;
    int x, wrong = 0, match = 0, num = 1; // nonAlpha = 1; 
    struct stats currentuser;
    
    char again[MAX];
    char guess[MAX];
    char gameAnswer[MAX];
    char outputAnswer[MAX];
    char wordfilename[MAX];
    
    if (argc == 1)
    {
        strcpy(wordfilename, getenv("HOME"));
        strcat(wordfilename, "/.words");
    }
    else if (argc > 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    else
    {
        strcpy(wordfilename, argv[1]);
    }
   
    //Make .hangman file if it doesn't exist
    if( (game = fopen(".hangman", "r")) == NULL )
    {
        game = fopen(".hangman", "w");
        if (game == NULL)
        {
            exit(1);
        }
        struct stats user;
        fwrite(&num, 1, sizeof(int), game);
        strcpy(user.name, "NEWUSER");
        user.wins = 0;
        user.loss = 0;
        user.guess = 0;
        fwrite(&user, 1 , sizeof(struct stats), game);
    }
    fclose(game);
    
    getStats(&currentuser);

    strcpy(currentuser.name, getenv("USER"));
    
    while(1)
        {
        checkAnswer(wordfilename, gameAnswer);
        
        //Reset the output answer to all '_' characters
        for (x = 0; x < strlen(gameAnswer); x++)
        {
            outputAnswer[x] = '_';
        }
        outputAnswer[x] = '\0';
        if (strstr(getenv("SHELL"), "bin/bash") ) //If running in BASH shell environment
        {
            system("clear");
        }
        
        printBanner();
        printStage(wrong);
        
        while(1)
        {      
            //printf("Answer: %s\nLength: %lu\n", gameAnswer, strlen(gameAnswer));
            printAnswer(gameAnswer, outputAnswer);
            
            if (evaluateGuess(gameAnswer, guess, outputAnswer, &wrong, &match) == 1)
            {
                printf("\nUpdate loss stats\n");
                currentuser.loss++;
                
                break;
            }
            if (match)
            {
                printf("You win!\nThe answer was:  [%s]\n", gameAnswer);
                currentuser.wins++;
                printf("Total wins: %d\n", currentuser.wins);

                currentuser.guess += wrong;
                wrong = 0;
                break;
            }
            
            if (strstr(getenv("SHELL"), "bin/bash") ) //If running in BASH shell environment
            {
                system("clear");
            }
            printBanner();
            printStage(wrong);
            if (wrong == 6)
            {
                printf("You lost!\nThe answer was:  [%s]\n", gameAnswer);
                currentuser.loss++;
                wrong = 0;

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
    
    //Print stats for current user.
    printf("\nUser: %s \nW: %d, L: %d \nGuess Average: %.2f\n", currentuser.name,
             currentuser.wins, currentuser.loss, 
             (currentuser.wins < 1) ? 0 : (float) currentuser.guess / currentuser.wins);
             
             
    updateStats(&currentuser);
    return 0; 
}

void getStats(struct stats *user)
{
    FILE *fp;
    fp = fopen(".hangman", "rb+");
    unsigned int num;

    if ( fp == NULL )
    {
        printf("Couldn't open .hangman file");
        exit(1);
    }
    fseek(fp, 0, 0);
   
    fread(&num, 1, sizeof(int), fp);
    fread(user, sizeof(struct stats), 1, fp);
    
    
    fclose(fp);
    
}
void updateStats(struct stats *user)
{   

    FILE *fp;
    fp = fopen(".hangman", "r+");
    
    fseek(fp, 0, 0);
    int num = 1;
    fwrite(&num, 1, sizeof(int), fp);
    fwrite(user, 1 , sizeof(struct stats), fp);
    fclose(fp);
    
    
}
