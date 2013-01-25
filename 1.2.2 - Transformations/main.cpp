/*
ID: general10
PROG: transform
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
	FILE *fin  = fopen("transform.in", "r");
	FILE *fout = fopen("transform.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	char source[11][11] = {0};
	char target[11][11] = {0};
	char ref[11][11] = {0};
	char test[11][11] = {0};

	for(int i=0;i<n;i++)
		fscanf(fin, "%s\n", source[i]);

	for(int i=0;i<n;i++)
		fscanf(fin, "%s\n", target[i]);

	int res = -1;
	vector<int> potentialResults;
	for(int i=0;i<8;i++)
	{
		for(int r=0;r<n;r++) for(int c=0;c<n;c++) 
		{
			if(i & 4)
				ref[r][c] = source[r][(n-1)-c];
			else
				ref[r][c] = source[r][c];

			test[r][c] = ref[r][c];

		}

		switch(i & 3)
		{
		case 0:
			break;

		case 1:
			for(int r=0;r<n;r++) for(int c=0;c<n;c++) test[r][c] = ref[(n-1)-c][r];
			break;

		case 2:
			for(int r=0;r<n;r++) for(int c=0;c<n;c++) test[r][c] = ref[(n-1)-r][(n-1)-c];
			break;

		case 3:
			for(int r=0;r<n;r++) for(int c=0;c<n;c++) test[r][c] = ref[c][(n-1)-r];
			break;
		};

		res = i;
		for(int r=0;r<n && res!=-1;r++) for(int c=0;c<n;c++) if(test[r][c] != target[r][c])
		{
			res = -1;
			break;
		}

		if(res != -1)
		{
			if(res == 0)
				res = 6;
			else if((res & 4) && res != 4)
				res = 5;

			potentialResults.push_back(res);
		}
	}

	if(potentialResults.empty())
		potentialResults.push_back(7);

	sort(potentialResults.begin(), potentialResults.end());

	fprintf(fout, "%d\n", potentialResults[0]);

	fclose(fin);
	fclose(fout);

	return 0;
}
