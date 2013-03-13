/*
ID: general10
PROG: humble
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


int main() 
{
	FILE *fin  = fopen("humble.in", "r");
	FILE *fout = fopen("humble.out", "w");

	int numPrimes, nthHumble;
	fscanf(fin, "%d %d", &numPrimes, &nthHumble);

	int minPrime = INT_MAX;

	int primes[100] = {0};
	set<int> humbleNumbers;
	for(int i=0;i<numPrimes;i++)
	{
		fscanf(fin, "%d", &primes[i]);
		humbleNumbers.insert(primes[i]);

		minPrime = min(minPrime, primes[i]);
	}

	humbleNumbers.insert(1);

	int numHumble = 1;
	int current = minPrime;
	while(numHumble != nthHumble)
	{
		int nextPotentialHumble = INT_MAX;
		int primeFactor;

		for(int j=0;j<numPrimes;j++)
		{
			int a = current + primes[j] - (current % primes[j]);
			if(a < nextPotentialHumble)
			{
				nextPotentialHumble = a;
				primeFactor = primes[j];
			}
		}

		current = nextPotentialHumble;
		int quotient = current / primeFactor;
		if(humbleNumbers.find(quotient) != humbleNumbers.end())
		{
			numHumble++;
			humbleNumbers.insert(current);
		}
	}

	fprintf(fout, "%d\n", current);

	fclose(fout);
	fclose(fin);

	return 0;
}