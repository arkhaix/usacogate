/*
ID: general10
PROG: fracdec
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


int main() 
{
	FILE *fin  = fopen("fracdec.in", "r");
	FILE *fout = fopen("fracdec.out", "w");

	char buf[80];

	int numerator, denominator;
	fscanf(fin, "%d %d", &numerator, &denominator);

	list<int> results;
	map< pair<int, int>, list<int>::iterator > visited;

	map< pair<int, int>, list<int>::iterator >::iterator cycleIter = visited.end();
	while(cycleIter == visited.end() && numerator != 0)
	{
		list<int>::iterator iter = results.insert(results.end(), numerator / denominator);
		visited.insert( make_pair(make_pair(numerator, denominator), iter) );

		numerator %= denominator;

		numerator *= 10;

		cycleIter = visited.find( make_pair(numerator, denominator) );
	}

	string outStr = "";
	if(cycleIter == visited.end())
	{
		list<int>::iterator next = results.begin();
		sprintf(buf, "%d.", *next);
		outStr += buf;
		++next;
		if(next == results.end())
		{
			sprintf(buf, "0");
			outStr += buf;
		}
		else
		{
			for(; next != results.end(); ++next)
			{
				sprintf(buf, "%d", *next);
				outStr += buf;
			}
		}
	}
	else
	{
		list<int>::iterator next = results.begin();
		sprintf(buf, "%d.", *next);
		outStr += buf;
		++next;
		for(; next != cycleIter->second; ++next)
		{
			sprintf(buf, "%d", *next);
			outStr += buf;
		}
		outStr += "(";
		for(; next != results.end(); ++next)
		{
			sprintf(buf, "%d", *next);
			outStr += buf;
		}
		outStr += ")";
	}

	for(int i=0;i<outStr.length();i++)
	{
		fprintf(fout, "%c", outStr[i]);
		if( ((i+1) % 76) == 0 )
			fprintf(fout, "\n");
	}

	fprintf(fout, "\n");

	fclose(fout);
	fclose(fin);

	return 0;
}