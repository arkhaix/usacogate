/*
ID: general10
PROG: milk2
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() 
{
	FILE *fin  = fopen("milk2.in", "r");
	FILE *fout = fopen("milk2.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	int* state = (int*)malloc(1000000 * sizeof(int));
	for(int i=0;i<1000000;i++)
		state[i] = 0;

	int minStart = 1000000;
	int maxEnd = 0;

	for(int i=0;i<n;i++)
	{
		int start, end;
		fscanf(fin, "%d %d\n", &start, &end);
		for(int j=start;j<end;j++)
			state[j] = 1;

		minStart = min(start, minStart);
		maxEnd = max(end, maxEnd);
	}

	int longestActive = 0;
	int longestIdle = 0;

	int active = 0;
	int idle = 0;
	for(int i=minStart;i<maxEnd;i++)
	{
		if(state[i] == 0)
		{
			longestActive = max(active, longestActive);
			active = 0;
			idle++;
		}
		else
		{
			longestIdle = max(idle, longestIdle);
			idle = 0;
			active++;
		}
	}

	if(active != 0)
		longestActive = max(active, longestActive);
	else
		longestIdle = max(idle, longestIdle);

	free(state);

	fprintf(fout, "%d %d\n", longestActive, longestIdle);

	fclose(fin);
	fclose(fout);

	return 0;
}