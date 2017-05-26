#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hangman.h"

int main(int argc, char **argv)
{
    char gameAnswer[MAX];
    char outputAnswer[MAX];
    char usedChars[MAX];   
     
    struct stat user;
    
    if (argc != 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    getAnswer(argv[1], gameAnswer);
    printf("Answer: %s\nLength: %lu\n", gameAnswer, strlen(gameAnswer));
    
    getStats(&user);

    printf("%s \n", gameAnswer);

    for (int x = 0; x < MAX; x++)
    {
        *user.name = '\0';
    }

    strcpy(user.name, getenv("USER"));
    
    printf("Name: %s \nWins: %d\nLosses: %d\n", user.name, user.wins, user.loss);
    
    printBanner();
    printStage(0, usedChars);
    for (int x = 0; x < strlen(gameAnswer); x++)
        {
            outputAnswer[x] = '_';
        } 
    printAnswer(gameAnswer, outputAnswer);
    
    return 0;
}

