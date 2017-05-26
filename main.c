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
    
    if (argc != 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    //GET PREVIOUS GAME STATS from .hangout   fopen(.hangman, "w+")
    getStats(&currentuser);
    
    int x;
    
    printf("user: %s Wins: %d, Losses: %d \n", currentuser.name, currentuser.wins, currentuser.loss);
    
    while(1)
        {
        getAnswer(argv[1], gameAnswer);
        //Reset the output answer to all '_' characters
        for (x = 0; x < strlen(gameAnswer); x++)
        {
            outputAnswer[x] = '_';
        }
        outputAnswer[x] = '\0';
        
        while(0)
        {      
            system("clear");//&& system("cls");
            printBanner();
            printStage(wrong);
            
            printf("Answer: %s\nLength: %lu\n", gameAnswer, strlen(gameAnswer));
            printAnswer(gameAnswer, outputAnswer);
            
            if (evaluateGuess(gameAnswer, guess, outputAnswer, &wrong, &match) == 1)
            {
                printf("Update loss stats\n");
                currentuser.loss++;
                
                break;
            }
            printf("win: [%d] \n", match);
            if (match)
            {
                printf("You win!");
                currentuser.wins++;
                currentuser.guess += wrong;
                wrong = 0;
                
                break;
            }
            if (wrong == 6)
            {
                printf("You lost!\nThe answer was:  [%s]\n", gameAnswer);
                
                //printf("Update loss stats\n");
                currentuser.loss++;
                wrong = 0;
                break;
                
            }
            
        }
        //If user wins OR loses ask to play again.
        printf("Play again? Type 'yes' >  ");
        fgets(again, MAX, stdin);
        again[strlen(again) - 1] = '\0';
        printf("exit phrase: [%s] %d\n", again, strcmp(again, "yes"));
        if (strcmp(again, "yes") == 0)
        {
            printf("here on exit\n");
            match = 0;
            continue;
        }
        break;
    }
    printf("user: %s \nW: %d, L: %d \nGuess Average: %.2f\n", currentuser.name, currentuser.wins, 
           currentuser.loss, (currentuser.wins < 1) ? 0 : (float) currentuser.guess / currentuser.wins);
    //updateStats();
    
    return 0; 
}
void getStats(struct stat *user)
{
    //struct stat *temp = malloc(sizeof(struct stat));
    FILE *fp = fopen("hangman", "wb");

    if ( fp == NULL )
    {
        printf("Couldn't open .hangman file");
        exit(1);
    }
    
    if(fread(&temp, sizeof(struct stat), 1, fp) > 0)
    {
        printf("%d \n", user->wins);
        user = temp;
        return;
    }
    else
    {
        strcpy(user->name, getenv("USER"));
        user->wins = 0;
        user->loss = 0;
        user->guess = 0;
    }
    
    fclose(fp);
        
}
void updateStats(struct stat *user)
{
    FILE *fp = fopen("hangman", "wb+");
    
    if ( fp == NULL )
    {
        printf("Couldn't open .hangman file");
        exit(1);
    }
    
    
    fseek(fp, 0, 0);
    fwrite(user, sizeof(struct stat), 1, fp);
    fclose(fp);
    return;
    
}
