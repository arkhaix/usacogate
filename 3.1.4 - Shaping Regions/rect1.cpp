
/*
ID: general10
PROG: rect1
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
	FILE *fin  = fopen("rect1.in", "r");
	FILE *fout = fopen("rect1.out", "w");

	int numPrimes, nthHumble;
	fscanf(fin, "%d %d", &numPrimes, &nthHumble);


	fclose(fout);
	fclose(fin);

	return 0;
}