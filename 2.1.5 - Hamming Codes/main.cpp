/*
ID: general10
PROG: hamming
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

int numCodewords;
int numBits;
int minDistance;

bool dfs(vector<int>& solution, int start)
{
	if(solution.size() == numCodewords)
		return true;

	for(int i=start;i<(1<<numBits);i++)
	{
		bool ok = true;

		for(int k=0;k<solution.size();k++)
		{
			int distance = 0;

			for(int j=0;j<numBits;j++)
			{
				if((i & (1<<j)) && !(solution[k] & (1<<j)))
					distance++;
				else if(!(i & (1<<j)) && (solution[k] & (1<<j)))
					distance++;
			}

			if(distance < minDistance)
			{
				ok = false;
				break;
			}
		}

		if(ok == false)
			continue;

		solution.push_back(i);
		if(dfs(solution, i+1))
			return true;
		else
			solution.pop_back();
	}

	return false;
}

int main() 
{
	FILE *fin  = fopen("hamming.in", "r");
	FILE *fout = fopen("hamming.out", "w");

	fscanf(fin, "%d %d %d", &numCodewords, &numBits, &minDistance);

	vector<int> solution;
	dfs(solution, 0);

	int numbersThisLine = 0;
	for(int i=0;i<solution.size();i++)
	{
		fprintf(fout, "%d", solution[i]);
		numbersThisLine++;
		if(numbersThisLine == 10 && i != solution.size()-1)
		{
			fprintf(fout, "\n");
			numbersThisLine = 0;
		}
		else if(numbersThisLine < 10 && i != solution.size()-1)
		{
			fprintf(fout, " ");
		}
	}
	fprintf(fout, "\n");

	fclose(fout);
	fclose(fin);

	return 0;
}