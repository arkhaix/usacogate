/*
ID: general10
PROG: pprime
LANG: C++
*/
#include <algorithm>
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

vector<bool> primes(10000001, true);

bool isPalindrome(int n)
{
	int digits[10] = {0};
	int len = 0;

	while(n != 0)
	{
		digits[len] = n % 10;
		n /= 10;
		len++;
	}

	for(int i=0;i<len/2;i++)
		if(digits[i] != digits[len-(i+1)])
			return false;

	return true;
}

int main() 
{
	FILE *fin  = fopen("pprime.in", "r");
	FILE *fout = fopen("pprime.out", "w");

	primes[0] = primes[1] = false;
	for(int i=3;i<=10000;i+=2)
	{
		if(primes[i] == false)
			continue;

		for(int j=i+i;j<primes.size();j+=i)
			primes[j]=false;
	}

	int a, b;
	fscanf(fin, "%d %d\n", &a, &b);
	if((a & 1) == 0)
		a++;

	a = min(a,10000000);
	b = min(b,10000000);

	for(int i=a;i<=b;i+=2)
	{
		if(primes[i] == false)
			continue;

		if(isPalindrome(i) == false)
			continue;

		fprintf(fout, "%d\n", i);
	}

	fclose(fout);
	fclose(fin);

	return 0;
}