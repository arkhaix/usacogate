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

const int MOD = 9901;
int twoExp[101] = {0};

int twoExpN_choose_k(int n, int k)
{
	return -1;
}

int dfs(int depth, int totalNodesUsed, int parentNodesUsed)
{
	if(totalNodesUsed > numNodes-2 || depth > treeHeight)
		return 0;

	int maxAvailableNodes = numNodes - totalNodesUsed;
	maxAvailableNodes = min(maxAvailableNodes, parentNodesUsed * 2);

	int parentDepth = depth-1;
	int parentSlots = 1<<parentDepth;

	int res = 0;

	if(depth == treeHeight)
	{
		if(maxAvailableNodes != numNodes - totalNodesUsed)
			return 0;

		//res = (2^parentDepth) choose (maxAvailableNodes/2), mod 9901
		//res = parentNodesUsed choose (maxAvailableNodes/2), mod 9901
	}
	else
	{
		for(int n=2; n <= maxAvailableNodes; n+=2)
		{
			int childRes = dfs(depth+1, totalNodesUsed+n, n);
			if(childRes == 0)
				continue;

			//int curRes = (2^parentDepth) choose (n/2), mod 9901;
			//int curRes = parentNodesUsed choose (n/2), mod 9901;
			//res += (curRes * childRes) mod 9901;
		}
	}

	return res;
}

int main() 
{
	FILE *fin  = fopen("nocows.in", "r");
	FILE *fout = fopen("nocows.out", "w");

	fscanf(fin, "%d %d", &numNodes, &treeHeight);

	twoExp[0] = 1;
	for(int i=1;i<=100;i++)
		twoExp[i] = (twoExp[i-1] * 2) % MOD;

	int fact[201] = {0};
	fact[1] = 1;
	for(int i=2;i<=200;i++)
		fact[i] = (i * fact[i-1]) % MOD;
	
	if((numNodes%2) == 0 ||
		treeHeight <= 8 && numNodes > (1<<treeHeight)-1 )
	{
		fprintf(fout, "0\n");
	}
	else
	{
		fprintf(fout, "%d\n", dfs(1, 1, 1));
	}

	fclose(fout);
	fclose(fin);

	return 0;
}