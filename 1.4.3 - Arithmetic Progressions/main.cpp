/*
ID: general10
PROG: ariprog
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

struct Progression
{
	int Start;
	int Increment;
};

bool ProgressionByIncrement(const Progression& a, const Progression& b)
{
	if(a.Increment != b.Increment)
		return a.Increment < b.Increment;

	return a.Start < b.Start;
}

int main() 
{
	FILE *fin  = fopen("ariprog.in", "r");
	FILE *fout = fopen("ariprog.out", "w");

	int progressionLength;
	int bisquareLimit;
	fscanf(fin, "%d\n", &progressionLength);
	fscanf(fin, "%d\n", &bisquareLimit);

	set<int> bisquares;
	int maxBisquare = -1;

	for(int p=0;p<=bisquareLimit;p++)
		for(int q=0;q<=bisquareLimit;q++)
		{
			maxBisquare = (p*p)+(q*q);
			bisquares.insert(maxBisquare);
		}

	int maxInterval = maxBisquare / (progressionLength-1);

	vector<Progression> progressions;

	for(set<int>::iterator iter = bisquares.begin(); iter != bisquares.end(); ++iter)
	{
		for(int j=1;j<=maxInterval;j++)
		{
			bool found = true;
			for(int k=1;k<progressionLength;k++)
			{
				int nextValue = *iter + (k*j);
				if(bisquares.find(nextValue) == bisquares.end())
				{
					found = false;
					break;
				}
			}

			if(found == true)
			{
				Progression progression;
				progression.Start = *iter;
				progression.Increment = j;
				progressions.push_back(progression);
			}
		}
	}


	if(progressions.size() == 0)
	{
		fprintf(fout, "NONE\n");
	}
	else
	{
		sort(progressions.begin(), progressions.end(), ProgressionByIncrement);
		for(int i=0;i<progressions.size();i++)
			fprintf(fout, "%d %d\n", progressions[i].Start, progressions[i].Increment);
	}

	fclose(fout);
	fclose(fin);

	return 0;
}