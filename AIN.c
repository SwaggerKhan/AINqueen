#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
int * GenRanState(int);
void hill(int);


int main()
{              
    int n,x;
    printf("\nEnter the value of N for N queens");
    scanf("%d",&n);
    printf("\n\n\t\tChoose algorithm for computation.\n1.Hill Climbing\n2.Simulated Annealing\n3.Local Beam Search\n");
    scanf("%d",&x);
    switch(x)
    {
        case 1: hill(n);
                break; 
    }
    getch();
    return 0;
}


int * GenRanState(int n)
{
    int z[50][50];
    for(int l=0;l<n;l++)
    {
        int i=rand()%n;
        z[l][i]=1;
    }
    return z;

}



void hill(int n)
{
    int *za;
    int *ax=GenRanState(n);
    int z[50][50];
    int cost=10;
    int h=0;
    int l,m,i,j;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(z[i][j]==1)
            { l=i+1;m=j+1;
                while(l<n||m<n)
                {
                    if(z[i][j]==z[l][j])
                    h+=1;
                    if(z[i][j]==z[l][m])
                    h+=1;
                    l++;
                    m++;
                }
                for(l=0;l<(i+j);l++)
                {
                    for(int m=0;m<(i+j);m++)
                    if(z[i][j]==z[l][m])
                    h+=1;
                }

            }
        }
    }
    cost=h;


   do 
    {
        GenRanState(n);
        hill(n);
    }   while(cost!=0);
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<n;j++)
        {
            if(z[i][j]!=1)
            {
                z[i][j]==0;
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("\t%d",z[i][j]);
        }
        printf("\n");
    }
}
