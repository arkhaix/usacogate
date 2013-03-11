/*
ID: general10
PROG: agrinet
LANG: C++
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;


int main() 
{
	FILE *fin  = fopen("agrinet.in", "r");
	FILE *fout = fopen("agrinet.out", "w");

	int numFarms;
	fscanf(fin, "%d", &numFarms);

	int edges[100][100] = {0};
	for(int i=0;i<numFarms;i++)
		for(int j=0;j<numFarms;j++)
			fscanf(fin, "%d", &edges[i][j]);

	int connected[100] = {0};

	int res = 0;
	connected[0] = true;
	for(int farmsConnected=1;farmsConnected<numFarms;farmsConnected++)
	{
		int nextIndex = -1;
		int nextDistance = -1;

		for(int i=0;i<numFarms;i++)
		{
			if(connected[i])
				continue;

			for(int j=0;j<numFarms;j++)
			{
				if(j==i)
					continue;

				if(!connected[j])
					continue;

				if(nextIndex == -1 || edges[i][j] < nextDistance)
				{
					nextIndex = i;
					nextDistance = edges[i][j];
				}
			}
		}

		connected[nextIndex] = 1;
		res += nextDistance;
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}