/*
ID: general10
PROG: inflate
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


struct Denomination
{
	unsigned int weight;
	unsigned int value;
};

bool DenominationsByWeight(const Denomination& lhs, const Denomination& rhs)
{
	return lhs.weight < rhs.weight;
}

int main() 
{
	FILE *fin  = fopen("inflate.in", "r");
	FILE *fout = fopen("inflate.out", "w");

	unsigned int knapSize;
	unsigned int numDenominations;
	vector<Denomination> denominations;

	fscanf(fin, "%d %d", &knapSize, &numDenominations);

	for(unsigned int i=0;i<numDenominations;i++)
	{
		Denomination d;
		fscanf(fin, "%d %d", &d.value, &d.weight);
		denominations.push_back(d);
	}

	sort(denominations.begin(), denominations.end(), DenominationsByWeight);

	unsigned int dp[10001] = {0};
	for(unsigned int i=0;i<=knapSize;i++)
	{
		for(unsigned int j=0;j<denominations.size();j++)
		{
			if(denominations[j].weight > i)
				break;

			dp[i] = max(dp[i], dp[i - denominations[j].weight] + denominations[j].value);
		}
	}

	fprintf(fout, "%d\n", dp[knapSize]);

	fclose(fout);
	fclose(fin);

	return 0;
}