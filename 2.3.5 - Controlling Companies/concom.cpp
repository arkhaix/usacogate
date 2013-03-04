/*
ID: general10
PROG: concom
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


int adjacency[101][101];
int res[101][101] = {0};

void Go(int owner, int child)
{
	if(child == owner)
		return;

	for(int i=0;i<101;i++)
	{
		if(adjacency[child][i] > 0 && i != child && i != owner)
		{
			res[owner][i] += adjacency[child][i];
			if(res[owner][i] > 50 && res[owner][i] - adjacency[child][i] <= 50)
				Go(owner, i);
		}
	}
}

int main()
{
	FILE *fin  = fopen("concom.in", "r");
	FILE *fout = fopen("concom.out", "w");

	int numCompanies;
	fscanf(fin, "%d", &numCompanies);

	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			adjacency[i][j] = -1;

	set<int> companies;

	for(int i=0;i<numCompanies;i++)
	{
		int companyA, companyB, percent;
		fscanf(fin, "%d %d %d", &companyA, &companyB, &percent);
		adjacency[companyA][companyB] = percent;

		companies.insert(companyA);
		companies.insert(companyB);
	}

	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			res[i][j] = (adjacency[i][j] > 0) ? adjacency[i][j] : 0;

	for(set<int>::iterator iter = companies.begin(); iter != companies.end(); ++iter)
	{
		int owner = *iter;
		for(int i=0;i<101;i++)
		{
			if(i == owner)
				continue;

			if(adjacency[owner][i] > 50)
				Go(owner, i);
		}
	}

	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			if(res[i][j] > 50 && i!=j)
				fprintf(fout, "%d %d\n", i, j);

	fclose(fout);
	fclose(fin);

	return 0;
}