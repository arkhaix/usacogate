/*
ID: general10
PROG: checker
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


vector<string> solutions;
int numSolutions;
int board[13][13] = {0};
int colUsed[13] = {0};
int upDiagonalUsed[26] = {0};
int downDiagonalUsed[26] = {0};
int n;

string Save()
{
	string res;
	char buf[8];

	for(int r=0;r<n;r++) for(int c=0;c<n;c++) 
	{
		if(board[r][c])
		{
			sprintf(buf, "%d", c+1);
			res += buf;
			if(r != n-1)
				res += " ";
			break;
		}
	}

	return res;
}

void Go(int depth)
{
	int r = depth;
	if(r == n)
	{
		if(solutions.size() < 3)
			solutions.push_back(Save());
		numSolutions++;
		return;
	}

	for(int c=0;c<n;c++)
	{
		if(colUsed[c])
			continue;

		int ud = r+c;
		if(upDiagonalUsed[ud])
			continue;

		int dd = 13+(c-r);
		if(downDiagonalUsed[dd])
			continue;

		board[r][c]=1;
		colUsed[c]=1;
		upDiagonalUsed[ud]=1;
		downDiagonalUsed[dd]=1;

		Go(depth+1);

		downDiagonalUsed[dd]=0;
		upDiagonalUsed[ud]=0;
		colUsed[c]=0;
		board[r][c]=0;
	}
}

int main() 
{
	FILE *fin  = fopen("checker.in", "r");
	FILE *fout = fopen("checker.out", "w");

	fscanf(fin, "%d\n", &n);

	Go(0);

	for(int i=0;i<solutions.size();i++)
	{
		fprintf(fout, "%s\n", solutions[i].c_str());
	}

	fprintf(fout, "%d\n", numSolutions);

	fclose(fout);
	fclose(fin);

	return 0;
}
