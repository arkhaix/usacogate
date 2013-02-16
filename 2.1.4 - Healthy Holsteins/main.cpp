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

bool NeedsMet(int feedsUsed)
{
	vector<int> vitaminsNeeded = vitaminReqs;

	for(int feedIndex=0;feedIndex<numFeedTypes;feedIndex++)
	{
		int feedBit = 1 << feedIndex;
		if( (feedsUsed & feedBit) == 0 )
			continue;

		for(int vitaminIndex = 0; vitaminIndex < numVitaminTypes; vitaminIndex++)
			vitaminsNeeded[vitaminIndex] -= vitaminsPerFeed[feedIndex][vitaminIndex];
	}

	bool ok = true;
	for(int vitaminIndex = 0; vitaminIndex < numVitaminTypes; vitaminIndex++)
	{
		if(vitaminsNeeded[vitaminIndex] > 0)
		{
			ok = false;
			break;
		}
	}

	return ok;
}

struct Solution
{
	int NumFeedsUsed;
	int FeedsUsed;

	Solution()
	{
		NumFeedsUsed = 0;
		FeedsUsed = 0;
	}

	Solution(int feedsUsed)
	{
		FeedsUsed = feedsUsed;

		NumFeedsUsed = 0;
		for(int i=0;i<numFeedTypes;i++)
			if(FeedsUsed & (1<<i))
				NumFeedsUsed++;
	}
};

bool operator<(const Solution& lhs, const Solution& rhs)
{
	if(lhs.NumFeedsUsed != rhs.NumFeedsUsed)
		return lhs.NumFeedsUsed < rhs.NumFeedsUsed;

	return lhs.FeedsUsed < rhs.FeedsUsed;
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

	Solution bestSolution((1<<(numFeedTypes+1))-1);

	for(int feedsUsed = 0; feedsUsed < (1<<numFeedTypes); feedsUsed++)
	{
		Solution solution(feedsUsed);
		if(bestSolution < solution)
			continue;

		if(NeedsMet(feedsUsed) == false)
			continue;

		bestSolution = solution;
	}

	fprintf(fout, "%d", bestSolution.NumFeedsUsed);
	for(int i=0;i<numFeedTypes;i++)
		if(bestSolution.FeedsUsed & (1<<i))
			fprintf(fout, " %d", i+1);
	fprintf(fout, "\n");

	fclose(fout);
	fclose(fin);

	return 0;
}