/*
ID: general10
PROG: butter
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

int numCows, numPastures, numPaths;
int cowPastures[500];
int pastures[800][800];
bool visited[800] = {false};

void dfs(list<int>& path)
{
	int current = -1;
	list<int>::iterator iter = path.end();
	--iter;
	current = *iter;

	int prevNode = current;
	int visitNode = current;
	while(iter != path.begin())
	{
		visitNode = *iter;

		pastures[current][visitNode] = pastures[visitNode][current] =
			pastures[current][prevNode] + pastures[prevNode][visitNode];

		prevNode = visitNode;
		--iter;
	}

	visited[current] = true;

	for(int i=0;i<numPastures;i++)
	{
		if(visited[i] == false && pastures[current][i] != -1)
		{
			path.push_back(i);
			dfs(path);
			path.pop_back();
		}
	}
}

int main() 
{
	memset((void*)&pastures[0][0], -1, sizeof(pastures));

	FILE *fin  = fopen("butter.in", "r");
	FILE *fout = fopen("butter.out", "w");

	fscanf(fin, "%d %d %d", &numCows, &numPastures, &numPaths);
	
	for(int i=0;i<numCows;i++)
	{
		fscanf(fin, "%d", &cowPastures[i]);
		cowPastures[i]--;
	}

	for(int i=0;i<numPaths;i++)
	{
		int a, b, dist;
		fscanf(fin, "%d %d %d", &a, &b, &dist);
		pastures[a-1][b-1] = dist;
		pastures[b-1][a-1] = dist;
	}

	for(int i=0;i<numPastures;i++)
		pastures[i][i] = 0;

	list<int> path;
	path.push_back(cowPastures[0]);
	dfs(path);

	int minIndex = -1;
	int minSum = -1;
	for(int i=0;i<numPastures;i++)
	{
		int sum = 0;
		for(int j=0;j<numCows;j++)
		{
			if(pastures[i][ cowPastures[j] ] == -1)
			{
				sum = 1e9;
				break;
			}
			else
			{
				sum += pastures[i][ cowPastures[j] ];
			}
		}

		if(minIndex == -1 || sum < minSum)
		{
			minIndex = i;
			minSum = sum;
		}
	}

	fprintf(fout, "%d\n", minSum);

	fclose(fout);
	fclose(fin);

	return 0;
}