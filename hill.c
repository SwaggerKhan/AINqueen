#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>
int SIZE;
int answers[100] = {};
int count = 0;

int length(int array[])
{
    int i=0;
    while(array[i] != -1) i++;
    return i;
}

int getRand(int mod)
{
    int z;
    z= rand() % mod;
    return z;
}

void printArray(int array[])
{
    int i;
    for(i=0; i<SIZE-1; i++)
    printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",SIZE-1,array[SIZE-1]);
    printf("\n");
}

int isValid(int array[], int curRow, int curCol)
{
    int i;
    if(length(array))
    {
        for(i=0;i<length(array);i++) if(i==curRow || array[i]==curCol || abs(i-curRow)==abs(array[i]-curCol)) return 0;
        return 1;
    } 
    else return 1;
    return 0;
}

int getWeight(int array[])
{
    int weight = 0;
    int queen;
    for(queen=0;queen<SIZE;queen++)
    {     
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<SIZE;nextqueen++)
        {         
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen]))
            {    
                weight++;
            }
        }
    }
    return weight;
}

void hillClimbing(int array[])
{
    int weight = getWeight(array);
    if (weight == 0)
    {
        printf("\n\nsolution: ");
        printArray(array);
        printf("count: %i\n",count);
        getch();
    }
     else 
    {
        int nextrow[] = {-1};
        int nextcol[] = {-1};
        int nextweight = weight;
        int queen;
        for(queen=0;queen<SIZE;queen++)
        {                             
            int origcol = array[queen];                                   
            int validcol;                                                                         
            for(validcol = 0; validcol<SIZE;validcol++)
            {            
                if(validcol != origcol)
                {                           
                    array[queen] = validcol;                       
                    int newweight = getWeight(array);                
                    if(newweight < nextweight)
                    {                     
                        int i;
                        for(i=0;i<length(nextrow);i++)
                        {             
                            nextrow[i] = (int)NULL;
                            nextcol[i] = (int)NULL;
                        }
                        nextrow[0] = queen;
                        nextrow[1] = -1;                 
                        nextcol[0] = validcol;
                        nextcol[1] = -1;
                        nextweight = newweight;
                        count++;
                        printArray(array);
                        hillClimbing(array);
                    } 
                    else if (newweight == nextweight)
                    {
                        int len = length(nextrow);
                        nextrow[len] = queen;
                        nextrow[len+1] = -1;
                        nextcol[len] = validcol;
                        nextcol[len+1] = -1;
                    }
                    
                }
            }
            array[queen] = origcol;
        }
         
        if (nextcol[0] != -1 && nextrow[0] != -1)
        {           
            int i;
            for(i=0;i<length(nextrow);i++)
            {                  
                array[nextrow[i]] = nextcol[i];              
                count++;                                     
                printf("count: %i\n",count);
                printArray(array);
                hillClimbing(array);                         
                count--;                                     
            }
        } 
        else
        {
            printf("local max reached. retrying\n");
            int i;
            for(i=0;i<SIZE;i++) 
            answers[i] = getRand(SIZE);
            printArray(answers);
            hillClimbing(answers);
        }
    }
}

void hill()
{
    srand((unsigned int)time(NULL));  
    int i;
    printf("\nEnter value of n:\n");
    scanf("%d",&SIZE);
    for(i=0;i<SIZE;i++)
    answers[i] = getRand(SIZE);
    printf("running hill climbing with array: ");
    printArray(answers);
    hillClimbing(answers);
}