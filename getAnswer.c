#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 50

void getAnswer(char *filename, char *answer)
{
    FILE *fp;
    char temp[MAX];
    int wordNum, lc = 0;
    
    if( (fp = fopen(filename, "r")) == NULL)
    {
        printf("Could not open %s\n", filename);
        exit(2);
    }
    
    while( (fgets(temp, MAX, fp)) != NULL )
    {
            lc++;
    }
    
    srand(time(NULL));
    wordNum = rand() % (lc + 1);  
    //Generate rand num for line to select. between 0 and last line.
    printf("line number: [%d] wordNum: [%d]\n", lc, wordNum);
    lc = 0;

    fseek(fp, 0, 0);
    while( fgets(temp, MAX, fp))
    {
        lc++;
        if ((lc == wordNum)  && (sscanf(temp,"%s", answer)))
        {
            printf("[%s]: answer\n", answer);
            for( ; *answer; answer++)
            {
                *answer = tolower(*answer);
            }
            fclose(fp);
            return;
        }
    }
    
    fclose(fp);

    
    
}
