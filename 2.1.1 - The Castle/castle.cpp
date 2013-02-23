/*
ID: general10
PROG: castle
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int m, n;
int castle[50][50];

int rooms[50][50];
int numRooms = 0;
int largestRoom = 0;

int GenComponents(int r, int c)
{
	if(rooms[r][c] != -1)
		return 0;

	int res = 1;

	rooms[r][c] = numRooms;

	if((castle[r][c] & 1) == 0 && c-1>=0)
		res += GenComponents(r,c-1);

	if((castle[r][c] & 2) == 0 && r-1>=0)
		res += GenComponents(r-1,c);

	if((castle[r][c] & 4) == 0 && c+1<n)
		res += GenComponents(r,c+1);

	if((castle[r][c] & 8) == 0 && r+1<m)
		res += GenComponents(r+1,c);

	largestRoom = max(largestRoom, res);

	return res;
}

int main() 
{
	FILE *fin  = fopen("castle.in", "r");
	FILE *fout = fopen("castle.out", "w");

	fscanf(fin, "%d %d\n", &m, &n);
	swap(m,n);

	for(int i=0;i<m*n;i++)
	{
		int r = i/n;
		int c = i%n;
		fscanf(fin, "%d", &castle[r][c]);
		rooms[r][c] = -1;
	}

	for(int r=0;r<m;r++)
	{
		for(int c=0;c<n;c++)
		{
			int roomSize = GenComponents(r,c);
			if(roomSize > 0)
				numRooms++;
		}
	}

	fprintf(fout, "%d\n", numRooms);
	fprintf(fout, "%d\n", largestRoom);

	for(int r=0;r<m;r++) for(int c=0;c<n;c++) rooms[r][c]=-1;

	int wallR = 0;
	int wallC = 0;
	int wallN = 0;

	for(int c=0;c<n;c++)
	{
		for(int r=m-1;r>=0;r--)
		{
			for(int i=1;i<=2;i++)
			{
				int oldVal = castle[r][c];
				castle[r][c] &= ~(1<<i);
				if(castle[r][c] != oldVal)
				{
					int oldLargest = largestRoom;
					GenComponents(r,c);
					for(int r=0;r<m;r++) for(int c=0;c<n;c++) rooms[r][c]=-1;
					if(largestRoom > oldLargest)
					{
						wallR = r;
						wallC = c;
						wallN = i;
					}
				}
				castle[r][c] = oldVal;
			}
		}
	}

	fprintf(fout, "%d\n", largestRoom);

	const char* wallStr[] = {"W","N","E","S"};
	fprintf(fout, "%d %d %s\n", wallR+1, wallC+1, wallStr[wallN]);

	fclose(fout);
	fclose(fin);

	return 0;
}