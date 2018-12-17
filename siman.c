#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include <math.h>
#include "hill.h"

#define e 2.718281828459045 //double
int s;
int ans[100] = {};
void printArr(int array[])
{
    int i;
    for(i=0; i<s-1; i++) printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",s-1,array[s-1]);
    printf("\n");
}
int getWeigh(int array[])
{
    int weight = 0;
    int queen;
    for(queen=0;queen<s;queen++)
    {    //for each queen
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<s;nextqueen++)
        {        //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen]))
            {   //if conflict
                weight++;
            }
        }
    }
    return weight;
}
int getRandOne()
{
    return (rand()%1000)/1000;
}

void simulatedAnnealing(){
    int temp = 4000;
    int sch = .99;
    int k;
    int dw;
    int successor[s];
    for(k=0;k<1700000;k++)
    {  //roughly even distribution of "took to long" and solution with this k value
        temp *= sch;
        int i;
        for(i=0;i<s;i++) 
        successor[i] = ans[i];
        successor[rand()%s] = rand()%s;
        dw = getWeigh(successor) - getWeigh(ans);
        if(dw > 0 || getRandOne() < pow(e,-dw*temp))
        {
            for(i=0;i<s;i++) 
            ans[i] = successor[i];
            printArr(ans);
        }
        if(getWeigh(ans) == 0)
        {
            printf("solution: ");
            printArr(ans);
            getch();
        }
    }
    printf("took too long");
}

void siman()
{
    srand((unsigned int)time(NULL));
    int i;
    printf("\nEnter value of n:\n");
    scanf("%d",&s);
    for(i=0;i<s;i++) 
    ans[i] = rand()%s;
    printArr(ans);
    simulatedAnnealing();
    getch();;
}