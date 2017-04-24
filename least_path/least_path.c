#include <stdio.h>
#include <stdlib.h>

#define M 6
#define N 7
#define Max 100

int map[M][N] =
{   
	 1, 1, 1, 1, 1, 1, 1, 
	 1, 0, 1, 0, 1, 0, 1, 
	 1, 1, 1, 1, 1, 1, 1, 
	 1, 1, 1, 0, 1, 1, 1, 
	 1, 0, 1, 0, 1, 0, 1, 
	 1, 1, 1, 1, 1, 1, 1
};


struct
{
	int i, j;
	int pre; // 路径中上一块在路径中的下标
}Qu[Max];

int front = -1, rear = -1;
void printPath(int n);
int search(int starti, int startj, int endi, int endj);

int search(int starti, int startj, int endi, int endj)
{
	int i,j,di;
	int find = 0;

	if (map[starti][startj] == 0 || map[endi][endj] == 0 ||
			starti < 0 || startj < 0 || starti > 5 || startj > 5 ||
			endi < 0 || endj < 0 || endi > 6 || endj > 6)
	{
		printf("The input is valid\n");
		return -1;
	}

	rear++;
	Qu[rear].i = starti;
	Qu[rear].j = startj;
	Qu[rear].pre = -1;
    map[0][0] = -1;
	while(front < rear && !find)
	{
		front++;
		i = Qu[front].i;
		j = Qu[front].j;
		if ( i == endi && j == endj)
		{
			find = 1;
			printPath(front);
			return 1;
        }
   // search all the directions
		for (di = 0; di < 4; di++)
		{
			switch(di)
			{
				case 0:
					i = Qu[front].i-1;
					j = Qu[front].j;
					break;
				case 1:
					i = Qu[front].i;
					j = Qu[front].j+1;
					break;
				case 2:
					i = Qu[front].i+1;
					j = Qu[front].j;
					break;
				case 3:
					i = Qu[front].i;
					j = Qu[front].j-1;
					break;
			}

			if(i<0||i>M-1||j<0||j>N-1)
				continue;

			if (map[i][j] == 1)
			{
				rear++;
				Qu[rear].i = i;
				Qu[rear].j = j;
				Qu[rear].pre = front;
				map[i][j] = -1;  //  Not access the dead loop
				
			}
			
		}
		
	}
	return 0;

}

void printPath(int n)
{
	int k = n, j, m = 0;
	do 
	{
		j = k;
		k = Qu[k].pre;
		Qu[j].pre = -1;

	}while(k!=0);

    k = 0;
	while(k < Max)
	{
		if (Qu[k].pre == -1)
		{
			printf("(%d, %d)", Qu[k].i, Qu[k].j);
			m++;
		}
		k++;
	}
	printf("\n");
	printf("distace: %d", m-1);
	printf("\n");
}



int main(int argc, char *argv)
{
	int starti, startj, endi, endj;
	scanf("%d%d%d%d", &starti, &startj, &endi, &endj);
	search(starti, startj, endi, endj);
	return 0;
}
