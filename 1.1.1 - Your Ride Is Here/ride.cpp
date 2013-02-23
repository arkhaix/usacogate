/*
ID: general10
PROG: ride
LANG: C++
*/
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
	FILE *fin  = fopen("ride.in", "r");
	FILE *fout = fopen("ride.out", "w");

	char a[32], b[32];
	fscanf(fin, "%s\n%s\n", a, b);

	int am = 1;
	for(int i=0;i<strlen(a);i++)
	{
		am *= 1+(a[i]-'A');
		am %= 47;
	}

	int bm = 1;
	for(int i=0;i<strlen(b);i++)
	{
		bm *= 1+(b[i]-'A');
		bm %= 47;
	}

	if(am == bm)
		fprintf(fout, "GO\n");
	else
		fprintf(fout, "STAY\n");

	fclose(fin);
	fclose(fout);

	return 0;
}