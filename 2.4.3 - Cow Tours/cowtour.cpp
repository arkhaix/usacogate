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
		x = 0;
		y = 0;
		field = -1;
	}
};

int numPastures;
Pasture pastures[150];
int adjacency[150][150] = {0};
double distances[150][150] = {0};

struct Field
{
	vector<Pasture*> pastures;
};

vector<Field> fields;

void fill(int fieldIndex, int pastureIndex)
{
	if(pastures[pastureIndex].field != -1)
		return;

	pastures[pastureIndex].field = fieldIndex;
	fields[fieldIndex].pastures.push_back(&pastures[pastureIndex]);

	for(int i=0;i<numPastures;i++)
		if(adjacency[pastureIndex][i])
			fill(fieldIndex, i);
}

void dist(vector<Pasture*>&field)
{
	int n = field.size();

	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			int ai = field[i]->adjacencyIndex;
			int aj = field[j]->adjacencyIndex;

			if(adjacency[ai][aj] != 0)
			{
				distances[ai][aj] = distances[aj][ai] = sqrt( 
				(field[i]->x - field[j]->x) * (field[i]->x - field[j]->x) +
				(field[i]->y - field[j]->y) * (field[i]->y - field[j]->y) );
			}
			else
			{
				distances[ai][aj] = distances[aj][ai] = 1e10;
			}
		}
	}
}

void fw(vector<Pasture*>& field)
{
	int n = field.size();

	for(int k=0;k<n;k++)
	{
		int ak = field[k]->adjacencyIndex;
		for(int i=0;i<n;i++)
		{
			int ai = field[i]->adjacencyIndex;
			for(int j=0;j<n;j++)
			{
				int aj = field[j]->adjacencyIndex;

				if(distances[ai][aj] > distances[ai][ak] + distances[ak][aj])
					distances[ai][aj] = distances[ai][ak] + distances[ak][aj];
			}
		}
	}
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


	// Find all the fields

	int fieldId = 0;
	for(int i=0;i<numPastures;i++)
	{
		if(pastures[i].field == -1)
		{
			Field f;
			fields.push_back(f);

			fill(fieldId, i);
			fieldId++;
		}
	}


	// Find all-points min distances for the pastures in each field, separately
	
	for(unsigned int i=0;i<fields.size();i++)
	{
		dist(fields[i].pastures);
		fw(fields[i].pastures);
	}


	// Connect each pair of points in the separate fields, finding the maximal path
	// in each iteration, and keeping track of the smallest maximal path

	double maxCombinedDist = 3e10;

	for(unsigned int fieldA=0;fieldA<fields.size();fieldA++)
	{
		for(unsigned int fieldB=fieldA+1;fieldB<fields.size();fieldB++)
		{
			for(unsigned int i=0;i<fields[fieldA].pastures.size();i++)
			{
				int ai = fields[fieldA].pastures[i]->adjacencyIndex;

				double maxDist0 = 0.0;
				for(unsigned int k=0;k<fields[fieldA].pastures.size();k++)
				{
					if(k == i)
						continue;

					int ak = fields[fieldA].pastures[k]->adjacencyIndex;

					maxDist0 = max(maxDist0, distances[ai][ak]);
				}

				for(unsigned int j=0;j<fields[fieldB].pastures.size();j++)
				{
					int aj = fields[fieldB].pastures[j]->adjacencyIndex;

					double maxDist1 = 0.0;
					for(unsigned int k=0;k<fields[fieldB].pastures.size();k++)
					{
						if(k == j)
							continue;

						int ak = fields[fieldB].pastures[k]->adjacencyIndex;

						maxDist1 = max(maxDist1, distances[aj][ak]);
					}

					double curMaxDist = sqrt(
						(fields[fieldA].pastures[i]->x - fields[fieldB].pastures[j]->x) * (fields[fieldA].pastures[i]->x - fields[fieldB].pastures[j]->x) +
						(fields[fieldA].pastures[i]->y - fields[fieldB].pastures[j]->y) * (fields[fieldA].pastures[i]->y - fields[fieldB].pastures[j]->y)
						);

					curMaxDist += maxDist0 + maxDist1;

					maxCombinedDist = min(maxCombinedDist, curMaxDist);
				}
			}
		}
	}


	// Sometimes, a field can have a larger path within itself than any maximal 
	// path resulting from combining two fields.
	double res = 0.0;

	for(unsigned int i=0;i<fields.size();i++)
		for(unsigned int j=0;j<fields[i].pastures.size();j++)
			for(unsigned int k=j+1;k<fields[i].pastures.size();k++)
				res = max(res, distances[ fields[i].pastures[j]->adjacencyIndex ][ fields[i].pastures[k]->adjacencyIndex ]);

	res = max(res, maxCombinedDist);


	fprintf(fout, "%0.06f\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}