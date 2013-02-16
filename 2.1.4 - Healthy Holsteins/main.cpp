/*
ID: general10
PROG: holstein
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

int numVitaminTypes;
vector<int> vitaminReqs;

int numFeedTypes;
vector< vector<int> > vitaminsPerFeed;

vector<int> bfs(vector<int> feedsUsed, vector<int> vitaminsNeeded)
{
	bool success = true;
	for(int i=0; i < vitaminsNeeded.size(); i++)
	{
		if(vitaminsNeeded[i] > 0)
		{
			success = false;
			break;
		}
	}

	if(success == true)
	{
		return feedsUsed;
	}

	int totalVitaminsNeeded = 0;
	for(int i=0; i < vitaminsNeeded.size(); i++)
		if(vitaminsNeeded[i] > 0)
			totalVitaminsNeeded += vitaminsNeeded[i];

	vector<int> res;
	for(int feedIndex=0; feedIndex < numFeedTypes; feedIndex++)
	{
		if( find(feedsUsed.begin(), feedsUsed.end(), feedIndex) != feedsUsed.end() )
			continue;

		vector<int> potentialVitaminsNeeded = vitaminsNeeded;
		for(int vitaminIndex=0; vitaminIndex < numVitaminTypes; vitaminIndex++)
			potentialVitaminsNeeded[vitaminIndex] -= vitaminsPerFeed[feedIndex][vitaminIndex];

		int totalPotentialVitaminsNeeded = 0;
		for(int vitaminIndex=0; vitaminIndex < numVitaminTypes; vitaminIndex++)
			if(potentialVitaminsNeeded[vitaminIndex] > 0)
				totalPotentialVitaminsNeeded += potentialVitaminsNeeded[vitaminIndex];

		if(totalPotentialVitaminsNeeded < totalVitaminsNeeded)
		{
			feedsUsed.push_back(feedIndex);
			vector<int> potentialResult = bfs(feedsUsed, potentialVitaminsNeeded);
			feedsUsed.pop_back();
			bool better = false;

			if(res.size() == 0 || potentialResult.size() < res.size())
			{
				sort(potentialResult.begin(), potentialResult.end());
				better = true;
			}
			else if(potentialResult.size() > 0 && potentialResult.size() == res.size())
			{
				sort(potentialResult.begin(), potentialResult.end());
				for(int i=0;i<potentialResult.size();i++)
				{
					if(potentialResult[i] < res[i])
					{
						better = true;
						break;
					}
					else if(potentialResult[i] > res[i])
						break;
				}
			}

			if(better == true)
				res = potentialResult;
		}
	}

	return res;
}

int main() 
{
	FILE *fin  = fopen("holstein.in", "r");
	FILE *fout = fopen("holstein.out", "w");

	fscanf(fin, "%d", &numVitaminTypes);
	for(int i=0;i<numVitaminTypes;i++)
	{
		int req;
		fscanf(fin, "%d", &req);
		vitaminReqs.push_back(req);
	}

	fscanf(fin, "%d", &numFeedTypes);
	for(int i=0;i<numFeedTypes;i++)
	{
		vector<int> vitaminsThisFeed;

		for(int j=0;j<numVitaminTypes;j++)
		{
			int vitamins;
			fscanf(fin, "%d", &vitamins);
			vitaminsThisFeed.push_back(vitamins);
		}

		vitaminsPerFeed.push_back(vitaminsThisFeed);
	}

	vector<int> empty;
	vector<int> res = bfs(empty, vitaminReqs);

	fprintf(fout, "%d", res.size());
	for(int i=0;i<res.size();i++)
		fprintf(fout, " %d", res[i]+1);
	fprintf(fout, "\n");

	fclose(fout);
	fclose(fin);

	return 0;
}