/*
ID: general10
PROG: sort3
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


int main() 
{
	FILE *fin  = fopen("sort3.in", "r");
	FILE *fout = fopen("sort3.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	vector<int> sequence;
	sequence.reserve(1000);
	for(int i=0;i<n;i++)
	{
		int num;
		fscanf(fin, "%d\n", &num);
		sequence.push_back(num);
	}

	vector<int> sortedSequence = sequence;
	sort(sortedSequence.begin(), sortedSequence.end());

	int res = 0;
	int bad = 0;

	for(int i=0;i<sequence.size();i++)
	{
		if(sequence[i] == sortedSequence[i])
			continue;

		bool foundSwap = false;

		for(int j=0;j<n;j++)
		{
			if(sequence[i] == sortedSequence[j] && sequence[j] == sortedSequence[i])
			{
				swap(sequence[i], sequence[j]);
				res++;
				foundSwap = true;
				break;
			}
		}

		if(foundSwap == false)
		{
			for(int k=0;k<n;k++)
			{
				if(sequence[k] == sortedSequence[i] && sequence[k] != sortedSequence[k])
				{
					swap(sequence[i], sequence[k]);
					res++;
					break;
				}
			}
		}
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}