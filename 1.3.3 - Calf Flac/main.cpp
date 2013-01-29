/*
ID: general10
PROG: calfflac
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

string input;
int nextChar(int startIndex, int direction)
{
	int index = startIndex;

	index += direction;
	while(index >= 0 && index < input.length())
	{
		if( (input[index] >= 'a' && input[index] <= 'z') || 
			(input[index] >= 'A' && input[index] <= 'Z'))
			return index;

		index += direction;
	}

	return -1;
}

int main() 
{
	FILE *fin  = fopen("calfflac.in", "r");
	FILE *fout = fopen("calfflac.out", "w");

	char tmp[1024];

	while(true)
	{
		const char* readStatus = fgets(tmp, 1024, fin);
		if(readStatus == NULL)
			break;

		input += tmp;
	}

	int longestPalindrome = 0;
	string result = "";

	for(int i=nextChar(-1, 1); i != -1; i=nextChar(i, 1))
	{
		// Odd-length palindromes

		int palindromeLength = 1;
		int leftIndex = i;
		int rightIndex = i;

		while(true)
		{
			int testLeftIndex = nextChar(leftIndex, -1);
			int testRightIndex = nextChar(rightIndex, 1);

			int x = 0;
			int y = 0;
			if(testLeftIndex >= 0)
				x = tolower(input[testLeftIndex]);
			if(testRightIndex >= 0)
				y = tolower(input[testRightIndex]);

			if(testLeftIndex == -1 || testRightIndex == -1 || tolower(input[testLeftIndex]) != tolower(input[testRightIndex]))
				break;

			leftIndex = testLeftIndex;
			rightIndex = testRightIndex;

			palindromeLength += 2;
		}

		if(palindromeLength > longestPalindrome)
		{
			longestPalindrome = palindromeLength;
			result = input.substr(leftIndex, (rightIndex - leftIndex) + 1);
		}


		// Even-length palindromes

		leftIndex = i;
		rightIndex = nextChar(i, 1);

		if(rightIndex != -1 && input[leftIndex] == input[rightIndex])
		{
			palindromeLength = 2;

			while(true)
			{
				int testLeftIndex = nextChar(leftIndex, -1);
				int testRightIndex = nextChar(rightIndex, 1);

				if(testLeftIndex == -1 || testRightIndex == -1 || _tolower(input[testLeftIndex]) != _tolower(input[testRightIndex]))
					break;

				leftIndex = testLeftIndex;
				rightIndex = testRightIndex;

				palindromeLength += 2;
			}
		}

		if(palindromeLength > longestPalindrome)
		{
			longestPalindrome = palindromeLength;
			result = input.substr(leftIndex, (rightIndex - leftIndex) + 1);
		}
	}

	fprintf(fout, "%d\n", longestPalindrome);
	fprintf(fout, "%s\n", result.c_str());

	fclose(fout);
	fclose(fin);

	return 0;
}