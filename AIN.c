#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include "hill.h"
#include "lbs.h"
#include "siman.h"
int main()
{              
    int n,x;
                printf("\n\n\t\tChoose algorithm for computation.\n1.Hill Climbing\n2.Simulated Annealing\n3.Local Beam Search\n");
                scanf("%d",&x);
                switch(x)
                {
                        case 1: hill();
                                break; 
                        case 2: siman();
                                break;
                        case 3: lbs();
                                break;
                }       
               
    getch();
    return 0;
}