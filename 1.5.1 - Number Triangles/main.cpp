/*
ID: general10
PROG: numtri
LANG: C++
*/
#include <algorithm>
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

int main() 
{
	FILE *fin  = fopen("numtri.in", "r");
	FILE *fout = fopen("numtri.out", "w");

	int numRows;
	fscanf(fin, "%d\n", &numRows);

	vector<int> prevRow;
	int node;
	fscanf(fin, "%d\n", &node);
	prevRow.push_back(node);

	vector<int> nextRow;
	int res = 0;

	for(int row=2;row<=numRows;row++)
	{
		for(int col=0;col<=prevRow.size();col++)
		{
			int val;
			fscanf(fin, "%d ", &val);
			node = val;

			if(col < prevRow.size())
				node = max(node, val+prevRow[col]);

			if(col-1 >= 0)
				node = max(node, val+prevRow[col-1]);

			res = max(res, node);

			nextRow.push_back(node);
		}

		prevRow = nextRow;
		nextRow.clear();
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}