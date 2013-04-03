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
	unsigned long long res = 2;

	int a = 1, b = 2, c = 3;
	while(c < 4000000)
	{
		if( (c%2)==0 )
			res += c;

		a = b;
		b = c;
		c = a+b;
	}

	printf("%d\n", res);

	return 0;
}