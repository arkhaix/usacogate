/*
ID: general10
PROG: runround
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


vector<int> Digits(int n)
{
	vector<int> res;
	res.reserve(10);
	while(n != 0)
	{
		res.push_back(n%10);
		n /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

bool IsRunaround(int n)
{
	vector<int> digits = Digits(n);
	vector<bool> seen(digits.size(), false);
	vector<bool> digitUsed(10, false);

	for(int nextIndex=0;;)
	{
		int prevIndex = nextIndex;
		nextIndex = (nextIndex + digits[nextIndex]) % digits.size();
		
		if(seen[nextIndex] == true)
			break;

		seen[nextIndex] = true;

		if(nextIndex == prevIndex)
			return false;

		if(digitUsed[ digits[nextIndex] ] == true)
			return false;

		digitUsed[ digits[nextIndex] ] = true;
	}

	for(int i=0;i<digits.size();i++)
		if(seen[i] == false)
			return false;

	return true;
}

int main() 
{
	FILE *fin  = fopen("runround.in", "r");
	FILE *fout = fopen("runround.out", "w");

	int n;
	fscanf(fin, "%d", &n);
	n++;

	while(!IsRunaround(n))
		n++;

	fprintf(fout, "%d\n", n);

	fclose(fout);
	fclose(fin);

	return 0;
}