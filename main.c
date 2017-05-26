#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "hangman.h"

int main(int argc, char **argv)
{
    FILE *game;
    int x, wrong = 0, match = 0, num = 1; //win, loss;
    struct stats currentuser;
    
    char again[MAX];
    char guess[MAX];
    char gameAnswer[MAX];
    char outputAnswer[MAX];
    /*
    if (argc == 1)
    */
    if (argc == 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    /*
    if (argc == 3)
    {
        //get the 
    }
    */
    //Make .hangman file if it doesn't exist
    if( (game = fopen("hangman", "r")) == NULL )
    {
        printf("here if hangman does not exist\n");
        game = fopen("hangman", "w");
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
        printf("[%ld] position \n", ftell(game));
    }
    printf("skip making hangman\n");
    fclose(game);
    
    getStats(&currentuser);

    printf("[%s] \n", getenv("SHELL"));
    printf("Begining of game\nuser: %s \nW: %d, L: %d \nGuess Average: %.2f\n", currentuser.name,
             currentuser.wins, currentuser.loss, 
             (currentuser.wins < 1) ? 0 : (float) currentuser.guess / currentuser.wins);
             
    strcpy(currentuser.name, getenv("USER"));
    
    while(1)
        {
        getAnswer(argv[1], gameAnswer);
        //Reset the output answer to all '_' characters
        for (x = 0; x < strlen(gameAnswer); x++)
        {
            outputAnswer[x] = '_';
        }
        outputAnswer[x] = '\0';
        
        while(1)
        {      
            if (strstr(getenv("SHELL"), "bin/bash") ) //If running in BASH shell environment
            {
                system("clear");
            }
            
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
                printf("Current wins: %d", currentuser.wins);

                currentuser.guess += wrong;
                wrong = 0;
                
                break;
            }
            if (wrong == 6)
            {
                printf("You lost!\nThe answer was:  [%s]\n", gameAnswer);
                
                printf("Update loss stats: %d\n", currentuser.loss);
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
    printf("AFter game\nuser: %s \nW: %d, L: %d \nGuess Average: %.2f\n", currentuser.name,
             currentuser.wins, currentuser.loss, 
             (currentuser.wins < 1) ? 0 : (float) currentuser.guess / currentuser.wins);
             
             
    updateStats(&currentuser);
    return 0; 
}
void getStats(struct stats *user)
{
    FILE *fp;
    fp = fopen("hangman", "rb+");
    unsigned int num;

    if ( fp == NULL )
    {
        printf("Couldn't open .hangman file");
        exit(1);
    }
    fseek(fp, 0, 0);
    printf("Open hangman at: %ld \n", ftell(fp));
   
    printf("[%ld] position \n", ftell(fp));
    fread(&num, 1, sizeof(int), fp);
    printf("[%d]\n", num);
    printf("[%ld] position \n", ftell(fp));
    fread(user, sizeof(struct stats), 1, fp);
    printf("[%ld] position \n", ftell(fp));
    
    
    fclose(fp);
    
}
void updateStats(struct stats *user)
{   

    FILE *fp;
    fp = fopen("hangman", "r+");
    
    fseek(fp, 0, 0);
    printf("[%ld] position \n", ftell(fp));
    int num = 1;
    fwrite(&num, 1, sizeof(int), fp);
    printf("[%ld] position \n", ftell(fp));
    
    fwrite(user, 1 , sizeof(struct stats), fp);
    printf("[%ld] position \n", ftell(fp));
    fclose(fp);
    
    
}
