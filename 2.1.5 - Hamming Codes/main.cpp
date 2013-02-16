/*
ID: general10
PROG: hamming
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

int numCodewords;
int numBits;
int minDistance;

vector<int> solution;

bool dfs(int depth, int ones, int zeroes, int start)
{
	if(depth == numCodewords)
		return true;

	for(int i=start;i<(1<<numBits);i++)
	{
		int distance = 0;
		int newOnes = ones;
		int newZeroes = zeroes;

		for(int j=0;j<numBits;j++)
		{
			if((i & (1<<j)) && !(ones & (1<<j)))
			{
				distance++;
				newOnes |= (1<<j);
			}
			else if(!(i & (1<<j)) && !(zeroes & (1<<j)))
			{
				distance++;
				newZeroes |= (1<<j);
			}
		}

		if(distance < minDistance && depth != 0)
			continue;

		if(dfs(depth+1, newOnes, newZeroes, i+1))
		{
			solution.push_back(i);
			return true;
		}
	}

	return false;
}

int main() 
{
	FILE *fin  = fopen("hamming.in", "r");
	FILE *fout = fopen("hamming.out", "w");

	fscanf(fin, "%d %d %d", &numCodewords, &numBits, &minDistance);

	dfs(0, 0, 0, 0);

	fclose(fout);
	fclose(fin);

	return 0;
}