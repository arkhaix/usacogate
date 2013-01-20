/*
ID: general10
PROG: beads
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
	FILE *fin  = fopen("beads.in", "r");
	FILE *fout = fopen("beads.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	char beads[1024];
	fscanf(fin, "%s\n", beads);

	int res = 0;
	for(int breakPoint=0;breakPoint<n;breakPoint++)
	{
		int r = 0;
		int rp = breakPoint;
		bool ok = true;

		char chainColor = 'w';
		do
		{
			if(beads[rp] == chainColor || beads[rp] == 'w' || chainColor == 'w')
			{
				if(chainColor == 'w')
					chainColor = beads[rp];
				rp++;
				r++;
			}
			else
			{
				ok = false;
			}

			if(rp>=n)
				rp = 0;
		}
		while(ok && rp != breakPoint);

		int l = 0;
		int lp = breakPoint-1;
		if(lp < 0)
			lp = n-1;

		ok = true;
		chainColor = 'w';
		do
		{
			if(lp == rp)
				ok = false;

			if(beads[lp] == chainColor || beads[lp] == 'w' || chainColor == 'w')
			{
				if(chainColor == 'w')
					chainColor = beads[rp];
				lp--;
				l++;
			}
			else
			{
				ok = false;
			}

			if(lp < 0)
				lp = n-1;
		}
		while(ok && lp != breakPoint);

		int total = r + l;
		if(total > n)
			total = n;

		res = max(res, total);
	}

	fprintf(fout, "%d\n", res);

	fclose(fin);
	fclose(fout);

	return 0;
}