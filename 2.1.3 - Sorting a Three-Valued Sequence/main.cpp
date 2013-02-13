/*
ID: general10
PROG: sort3
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


int main() 
{
	FILE *fin  = fopen("sort3.in", "r");
	FILE *fout = fopen("sort3.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	int count[3] = {0};
	int sequence[1000];
	for(int i=0;i<n;i++)
	{
		fscanf(fin, "%d\n", &sequence[i]);
		count[sequence[i]-1]++;
	}

	int startPos[3] = {0, count[0], count[0]+count[1]};
	int pos[3] = {startPos[0], startPos[1], startPos[1]};
	int endPos[3] = {startPos[1], startPos[2], n};

	int res = 0;
	for(;pos[0]<endPos[0];pos[0]++)
	{
		if(sequence[ pos[0] ] == 2)
		{
			for(; sequence[ pos[1] ] != 1; pos[1]++) {}
			swap(sequence[ pos[0] ], sequence[ pos[1] ]);
			res++;
		}
		else if(sequence[ pos[0] ] == 3)
		{
			for(; sequence[ pos[2] ] != 1 && pos[2] < endPos[2]; pos[2]++) {}
			if(pos[2] >= endPos[2])
			{
				pos[2] = startPos[1];
				for(; sequence[ pos[2] ] != 1; pos[2]++) {}
			}
			swap(sequence[ pos[0] ], sequence[ pos[2] ]);
			res++;
		}
	}

	pos[1] = startPos[1];
	pos[2] = startPos[2];

	for(;pos[1]<endPos[1];pos[1]++)
	{
		if(sequence[ pos[1] ] == 3)
		{
			for(; sequence[ pos[2] ] != 2; pos[2]++) {}
			swap(sequence[ pos[1] ], sequence[ pos[2] ]);
			res++;
		}
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}