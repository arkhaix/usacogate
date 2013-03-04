/*
ID: general10
PROG: nocows
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

int numNodes = 0;
int treeHeight = 0;

int memo[201][101];

int Go(int nodesRemaining, int heightRemaining)
{
	if(memo[nodesRemaining][heightRemaining] >= 0 || memo[nodesRemaining][heightRemaining] == -2)
		return memo[nodesRemaining][heightRemaining];

	if((nodesRemaining & 1) == 0)
		return 0;

	if(nodesRemaining == 0)
		return 0;

	if(heightRemaining <= 8 && nodesRemaining >= (1<<heightRemaining))
	{
		memo[nodesRemaining][heightRemaining] = -2;
		return -2;
	}

	int childNodesRemaining = nodesRemaining - 1;	///<-1 for the current node

	int res = 0;

	for(int i=1;i<=childNodesRemaining-1;i+=2)
	{
		int left = Go(i, heightRemaining-1);
		int right = Go(childNodesRemaining-i, heightRemaining-1);

		if(left < 0 || right < 0)
			continue;

		res += max(left, right);
		res %= 9901;
	}

	memo[nodesRemaining][heightRemaining] = res;

	return res;
}

int main() 
{
	FILE *fin  = fopen("nocows.in", "r");
	FILE *fout = fopen("nocows.out", "w");

	fscanf(fin, "%d %d", &numNodes, &treeHeight);

	for(int i=0;i<=200;i++)
		for(int j=0;j<=100;j++)
			memo[i][j] = -1;

	memo[1][1] = 1;

	fprintf(fout, "%d\n", Go(numNodes, treeHeight));

	fclose(fout);
	fclose(fin);

	return 0;
}