/*
ID: general10
PROG: milk
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

struct FarmerInfo
{
	int MilkProduced;
	int MilkPrice;
};

bool FarmersByPrice(const FarmerInfo& a, const FarmerInfo& b)
{
	return a.MilkPrice < b.MilkPrice;
}

int main() 
{
	FILE *fin  = fopen("milk.in", "r");
	FILE *fout = fopen("milk.out", "w");

	int targetAmount, numFarmers;
	fscanf(fin, "%d %d\n", &targetAmount, &numFarmers);

	vector<FarmerInfo> farmers;

	for(int i=0;i<numFarmers;i++)
	{
		FarmerInfo farmer;
		fscanf(fin, "%d %d\n", &farmer.MilkPrice, &farmer.MilkProduced);
		farmers.push_back(farmer);
	}

	sort(farmers.begin(), farmers.end(), FarmersByPrice);

	int amountSpent = 0;
	for(int i=0;i<farmers.size() && targetAmount>0;i++)
	{
		int purchaseAmount = min(farmers[i].MilkProduced, targetAmount);
		targetAmount -= purchaseAmount;
		amountSpent += purchaseAmount * farmers[i].MilkPrice;
	}

	fprintf(fout, "%d\n", amountSpent);

	fclose(fout);
	fclose(fin);

	return 0;
}