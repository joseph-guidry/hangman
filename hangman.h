#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//void printStage(int s, char *used);
void printBanner(void);
void getAnswer(char *filename, char *answer);


#define MAX 50

void getAnswer(char *filename, char *answer)
{
    FILE *fp;
    int wordNum, lc = 0;
    
    if( (fp = fopen(filename, "r")) == NULL)
    {
        printf("Could not open %s\n", filename);
        exit(2);
    }
    
    while( (fgets(answer, MAX, fp)) != NULL )
    {
            lc++;
    }
    
    srand(time(NULL));
    wordNum = rand() % lc;  
    //Generate rand num for line to select. between 0 and last line.
    
    lc = 0;
    fseek(fp, 0, 0);
    while( fgets(answer, MAX, fp))
    {
        lc++;
        if (lc == wordNum)
        {
            answer[strlen(answer) - 1 ] = '\0';
            break;
        }
    }
    
    fclose(fp);
}

void printStage(int wrong, char *used)
{
    char uBody[3] = " ";
    char lBody[3] = " ";
    
    //PRINT TOP BAR
    printf("\t");
    for (int x = 0; x < 20; x++)
    {
        printf("_");
    }
    printf("\n\t|/\t\t   |\n");
    printf("\t|\t\t   |\n");
    printf("\t|\t\t   %c\n",  (wrong >= 1) ? 'O' : '|');
    // Upper BODY
    if (wrong == 2)
    {
        strcpy(uBody, "/");
    } 
    else if (wrong == 3)
    {
        strcpy(uBody, "/|");
    }
    else if (wrong >= 4) 
    {
        strcpy(uBody, "/|\\");
    }
    printf("\t|\t\t  %s \n", uBody);
    // Lower BODY 
    if (wrong == 5)
    {
        strcpy(lBody, "/  ");
    }
    else if (wrong >= 6)
    {
        strcpy(lBody, "/ \\");
    }
    printf("\t|\t\t  %s \n", lBody);
    printf("\t|\t\t\n"); 
    printf("\t|\t\t\n");
    
    printf("    ____|");
    for(int x = 0; x < 25; x++)
    {
        printf("_");
    }

    printf("\n\nUsed: ");
    putchar('\n');
/*
    for (int x = 0; x < strlen(used); x++)
        printf("%c ", *(used + x));
        
    */
}
