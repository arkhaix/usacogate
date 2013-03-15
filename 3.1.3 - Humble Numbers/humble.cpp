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


/*
	This whole HumbleNumber object exists so that we can reverse-sort the priority_queue.
	priority_queue doesn't have a comparator parameter; it always uses operator<
	and it always returns the greatest element first.  We need to reverse it so that
	it returns the smallest element first.
*/
struct HumbleNumber
{
	int Value;

	/*implicit*/ HumbleNumber(int n)
	{
		Value = n;
	}

	operator int() const
	{
		return Value;
	}

	bool operator==(int rhs) const
	{
		return Value == rhs;
	}
};

bool operator<(const HumbleNumber& lhs, const HumbleNumber& rhs)
{
	return rhs.Value < lhs.Value;
}

int main() 
{
	FILE *fin  = fopen("humble.in", "r");
	FILE *fout = fopen("humble.out", "w");

	int numPrimes, nthHumble;
	fscanf(fin, "%d %d", &numPrimes, &nthHumble);

	int primes[100] = {0};
	priority_queue<HumbleNumber> humbleNumbers;
	for(int i=0;i<numPrimes;i++)
		fscanf(fin, "%d", &primes[i]);

	int nextHumble = 1;
	humbleNumbers.push(nextHumble);

	set<int> humbleSet;
	int setSize = 0;
	int maxHumble = 0;

	for(int i=0;i<nthHumble;i++)
	{
		nextHumble = humbleNumbers.top();
		while(humbleNumbers.empty() == false && humbleNumbers.top() == nextHumble)
			humbleNumbers.pop();

		int numHumblesToGo = nthHumble - i;

		for(int j=0;j<numPrimes;j++)
		{
			long long n = (long long)nextHumble * (long long)primes[j];
			if(n > nextHumble && n < (long long)INT_MAX && 
				(setSize < numHumblesToGo || n < maxHumble) &&
				humbleSet.find(n) == humbleSet.end())
			{
				humbleSet.insert(n);
				humbleNumbers.push(n);
				setSize++;
				maxHumble = max(maxHumble, (int)n);
			}
		}
	}

	fprintf(fout, "%d\n", humbleNumbers.top());

	fclose(fout);
	fclose(fin);

	return 0;
}