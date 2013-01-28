/*
ID: general10
PROG: dualpal
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;


bool isPalindrome(string& s)
{
	for(unsigned int i=0;i<s.length()/2;i++)
	{
		if(s[i] != s[ s.length()-(i+1) ])
			return false;
	}

	return true;
}

string nToBase(int n, int base)
{
	string res = "";

	if(n == 0)
		return "0";

	char baseChar[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
	};

	while(n > 0)
	{
		res = baseChar[n % base] + res;
		n /= base;
	}

	return res;
}

int main() 
{
	FILE *fin  = fopen("dualpal.in", "r");
	FILE *fout = fopen("dualpal.out", "w");

	int targetNumResults, searchStart;
	fscanf(fin, "%d %d\n", &targetNumResults, &searchStart);
	searchStart++;

	int resultsFound = 0;

	for(int i=searchStart;;i++)
	{
		int numPalindromicBases = 0;

		for(int base=2;base<=10;base++)
		{
			string s = nToBase(i, base);
			if(isPalindrome(s) == true)
			{
				numPalindromicBases++;
				if(numPalindromicBases > 1)
					break;
			}
		}

		if(numPalindromicBases >= 2)
		{
			fprintf(fout, "%d\n", i);
			resultsFound++;
		}

		if(resultsFound >= targetNumResults)
			break;
	}

	fclose(fout);
	fclose(fin);

	return 0;
}