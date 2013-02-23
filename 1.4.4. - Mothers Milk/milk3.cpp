/*
ID: general10
PROG: milk3
LANG: C++
*/
#include <algorithm>
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

int ma, mb, mc;

struct abc
{
	int a, b, c;
	abc(int inA, int inB, int inC)
	{
		a = inA;
		b = inB;
		c = inC;
	}
};
map<abc, set<int> > memo;

bool operator<(const abc& a, const abc& b)
{
	if(a.a != b.a) return a.a < b.a;
	if(a.b != b.b) return a.b < b.b;
	return a.c < b.c;
}

set<int> dfs(int a, int b, int c)
{
	map<abc, set<int> >::iterator iter = memo.find(abc(a,b,c));
	if(iter != memo.end())
		return iter->second;

	set<int> ret;
	ret.insert(-1);
	memo.insert(make_pair(abc(a,b,c), ret));

	int na, nb, nc;
	set<int> res;

	set<int> asdf;
	int amt;

	if(a > 0)
	{
		amt=min(a,mb-b);
		na = a-amt;
		nb = b+amt;
		nc = c;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());

		amt=min(a,mc-c);
		na = a-amt;
		nb = b;
		nc = c+amt;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());
	}

	if(b > 0)
	{
		amt=min(b,ma-a);
		na = a+amt;
		nb = b-amt;
		nc = c;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());

		amt=min(b,mc-c);
		na = a;
		nb = b-amt;
		nc = c+amt;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());
	}

	if(c > 0)
	{
		amt=min(c,ma-a);
		na = a+amt;
		nb = b;
		nc = c-amt;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());

		amt=min(c,mb-b);
		na = a;
		nb = b+amt;
		nc = c-amt;
		asdf = dfs(na, nb, nc);
		res.insert(asdf.begin(), asdf.end());
	}

	if(a == 0)
		res.insert(c);

	memo[abc(a,b,c)] = res;

	return res;
}

int main() 
{
	FILE *fin  = fopen("milk3.in", "r");
	FILE *fout = fopen("milk3.out", "w");

	fscanf(fin, "%d %d %d\n", &ma, &mb, &mc);

	set<int> res = dfs(0,0,mc);
	res.erase(-1);

	set<int>::iterator endIter = res.end();
	--endIter;
	for(set<int>::iterator iter = res.begin(); iter != res.end(); ++iter)
	{
		fprintf(fout, "%d", *iter);
		if(iter != endIter)
			fprintf(fout, " ");
	}
	fprintf(fout, "\n");

	fclose(fout);
	fclose(fin);

	return 0;
}