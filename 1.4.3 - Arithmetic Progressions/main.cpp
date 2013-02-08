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

	vector<int> bisquares;
	set<int> bisquaresSet;

	for(int p=0;p<=bisquareLimit;p++)
		for(int q=0;q<=bisquareLimit;q++)
			bisquaresSet.insert((p*p)+(q*q));

	for(set<int>::iterator iter = bisquaresSet.begin(); iter != bisquaresSet.end(); ++iter)
		bisquares.push_back(*iter);

	sort(bisquares.begin(), bisquares.end());

	vector<int> diffs(bisquares.size());
	diffs[0] = 0;
	for(int i=1;i<bisquares.size();i++)
		diffs[i] = bisquares[i]-bisquares[i-1];

	Progression currentProgression;
	vector<Progression> progressions;

	int run = 1;
	int res = 0;
	for(int i=1;i<diffs.size();i++)
	{
		if(diffs[i] == diffs[i-1])
		{
			run++;
		}
		else
		{
			run = 1;
			currentProgression.Start = bisquares[i];
		}

		if(run == progressionLength)
		{
			currentProgression.Increment = diffs[i];
			progressions.push_back(currentProgression);

			run = 1;
			currentProgression.Start = bisquares[i];
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