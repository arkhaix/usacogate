/*
ID: general10
PROG: money
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

int numCoins, targetAmount;
int coinValue[25] = {0};

long long memo[10001][25] = {-1};

unsigned long long Go(int amount, int maxCoinIndex)
{
	if(amount < 0)
		return 0;

	if(amount == 0)
		return 1;

	if(memo[amount][maxCoinIndex] != (long long)-1)
		return memo[amount][maxCoinIndex];

	unsigned long long res = 0;
	for(int i=0;i<=maxCoinIndex;i++)
		res += Go(amount - coinValue[i], i);

	memo[amount][maxCoinIndex] = res;

	return res;
}

int main() 
{
	FILE *fin  = fopen("money.in", "r");
	FILE *fout = fopen("money.out", "w");

	for(int i=0;i<10001;i++)
		for(int j=0;j<25;j++)
			memo[i][j] = -1;

	fscanf(fin, "%d %d", &numCoins, &targetAmount);

	for(int i=0;i<numCoins;i++)
		fscanf(fin, "%d", &coinValue[i]);

	sort(&coinValue[0], &coinValue[numCoins]);

	fprintf(fout, "%llu\n", Go(targetAmount, numCoins-1));

	fclose(fout);
	fclose(fin);

	return 0;
}