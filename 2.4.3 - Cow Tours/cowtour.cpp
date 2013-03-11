/*
ID: general10
PROG: cowtour
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

double distance(int x1, int y1, int x2, int y2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

struct Pasture
{
	int x, y;
	int field;
	int adjacencyIndex;

	Pasture()
	{
		x = y = field = 0;
	}
};

int numPastures;
Pasture pastures[150];
int adjacency[150][150] = {0};

vector<Pasture*> field0;
vector<Pasture*> field1;
double distance0[150][150] = {0.0};
double distance1[150][150] = {0.0};

void fill(int pastureIndex)
{
	if(pastures[pastureIndex].field == 1)
		return;

	pastures[pastureIndex].field = 1;
	field1.push_back(&pastures[pastureIndex]);

	for(int i=0;i<numPastures;i++)
		if(adjacency[pastureIndex][i])
			fill(i);
}

void dist(vector<Pasture*>&field, double (&dist)[150][150])
{
	int n = field.size();

	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if(adjacency[ field[i]->adjacencyIndex ][ field[j]->adjacencyIndex ] != 0)
			{
				dist[i][j] = dist[j][i] = sqrt( 
				(field[i]->x - field[j]->x) * (field[i]->x - field[j]->x) +
				(field[i]->y - field[j]->y) * (field[i]->y - field[j]->y) );
			}
			else
			{
				dist[i][j] = dist[j][i] = 1e10;
			}
		}
	}
}

void fw(vector<Pasture*>& field, double (&dist)[150][150])
{
	int n = field.size();

	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
}

int main() 
{
	// Inputs

	FILE *fin  = fopen("cowtour.in", "r");
	FILE *fout = fopen("cowtour.out", "w");

	fscanf(fin, "%d", &numPastures);

	for(int i=0;i<numPastures;i++)
	{
		fscanf(fin, "%d %d\n", &pastures[i].x, &pastures[i].y);
		pastures[i].adjacencyIndex = i;
	}

	char buf[256];
	for(int i=0;i<numPastures;i++)
	{
		fgets(buf, 256, fin);
		for(int j=0;j<numPastures;j++)
			adjacency[i][j] = buf[j] - '0';
	}


	// Find the two fields

	fill(0);

	for(int i=0;i<numPastures;i++)
		if(pastures[i].field == 0)
			field0.push_back(&pastures[i]);


	// Find all-points min distances for the pastures in each field, separately
	
	dist(field0, distance0);
	fw(field0, distance0);

	dist(field1, distance1);
	fw(field1, distance1);


	// Connect each pair of points in the two fields, finding the maximal path
	// in each iteration, and keeping track of the smallest maximal path

	double res = 3e10;

	for(unsigned int i=0;i<field0.size();i++)
	{
		double maxDist0 = 0.0;
		for(unsigned int k=0;k<field0.size();k++)
		{
			if(k == i)
				continue;

			maxDist0 = max(maxDist0, distance0[i][k]);
		}

		for(unsigned int j=0;j<field1.size();j++)
		{
			double maxDist1 = 0.0;
			for(unsigned int k=0;k<field1.size();k++)
			{
				if(k == j)
					continue;

				maxDist1 = max(maxDist1, distance1[j][k]);
			}

			double curMaxDist = sqrt(
				(field0[i]->x - field1[j]->x) * (field0[i]->x - field1[j]->x) +
				(field0[i]->y - field1[j]->y) * (field0[i]->y - field1[j]->y)
				);

			curMaxDist += maxDist0 + maxDist1;

			res = min(res, curMaxDist);
		}
	}

	fprintf(fout, "%0.06f\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}