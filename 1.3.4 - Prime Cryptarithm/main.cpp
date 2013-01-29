/*
ID: general10
PROG: crypt1
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

int okDigits[10] = {0};

bool valueOk(int n)
{
	while(n != 0)
	{
		int digit = n % 10;
		if(okDigits[digit] == 0)
			return false;

		n /= 10;
	}

	return true;
}

int main() 
{
	FILE *fin  = fopen("crypt1.in", "r");
	FILE *fout = fopen("crypt1.out", "w");

	int n;
	fscanf(fin, "%d\n", &n);

	vector<int> digits;
	for(int i=0;i<n;i++)
	{
		int digit;
		fscanf(fin, "%d", &digit);
		digits.push_back(digit);
		okDigits[digit] = 1;
	}

	int res = 0;

	int totalDigitCombinations = n*n*n*n*n;	///<this is safe. max(n,10) = 10. 10^5 = 100000.
	for(int i=0;i<totalDigitCombinations;i++)
	{
		int operand[2] = {0};
		int digitsPlaced = 0;
		int curNum = i;

		for(int digitsPlaced=0;digitsPlaced<3;digitsPlaced++)
		{
			int digit = curNum % n;
			curNum /= n;
			operand[0] *= 10;
			operand[0] += digits[digit];
		}

		for(int digitsPlaced=0;digitsPlaced<2;digitsPlaced++)
		{
			int digit = curNum % n;
			curNum /= n;
			operand[1] *= 10;
			operand[1] += digits[digit];
		}

		bool okResult = true;

		int a = (operand[1] % 10) * operand[0];
		if(a >= 1000 || valueOk(a) == false)
		{
			okResult = false;
		}
		else
		{
			int b = (operand[1] / 10) * operand[0];
			if(b >= 1000 || valueOk(b) == false)
			{
				okResult = false;
			}
			else
			{
				int c = (b*10) + a;
				if(c >= 10000 || valueOk(c) == false)
					okResult = false;
			}
		}

		if(okResult == true)
			res++;
	}

	fprintf(fout, "%d\n", res);

	fclose(fout);
	fclose(fin);

	return 0;
}