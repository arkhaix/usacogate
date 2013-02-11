/*
ID: general10
PROG: sprime
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

bool isPrime(int n)
{
	if(n < 2) return false;
	if(n == 2) return true;
	if((n&1)==0) return false;

	int root = (int)sqrt((double)n);
	for(int i=3;i<=root;i+=2)
	{
		if((n%i) == 0)
			return false;
	}

	return true;
}

void Go(FILE* fout, int val, int depth, int len)
{
	if(depth == len)
	{
		fprintf(fout, "%d\n", val);
		return;
	}

	const int append[] = {1,2,3,5,7,9};
	int newVal;

	for(int i=0;i<6;i++)
	{
		newVal = (val*10)+append[i];
		if(isPrime(newVal) == true)
			Go(fout, newVal, depth+1, len);
	}
}

int main() 
{
	FILE *fin  = fopen("sprime.in", "r");
	FILE *fout = fopen("sprime.out", "w");

	int len;
	fscanf(fin, "%d\n", &len);

	Go(fout, 0, 0, len);

	fclose(fout);
	fclose(fin);

	return 0;
}