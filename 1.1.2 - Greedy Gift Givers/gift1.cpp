/*
ID: general10
PROG: gift1
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

int main() 
{
	FILE *fin  = fopen("gift1.in", "r");
	FILE *fout = fopen("gift1.out", "w");

	int np;
	map<string, int> initialAmountByPerson;
	map<string, int> finalAmountByPerson;
	vector<string> outputOrder;
	char tmp[1024];

	fscanf(fin, "%d\n", &np);
	for(int i=0;i<np;i++)
	{
		fscanf(fin, "%s\n", tmp);
		finalAmountByPerson.insert( make_pair(tmp, 0) );
		outputOrder.push_back(tmp);
	}

	for(int i=0;i<np;i++)
	{
		string p;
		fscanf(fin, "%s\n", tmp);
		p = tmp;

		int initialAmount, ng;
		fscanf(fin, "%d %d\n", &initialAmount, &ng);

		initialAmountByPerson[p] = initialAmount;

		if(ng == 0)
		{
			finalAmountByPerson[p] += initialAmount;
		}
		else
		{
			int keptAmount = initialAmount % ng;
			int givenAmount = initialAmount / ng;

			finalAmountByPerson[p] += keptAmount;

			for(int j=0;j<ng;j++)
			{
				string recipient;
				fscanf(fin, "%s\n", tmp);
				recipient = tmp;

				finalAmountByPerson[recipient] += givenAmount;
			}
		}
	}

	for(unsigned int i=0;i<outputOrder.size();i++)
	{
		string person = outputOrder[i];
		fprintf(fout, "%s %d\n", person.c_str(), finalAmountByPerson[person] - initialAmountByPerson[person]);
	}

	fclose(fin);
	fclose(fout);

	return 0;
}