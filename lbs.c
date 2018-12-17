#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include "hill.h"
int siz ;
int k ;
int answer[50][50] = {};
clock_t st, stop;
void printA(int array[])
{
    int i;
    for(i=0; i<siz-1; i++) printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",siz-1,array[siz-1]);
    printf("\n");
}
void ConvertQueen(int array[])
{
	int i,m,p,q;
	int A[siz][siz];
	for(i=0;i<siz;i++)
	{
		for(m=0;m<siz;m++)
		{
			if(m==array[i])
			A[i][m]=1;
		else
            A[i][m]=0;
	    }
    }
	
	for (int p = 0; p < siz; p++) 
    	{ 
        	for (int q = 0; q < siz; q++) 
            printf(" %d ", A[p][q]); 
        	printf("\n"); 
    	} 
    	printf("\n"); 
} 
int getWt(int array[])
{
    int weight = 0;
    int queen;
    for(queen=0;queen<siz;queen++)
    {     
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<siz;nextqueen++)
        {        
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen]))
            {   
                weight++;
            }
        }
    }
    return weight;
}

void stochBeamSearch()
{
    int state,i,j;
    for(i=0;i<k;i++)
    {
        if(getWt(answer[i]) == 0){
            printf("solution: ");
            printA(answer[i]);
            ConvertQueen(answer[i]);
            stop=clock();
            cpu_time_used = ((double) (stop - st)) / CLOCKS_PER_SEC;
            printf("\nTime used:%lf\n",cpu_time_used);
            getch();
        }
    }
    for(i=0;i<k;i++) for(j=0;j<siz;j++) answer[i][j] = getRand(siz);     //fill K boards randomly
    int weightProb[3][(siz*(siz-1))*((siz*siz-1)/2)*k]; //{kstate,row,column}
    int wpl = 0;
    for(state=0;state<k;state++)
    {     
        int row;
        for(row=0;row<siz;row++)
        {   
            int col;
            for(col=0;col<siz;col++){   
                if (answer[state][row] != col){   //not including current state
                    int origcol = answer[state][row];
                    answer[state][row] = col;  //change state
                    int w = getWt(answer[state]);
                    for(i=0;i<w;i++)
                    {
                        weightProb[0][wpl] = state;
                        weightProb[1][wpl] = row;
                        weightProb[2][wpl] = col;
                        wpl++;
                    }
                    answer[state][row] = origcol;
                }
            }
        }
    }
    for(i=0;i<k;i++)
    {
        int n = getRand(wpl);
        //          state k             row             col
        answer[weightProb[0][n]][weightProb[1][n]] = weightProb[2][n];
        printA(answer[i]);
    }
    stochBeamSearch();
    
}

void lbs()
{
    st=clock();
    srand((unsigned int)time(NULL));
    printf("\nEnter value of n:\n");
    scanf("%d",&siz);
    printf("\nEnter value of k:\n");
    scanf("%d",&k);
    for(int i=0;i<k;i++) for(int j=0;j<siz;j++) answer[i][j] = getRand(siz);
    stochBeamSearch();
}