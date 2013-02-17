/*
ID: general10
PROG: preface
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


int numeralCount[256] = {0};

void Go(int digit, int ten, int five, int one)
{
	if(digit == 0)
	{
	}
	else if(digit < 4)
	{
		for(int i=0;i<digit;i++)
			numeralCount[one]++;
	}
	else if(digit == 4)
	{
		numeralCount[one]++;
		numeralCount[five]++;
	}
	else if(digit == 5)
	{
		numeralCount[five]++;
	}
	else if(digit < 9)
	{
		numeralCount[five]++;
		for(int i=0;i<digit-5;i++)
			numeralCount[one]++;
	}
	else if(digit == 9)
	{
		numeralCount[one]++;
		numeralCount[ten]++;
	}
}

void ToRoman(int n)
{
	if(n >= 1000)
		Go(n / 1000, 0, 0, 'M');
	while(n >= 1000)
		n -= 1000;

	if(n >= 100)
		Go(n / 100, 'M', 'D', 'C');
	while(n >= 100)
		n -= 100;

	if(n >= 10)
		Go(n / 10, 'C', 'L', 'X');
	while(n >= 10)
		n -= 10;

	if(n)
		Go(n, 'X', 'V', 'I');
}

int main() 
{
	FILE *fin  = fopen("preface.in", "r");
	FILE *fout = fopen("preface.out", "w");

	int n;
	fscanf(fin, "%d", &n);

	for(int i=1;i<=n;i++)
		ToRoman(i);

	int numerals[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
	for(int i=0;i<7;i++)
	{
		if(numeralCount[ numerals[i] ] > 0)
			fprintf(fout, "%c %d\n", numerals[i], numeralCount[ numerals[i] ]);
	}

	fclose(fout);
	fclose(fin);

	return 0;
}