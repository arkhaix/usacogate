/*
ID: general10
PROG: frac1
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

struct Fraction
{
	int numerator;
	int denominator;

	Fraction(int n, int d)
	{
		numerator = n;
		denominator = d;
	}

	void Reduce()
	{
		for(int i=2;i<=(int)sqrt((double)denominator);i++)
		{
			if( (numerator % i) == 0 && (denominator % i) == 0 )
			{
				numerator /= i;
				denominator /= i;
				i--;
			}
		}
	}
};

bool operator<(const Fraction& a, const Fraction& b)
{
	return (a.numerator*b.denominator) < (b.numerator*a.denominator);
}

int main() 
{
	FILE *fin  = fopen("frac1.in", "r");
	FILE *fout = fopen("frac1.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	set<Fraction> results;

	for(int denominator=1;denominator<=n;denominator++)
	{
		for(int i=0;i<=denominator;i++)
		{
			Fraction f(i, denominator);
			f.Reduce();
			results.insert(f);
		}
	}

	for(set<Fraction>::iterator iter=results.begin();iter!=results.end();++iter)
		fprintf(fout, "%d/%d\n", iter->numerator, iter->denominator);

	fclose(fout);
	fclose(fin);

	return 0;
}