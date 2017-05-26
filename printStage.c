#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printStage(int wrong)
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

    putchar('\n');
}
