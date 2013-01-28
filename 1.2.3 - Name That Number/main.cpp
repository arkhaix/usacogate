/*
ID: general10
PROG: namenum
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

struct DictEntry
{
	string name;
	string val;
};


int main() 
{
	FILE *fin  = fopen("namenum.in", "r");
	FILE *fout = fopen("namenum.out", "w");
	FILE* fdict = fopen("dict.txt", "r");

	char tmp[1024] = {0};

	/*
		  2: A,B,C     5: J,K,L    8: T,U,V
		  3: D,E,F     6: M,N,O    9: W,X,Y
		  4: G,H,I     7: P,R,S
	*/

	int keyMap[] =
	{
		2,2,2,
		3,3,3,
		4,4,4,
		5,5,5,
		6,6,6,
		7,7,7,7,
		8,8,8,
		9,9,9,9
	};

	// Read dict
	vector<DictEntry> dictionary;

	int dictStatus = 0;
	while(true)
	{
		dictStatus = fscanf(fdict, "%s\n", tmp);
		if(dictStatus == EOF)
			break;

		DictEntry entry;
		entry.name = tmp;

		for(int i=0;i<entry.name.length();i++)
			entry.val += (char)('0' + keyMap[entry.name[i] - 'A']);

		dictionary.push_back(entry);
	}


	fscanf(fin, "%s\n", tmp);
	string sourceVal = tmp;
	bool resultFound = false;
	
	for(unsigned int i=0;i<dictionary.size();i++)
	{
		if(dictionary[i].val == sourceVal)
		{
			fprintf(fout, "%s\n", dictionary[i].name.c_str());
			resultFound = true;
		}
	}

	if(resultFound == false)
		fprintf(fout, "NONE\n");

	fclose(fdict);
	fclose(fout);
	fclose(fin);

	return 0;
}