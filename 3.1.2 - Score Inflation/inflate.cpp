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
	int weight;
	int value;
};

bool DenominationsByWeight(const Denomination& lhs, const Denomination& rhs)
{
	return lhs.weight < rhs.weight;
}

int knapSize;
int numDenominations;
vector<Denomination> denominations;

map< pair<int, int>, int > memo;

int Go(int weightRemaining, int maxDenomination)
{
	int res = 0;

	if(weightRemaining == 0)
		return 0;

	map< pair<int, int>, int >::iterator iter = memo.find( make_pair(weightRemaining, maxDenomination) );
	if(iter != memo.end())
		return iter->second;

	for(int i=0;i<=maxDenomination;i++)
	{
		int remaining = weightRemaining - denominations[i].weight;
		if(remaining >= 0)
			res = max(res, denominations[i].value + Go(remaining, i));
	}

	memo[ make_pair(weightRemaining, maxDenomination) ] = res;
	return res;
}

int main() 
{
	FILE *fin  = fopen("inflate.in", "r");
	FILE *fout = fopen("inflate.out", "w");

	fscanf(fin, "%d %d", &knapSize, &numDenominations);

	for(int i=0;i<numDenominations;i++)
	{
		Denomination d;
		fscanf(fin, "%d %d", &d.value, &d.weight);
		denominations.push_back(d);
	}

	sort(denominations.begin(), denominations.end(), DenominationsByWeight);

	fprintf(fout, "%d\n", Go(knapSize, denominations.size()-1));

	fclose(fout);
	fclose(fin);

	return 0;
}