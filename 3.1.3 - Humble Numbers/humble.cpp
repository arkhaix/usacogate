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

	int primes[100] = {0};
	for(int i=0;i<numPrimes;i++)
		fscanf(fin, "%d", &primes[i]);

	int numHumble = 0;
	int i;
	for(i=2; numHumble != nthHumble; i++)
	{
		for(int j=0;j<numPrimes;j++)
		{
			if( (i % primes[j]) == 0 )
			{
				numHumble++;

				printf("%d: %d\n", numHumble, i);

				break;
			}
		}
	}

	fprintf(fout, "%d\n", i);

	fclose(fout);
	fclose(fin);

	return 0;
}