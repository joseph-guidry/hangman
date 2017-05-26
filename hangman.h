#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

void printStage(int s, char *used);
void printBanner(void);
void getAnswer(char *filename, char *answer);


struct stat {
    char name[MAX];
    int wins;
    int loss;
    int guess;
};
    
void getStats(struct stat *user);
void updateStats(struct stat *user);

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
