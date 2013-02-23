/*
ID: general10
PROG: prefix
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
	FILE *fin  = fopen("prefix.in", "r");
	FILE *fout = fopen("prefix.out", "w");

	char tmp[1024];
	int maxPrimitiveLength = 0;
	set<string> primitives;
	for(;;)
	{
		fscanf(fin, "%s", tmp);

		string primitive = tmp;
		if(primitive == ".")
			break;

		maxPrimitiveLength = max(maxPrimitiveLength, (int)primitive.length());

		primitives.insert(primitive);
	}

	string sequence;
	for(;;)
	{
		int readStatus = fscanf(fin, "%s", tmp);
		if(readStatus == EOF)
			break;

		sequence += tmp;
	}
	
	vector<bool> reachable(sequence.length(), false);
	int failCount = 0;
	int lastPos = -1;
	for(int pos=0;pos<sequence.length() && failCount <= 10;pos++)
	{
		failCount++;

		for(int length=10;length>0;length--)
		{
			int oldPos = pos - (length-1);
			if(oldPos < 0)
				continue;

			string substr = sequence.substr(oldPos, length);
			if(primitives.find(substr) != primitives.end())
			{
				for(int mark=oldPos;mark < oldPos+length;mark++)
					reachable[mark] = true;

				reachable[pos] = true;
				failCount = 0;
				break;
			}
		}

		lastPos = pos;
	}

	int resIndex = 0;
	for(; resIndex < reachable.size() && reachable[resIndex] == true; resIndex++)
	{ }

	fprintf(fout, "%d\n", resIndex);

	fclose(fout);
	fclose(fin);

	return 0;
}