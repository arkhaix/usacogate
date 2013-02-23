/*
ID: general10
PROG: palsquare
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
	FILE *fin  = fopen("palsquare.in", "r");
	FILE *fout = fopen("palsquare.out", "w");

	int base;
	fscanf(fin, "%d\n", &base);

	for(int i=1;i<=300;i++)
	{
		string s = nToBase(i*i, base);
		if(isPalindrome(s) == true)
			fprintf(fout, "%s %s\n", nToBase(i, base).c_str(), s.c_str());
	}

	fclose(fout);
	fclose(fin);

	return 0;
}