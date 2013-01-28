/*
ID: general10
PROG: barn1
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int CowFlag = 0x01;
const int BoardFlag = 0x02;

int main() 
{
	FILE *fin  = fopen("barn1.in", "r");
	FILE *fout = fopen("barn1.out", "w");

	int maxBoards, numStalls, numCows;
	fscanf(fin, "%d %d %d\n", &maxBoards, &numStalls, &numCows);

	int stalls[200] = {0};
	for(int i=0;i<numCows;i++)
	{
		int stallIndex;
		fscanf(fin, "%d\n", &stallIndex);
		stallIndex--;
		stalls[stallIndex] = CowFlag;
	}

	int firstCow = -1;
	int lastCow = -1;
	for(int i=0;i<numStalls;i++)
	{
		if(stalls[i] & CowFlag)
		{
			if(firstCow == -1)
				firstCow = i;

			lastCow = i;
		}
	}

	for(int i=firstCow;i<=lastCow;i++)
		stalls[i] |= BoardFlag;

	for(int boardNum=2;boardNum<=maxBoards;boardNum++)
	{
		int bestLength = 0;
		int startIndex = 0;

		int curLength = 0;
		int curIndex = 0;

		for(int i=0;i<numStalls;i++)
		{
			if((stalls[i] & BoardFlag) == 0 || (stalls[i] & CowFlag))
			{
				if(curLength > bestLength)
				{
					bestLength = curLength;
					startIndex = curIndex;
				}

				curLength = 0;
				curIndex = 0;
			}
			else if(curLength > 0)
			{
				curLength++;
			}
			else
			{
				curIndex = i;
				curLength = 1;
			}
		}

		if(curLength > bestLength)
		{
			bestLength = curLength;
			startIndex = curIndex;
		}

		for(int i=0;i<bestLength;i++)
		{
			stalls[startIndex+i] &= ~BoardFlag;
		}
	}

	int res = 0;
	for(int i=0;i<numStalls;i++)
	{
		if(stalls[i] & BoardFlag)
			res++;
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}