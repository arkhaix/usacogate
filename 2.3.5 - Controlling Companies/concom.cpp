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

void bfs(int company)
{
	stack<int> children;

	bool visited[101] = {false};

	children.push(company);
	while(children.empty() == false)
	{
		int child = children.top();
		children.pop();

		if(visited[child] == true)
			continue;

		visited[child] = true;

		for(int i=0;i<101;i++)
		{
			if(i == child)
				continue;

			if(adjacency[child][i] > 0)
			{
				res[company][i] += adjacency[child][i];
				if(adjacency[child][i] > 50)
					children.push(i);
			}
		}
	};
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

	for(set<int>::iterator iter = companies.begin(); iter != companies.end(); ++iter)
		bfs(*iter);

	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			if(res[i][j] > 50 && i!=j)
				fprintf(fout, "%d %d\n", i, j);

	fclose(fout);
	fclose(fin);

	return 0;
}