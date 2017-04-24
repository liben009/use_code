#include <stdio.h>
#include <stdlib.h>

#define M 6
#define N 7
#define PASS 1
#define BLOCK 0
#define YES 1
#define NO 0

void PathFinding(int i, int j, int endi, int endj, int count);
void GetCurLeastPath();
void PrintLeastPath(int starti, int startj, int endi, int endj);
int SearchLeastPath(int starti, int startj, int endi, int endj);


int path[M][N] =
{   
	 1, 1, 1, 1, 1, 1, 1, 
	 1, 0, 1, 0, 1, 0, 1, 
	 1, 1, 1, 1, 1, 1, 1, 
	 1, 1, 1, 0, 1, 1, 1, 
	 1, 0, 1, 0, 1, 0, 1, 
	 1, 1, 1, 1, 1, 1, 1
};

int least_path[M][N] = {0};
int path_thr[M][N] = {0};
static int least = 100;

void PathFinding(int i, int j,int endi, int endj, int count)
{
	if (path[i][j] == 1)
	{
		if ( i == endi && j == endj)
		{
			if (count < least)
			{
				path_thr[i][j] = YES;
				GetCurLeastPath();
				path_thr[i][j] = NO;
				least = count;
			}
			return;
		}
		path[i][j] = BLOCK;
		path_thr[i][j] = YES;

		//if(i-1>=0)
		//   PathFinding(i-1, j, endi, endj, count + 1);
		//if(j+1<N)
		//   PathFinding(i, j+1, endi, endj, count + 1);
		//if(i+1<M)
		//   PathFinding(i+1, j, endj, endj, count + 1);
		//if(j-1>=0)
		//   PathFinding(i, j-1, endi, endj, count + 1);

		if(j-1>=0)
			PathFinding(i,j-1,endi,endj,count+1);
		if(i+1<M)
			PathFinding(i+1,j,endi,endj,count+1);
		if(j+1<N)
			PathFinding(i,j+1,endi,endj,count+1);
		if(i-1>=0)
			PathFinding(i-1,j,endi,endj,count+1);


		path[i][j] = PASS;
		path_thr[i][j] = NO;
	}
}


int SearchLeastPath(int starti, int startj, int endi, int endj)
{
	if ( starti < 0 || startj < 0 || starti > 5 || startj > 5 ||
		 endi < 0 || endj < 0 || endi > 6 || endj > 6 ||
		 path[starti][startj] == 0 || path[endi][endj] == 0)
	{
		  printf("The input is valid\n");
		  return -1;

    }
    
	int count = 0;
	PathFinding(starti, startj, endi, endj, count);
	PrintLeastPath(starti,startj,endi,endj);
	return 0;

}


void GetCurLeastPath()
{
	int i,j;
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
		{
			least_path[i][j]=0;
			if(path_thr[i][j]==YES)
				least_path[i][j]=1;
		}
	}

}


void PrintLeastPath(int starti, int startj, int endi, int endj)
{
	int x,y;
	printf("diatance: %d\n", least);
	x=starti,y=startj;
	while(1)
	{
		printf("(%d,%d) ",x,y);
		least_path[x][y]=0;
		if(x==endi&&y==endj)
		{
			break;
		}
		if(y-1>=0&&least_path[x][y-1]==1)
		{
			y=y-1;
			continue;
		}
		if(x+1<M&&least_path[x+1][y]==1)
		{
			x=x+1;
			continue;
		}
		if(y+1<N&&least_path[x][y+1]==1)
		{
			y=y+1;
			continue;
		}
		if(x-1>=0&&least_path[x-1][y]==1)
		{
			x=x-1;
			continue;
		}
	}
	printf("\n");
}


int main(int argc, char *argv)
{
	int starti, startj, endi, endj;
	scanf("%d%d%d%d", &starti, &startj, &endi, &endj);
	SearchLeastPath(starti, startj, endi, endj);
	return 0;
}
