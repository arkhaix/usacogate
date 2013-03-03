/*
ID: general10
PROG: zerosum
LANG: C++
*/
#include <algorithm>
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

namespace Operator
{
	typedef int Type;

	enum
	{
		Add = 0,
		Subtract,
		Merge,

		NumOperators
	};
}	//namespace Operator

struct Operation
{
	Operator::Type op;
	int operand;
};

int n;
Operation ops[9];
set<int> seen;

FILE* fout;

int Eval()
{
	// Memo

	int visitKey = 0;
	for(int i=0;i<n;i++)
	{
		ops[i].operand = i+1;

		if(i != n-1)
		{
			visitKey <<= 2;
			visitKey += (int)ops[i].op;
		}
	}

	if(seen.find(visitKey) != seen.end())
		return -1;

	seen.insert(visitKey);


	// Merge

	for(int i=0;i<n-1;i++)
	{
		if(ops[i].op == Operator::Merge)
		{
			ops[i].operand *= 10;
			ops[i+1].operand += ops[i].operand;
		}
	}

	// ops is now suitable for printing
	// but we need to make more modifications in order to calculate the total easily
	// so copy it to a temporary buffer where that's safe

	Operation evalOps[9];
	for(int i=0;i<n;i++)
		evalOps[i] = ops[i];

	int startIndex = 0;
	while(evalOps[startIndex].op == Operator::Merge && startIndex < n)
		startIndex++;

	if(startIndex == n)
		return -1;

	Operation* currentOp = &evalOps[startIndex];
	for(int i=startIndex+1;i<n;i++)
	{
		if(evalOps[i].op == Operator::Merge && i!=n-1)
			continue;

		if(currentOp->op == Operator::Add)
			evalOps[i].operand += currentOp->operand;
		else if(currentOp->op == Operator::Subtract)
			evalOps[i].operand = currentOp->operand - evalOps[i].operand;

		currentOp = &evalOps[i];
	}

	return currentOp->operand;
}

void Print()
{
	for(int i=0;i<n-1;i++)
	{
		fprintf(fout, "%d", i+1);

		if(ops[i].op == Operator::Add)
			fprintf(fout, "+");
		else if(ops[i].op == Operator::Subtract)
			fprintf(fout, "-");
		else
			fprintf(fout, " ");
	}

	fprintf(fout, "%d\n", n);
}

void dfs(int index)
{
	if(index == n)
	{
		if(Eval() == 0)
			Print();

		return;
	}

	ops[index].op = Operator::Merge;
	dfs(index+1);

	ops[index].op = Operator::Add;
	dfs(index+1);

	ops[index].op = Operator::Subtract;
	dfs(index+1);
}

int main() 
{
	FILE *fin  = fopen("zerosum.in", "r");
	fout = fopen("zerosum.out", "w");

	fscanf(fin, "%d", &n);

	dfs(0);

	fclose(fout);
	fclose(fin);

	return 0;
}