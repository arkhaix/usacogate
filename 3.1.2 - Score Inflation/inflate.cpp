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

bool DenominationsByValuePerWeight(const Denomination& lhs, const Denomination& rhs)
{
	return ((double)lhs.value / (double)lhs.weight) < ((double)rhs.value / (double)rhs.weight);
}

int knapSize;
int numDenominations;
vector<Denomination> denominations;

int Go(int weightRemaining, int maxDenomination)
{
	for(int i=maxDenomination;i>=0;i--)
	{
		int remaining = weightRemaining - denominations[i].weight;
		if(remaining >= 0)
			return denominations[i].value + Go(remaining, i);
	}

	return 0;
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

	sort(denominations.begin(), denominations.end(), DenominationsByValuePerWeight);

	fprintf(fout, "%d\n", Go(knapSize, denominations.size()-1));

	fclose(fout);
	fclose(fin);

	return 0;
}