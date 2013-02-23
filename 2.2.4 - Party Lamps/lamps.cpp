/*
ID: general10
PROG: lamps
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


bool SolutionSort(const vector<int>& a, const vector<int>& b)
{
	if(a.size() != b.size())
		return a.size() < b.size();

	for(int i=0;i<a.size();i++)
	{
		if(a[i] != b[i])
			return a[i] < b[i];
	}

	return false;
}

int main() 
{
	FILE *fin  = fopen("lamps.in", "r");
	FILE *fout = fopen("lamps.out", "w");

	int numLamps;
	fscanf(fin, "%d", &numLamps);

	int numButtonPresses;
	fscanf(fin, "%d", &numButtonPresses);

	vector<int> finalLampsState(numLamps, -1);
	int lampIndex = -1;
	for(;;)	
	{
		fscanf(fin, "%d", &lampIndex);
		if(lampIndex == -1)
			break;

		finalLampsState[lampIndex-1] = 1;
	}

	vector<int> lampsOff;
	for(;;)	
	{
		fscanf(fin, "%d", &lampIndex);
		if(lampIndex == -1)
			break;

		finalLampsState[lampIndex-1] = 0;
	}

	vector< vector<int> > lampStates;
	int toggle[] = {1,0};
	for(int buttons = 0; buttons < 16; buttons++)
	{
		vector<int> lamps(numLamps, 1);

		if(buttons & 1)
			fill(lamps.begin(), lamps.end(), 0);

		if(buttons & 2)
		{
			for(int i=0;i<lamps.size();i+=2)
				lamps[i] = toggle[ lamps[i] ];
		}

		if(buttons & 4)
		{
			for(int i=1;i<lamps.size();i+=2)
				lamps[i] = toggle[ lamps[i] ];
		}

		if(buttons & 8)
		{
			for(int i=0;i<lamps.size();i+=3)
				lamps[i] = toggle[ lamps[i] ];
		}

		lampStates.push_back(lamps);
	}

	bool validBitCounts[5] = {false};
	if(numButtonPresses == 0)
	{
		validBitCounts[0] = true;
	}
	else if(numButtonPresses == 1)
	{
		validBitCounts[1] = true;
	}
	else if(numButtonPresses == 2)
	{
		validBitCounts[0] = true;
		validBitCounts[2] = true;
	}
	else if((numButtonPresses % 2) == 0)
	{
		validBitCounts[0] = true;
		validBitCounts[2] = true;
		validBitCounts[4] = true;
	}
	else	// (numButtonPresses%2) != 0
	{
		validBitCounts[1] = true;
		validBitCounts[3] = true;
	}


	vector< vector<int> > validSolutions;

	for(int i=0;i<16;i++)
	{
		int numBits = 0;
		for(int bit=0;bit<4;bit++)
		{
			if(i & (1<<bit))
				numBits++;
		}

		if(validBitCounts[numBits] == false)
			continue;

		bool ok = true;
		for(int lampIndex=0;lampIndex<numLamps;lampIndex++)
		{
			if(finalLampsState[lampIndex] != -1 && lampStates[i][lampIndex] != finalLampsState[lampIndex])
			{
				ok = false;
				break;
			}
		}

		if(ok == true)
		{
			if(find(validSolutions.begin(), validSolutions.end(), lampStates[i]) == validSolutions.end())
				validSolutions.push_back(lampStates[i]);
		}
	}

	if(validSolutions.size() == 0)
	{
		fprintf(fout, "IMPOSSIBLE\n");
	}
	else
	{
		sort(validSolutions.begin(), validSolutions.end(), SolutionSort);
		for(int i=0;i<validSolutions.size();i++)
		{
			for(int j=0;j<validSolutions[i].size();j++)
			{
				if(validSolutions[i][j])
					fprintf(fout, "1");
				else
					fprintf(fout, "0");
			}
			fprintf(fout, "\n");
		}
	}

	fclose(fout);
	fclose(fin);

	return 0;
}