/*
ID: general10
PROG: subset
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
	FILE *fin  = fopen("subset.in", "r");
	FILE *fout = fopen("subset.out", "w");

	int n;
	fscanf(fin, "%d", &n);

	unsigned int dp[40][1000] = {0};
	for(int i=1;i<40;i++)
	{
		for(int j=0;j<1000;j++)
		{
			int next = 0;
			if(j==i)
				next = 1;
			else if(j > i && dp[i-1][j-i] > 0)
				next = dp[i-1][j-i];

			dp[i][j] = dp[i-1][j] + next;
		}
	}

	unsigned int res = 0;
	if( ((n&1 && ((n+1)%4)==0)) || (((n&1)==0) && ((n%4)==0)) )
	{
		int targetSum = 0;
		if(n&1)
			targetSum = n * ((n+1)/4);
		else
			targetSum = (n+1) * (n/4);

		res = dp[n][targetSum];
	}
	res /= 2;

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}