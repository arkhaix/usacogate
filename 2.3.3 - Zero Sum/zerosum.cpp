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

int Eval()
{
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

	Operation* currentOp = &ops[0];
	for(int i=1;i<n;i++)
	{
		if(currentOp->op == Operator::Add)
			ops[i].operand += currentOp->operand;
		else if(currentOp->op == Operator::Subtract)
			ops[i].operand = currentOp->operand - ops[i].operand;
		else if(currentOp->op == Operator::Merge)
		{
			if(currentOp->operand >= 0)
				ops[i].operand = (currentOp->operand*10) + ops[i].operand;
			else
				ops[i].operand = (currentOp->operand*10) - ops[i].operand;
		}

		currentOp = &ops[i];
	}

	return currentOp->operand;
}

void Print()
{
	for(int i=0;i<n-1;i++)
	{
		printf("%d", i+1);

		if(ops[i].op == Operator::Add)
			printf("+");
		else if(ops[i].op == Operator::Subtract)
			printf("-");
		else
			printf(" ");
	}

	printf("%d\n", n);
}

void dfs(int index)
{
	if(index == n)
	{
		if(Eval() == 0)
			Print();

		return;
	}

	ops[index].op = Operator::Add;
	dfs(index+1);

	ops[index].op = Operator::Subtract;
	dfs(index+1);

	ops[index].op = Operator::Merge;
	dfs(index+1);
}

int main() 
{
	FILE *fin  = fopen("zerosum.in", "r");
	FILE *fout = fopen("zerosum.out", "w");

	fscanf(fin, "%d", &n);

	dfs(0);

	printf("--\n");

	n = 7;
	ops[0].op = Operator::Subtract;
	ops[1].op = Operator::Merge;
	ops[2].op = Operator::Add;
	ops[3].op = Operator::Add;
	ops[4].op = Operator::Add;
	ops[5].op = Operator::Add;
	seen.clear();
	Eval();


	fclose(fout);
	fclose(fin);

	return 0;
}