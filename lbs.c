#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include<hill.h>
int siz ;
int k ;

//we have K states
//look at all successors of each state (k * SIZE * SIZE-1) = k * 56
//implement a weighted probability distribution, so that the probability of choosing a state is proportional to fitness 28*numSuccessors

int answers[50][50] = {};
//answers[row] = column;
void printA(int array[])
{
    int i;
    for(i=0; i<siz-1; i++) printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",siz-1,array[siz-1]);
    printf("\n");
}
int getWt(int array[])
{
    int weight = 0;
    int queen;
    for(queen=0;queen<siz;queen++)
    {    //for each queen
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<siz;nextqueen++)
        {        //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen]))
            {   //if conflict
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
        if(getWt(answers[i]) == 0){
            printf("solution: ");
            printA(answers[i]);
            getch();
        }
    }
    for(i=0;i<k;i++) for(j=0;j<siz;j++) answers[i][j] = getRand(siz);     //fill K boards randomly
    //weighted prob arrays
    int weightProb[3][12*6*k]; //{kstate,row,column}
    /* kstate - which k is it from
     row - which row are we dealing with
     col - which col to switch to */
    int wpl = 0;
    for(state=0;state<k;state++)
    {   //for each state
        int row;
        for(row=0;row<siz;row++)
        {  //for each row
            int col;
            for(col=0;col<siz;col++){  //for each col
                if (answers[state][row] != col){   //not including current state
                    int origcol = answers[state][row];
                    answers[state][row] = col;  //change state
                    int w = getWt(answers[state]);
                    for(i=0;i<w;i++)
                    {
                        weightProb[0][wpl] = state;
                        weightProb[1][wpl] = row;
                        weightProb[2][wpl] = col;
                        wpl++;
                    }
                    answers[state][row] = origcol;
                }
            }
        }
    }
    for(i=0;i<k;i++)
    {
        int n = getRand(wpl);
        //          state k             row             col
        answers[weightProb[0][n]][weightProb[1][n]] = weightProb[2][n];
    }
    stochBeamSearch();
    
}

void lbs()
{
    srand((unsigned int)time(NULL));
    printf("\nEnter value of n:\n");
    scanf("%d",&siz);
    printf("\nEnter value of k:\n");
    scanf("%d",&k);
    for(int i=0;i<k;i++) for(int j=0;j<siz;j++) answers[i][j] = getRand(siz);
    stochBeamSearch();
    getch();
}