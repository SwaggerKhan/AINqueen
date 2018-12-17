#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include <math.h>
#include "hill.h"

#define e 2.718281828459045  
int s;
int ans[100] = {};
clock_t begin, ter;
void printArr(int array[])
{
    int i;
    for(i=0; i<s-1; i++) 
    printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",s-1,array[s-1]);
    printf("\n");
}
void ConvertQ(int array[])
{
	int i,m,p,q;
	int A[s][s];
	for(i=0;i<s;i++)
	{
		for(m=0;m<s;m++)
		{
			if(m==array[i])
			A[i][m]=1;
		else
            A[i][m]=0;
	    }
    }
	
	for (int p = 0; p < s; p++) 
    	{ 
        	for (int q = 0; q < s; q++) 
            printf(" %d ", A[p][q]); 
        	printf("\n"); 
    	} 
    	printf("\n"); 
} 
int getWeigh(int array[])
{
    int weight = 0;
    int queen;
    for(queen=0;queen<s;queen++)
    {     
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<s;nextqueen++)
        {         
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen]))
            {    
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
    {   
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
            ConvertQ(ans);
            ter=clock();
            cpu_time_used = ((double) (ter - begin)) / CLOCKS_PER_SEC;
            printf("\nTime used:%lf\n",cpu_time_used);
            getch();
        }
    }
    printf("took too long");
}

void siman()
{
    begin=clock();
    srand((unsigned int)time(NULL));
    int i;
    printf("\nEnter value of n:\n");
    scanf("%d",&s);
    for(i=0;i<s;i++) 
    ans[i] = rand()%s;
    printArr(ans);
    simulatedAnnealing();
}