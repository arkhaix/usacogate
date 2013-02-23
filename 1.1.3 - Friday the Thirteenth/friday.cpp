/*
ID: general10
PROG: friday
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

int main() 
{
	FILE *fin  = fopen("friday.in", "r");
	FILE *fout = fopen("friday.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	int res[7] = {0};	// 0 = Saturday (output requirement)
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int dayOfWeek = 2;

	for(int year=1900;year<1900+n;year++)
	{
		daysInMonth[1] = 28;
		if((year%4)==0 && ((year%100)!=0 || ((year%400)==0)))
			daysInMonth[1] = 29;

		for(int month=0;month<12;month++)
		{
			res[(dayOfWeek+12)%7]++;
			dayOfWeek += daysInMonth[month];
			dayOfWeek %= 7;
		}
	}

	for(int i=0;i<6;i++)
		fprintf(fout, "%d ", res[i]);
	fprintf(fout, "%d\n", res[6]);

	fclose(fin);
	fclose(fout);

	return 0;
}