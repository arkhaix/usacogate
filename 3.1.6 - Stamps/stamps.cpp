/*
ID: general10
PROG: stamps
LANG: C++
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;


int dp[2000001] = {0};

int main() 
{
	FILE *fin  = fopen("stamps.in", "r");
	FILE *fout = fopen("stamps.out", "w");

	int numAllowed, numValues;
	fscanf(fin, "%d %d", &numAllowed, &numValues);

	int values[51];
	for(int i=0;i<numValues;i++)
		fscanf(fin, "%d", &values[i]);

	for(int i=0;i<numValues;i++)
		dp[ values[i] ] = 1;

	int res = -1;
	for(int i=1;i<2000001;i++)
	{
		for(int j=0;j<numValues;j++)
		{
			int prev = i-values[j];
			if(prev <= 0)
				continue;

			if(dp[prev] > 0 && (dp[i] == 0 || dp[prev]+1 < dp[i]))
				dp[i] = dp[prev]+1;
		}

		if(dp[i] != 0 && dp[i] <= numAllowed)
			res = i;
		else
			break;
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}