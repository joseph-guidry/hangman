#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hangman.h"


struct stat {
    char name[MAX];
    int wins;
    int loss;
    int guess;
};
    
void getStats(struct stat *user);
void updateStats(struct stat *user);

int main(int argc, char **argv)
{
    char gameAnswer[MAX];
    char usedChars[MAX];   
     
    struct stat user;
    
    if (argc != 2)
    {
        printf("%s: invalid number of arguements\n", argv[0]);
        exit(1);
    }
    getAnswer(argv[1], gameAnswer);
    getStats(&user);

    printf("%s \n", gameAnswer);

    for (int x = 0; x < MAX; x++)
    {
        *user.name = '\0';
    }

    strcpy(user.name, getenv("USER"));
    
    printf("Name: %s \nWins: %d\nLosses: %d\n", user.name, user.wins, user.loss);
    
    
    printStage(0, usedChars);
    
    return 0;
}

void getStats(struct stat *user)
{
    struct stat *temp = malloc(sizeof(struct stat));
    FILE *fp;

    if ( (fp = fopen("hangman", "wb")) == NULL )
    {
        printf("Couldn't open .hangman file");
        exit(1);
    }
    
    fread(temp, sizeof(struct stat), 1, fp);
        fclose(fp);
        
    user = temp;
}
void updateStats(struct stat *user)
{
    FILE *fp = fopen("hangman", "wb");
    
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
