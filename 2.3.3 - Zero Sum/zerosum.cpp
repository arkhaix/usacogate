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
		Multiply,
		Divide,
		Merge,
		Ignore,

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

int Eval()
{
	for(int i=0;i<n-1;i++)
	{
		ops[i].operand += i+1;
		if(ops[i].op == Operator::Merge)
		{
			ops[i].operand *= 10;
			ops[i+1].operand += ops[i].operand;
			ops[i].op = Operator::Ignore;
		}
	}
	ops[n-1].operand += n;

	// ops is now suitable for printing
	// but we need to make more modifications in order to calculate the total easily
	// so copy it to a temporary buffer where that's safe

	Operation evalOps[9];
	for(int i=0;i<n;i++)
		evalOps[i] = ops[i];

	int startIndex = 0;
	while(evalOps[startIndex].op == Operator::Ignore)
		startIndex++;

	Operation* currentOp = &evalOps[startIndex];
	for(int i=startIndex+1;i<n;i++)
	{
		if(evalOps[i].op == Operator::Ignore && i!=n-1)
			continue;

		if(currentOp->op == Operator::Add)
			evalOps[i].operand += currentOp->operand;
		else if(currentOp->op == Operator::Subtract)
			evalOps[i].operand = currentOp->operand - evalOps[i].operand;
		else if(currentOp->op == Operator::Multiply)
			evalOps[i].operand *= currentOp->operand;
		else
			evalOps[i].operand = currentOp->operand / evalOps[i].operand;

		currentOp = &evalOps[i];
	}

	return currentOp->operand;
}

void Print()
{
	for(int i=0;i<n-1;i++)
	{
		if(ops[i].op == Operator::Ignore)
			continue;

		printf("%d", ops[i].operand);
		if(ops[i].op == Operator::Add)
			printf("+");
		else if(ops[i].op == Operator::Subtract)
			printf("-");
		else if(ops[i].op == Operator::Multiply)
			printf("*");
		else
			printf("/");
	}

	printf("%d\n", ops[n-1].operand);
}

int main() 
{
	FILE *fin  = fopen("zerosum.in", "r");
	FILE *fout = fopen("zerosum.out", "w");

	//fscanf(fin, "%d", &n);

	n = 4;
	ops[0].op = Operator::Merge;
	ops[1].op = Operator::Add;
	ops[2].op = Operator::Merge;

	//n = 9;
	//for(int i=0;i<9;i++)
	//	ops[i].op = Operator::Multiply;

	int x = Eval();
	printf("%d\n", x);

	Print();

	fclose(fout);
	fclose(fin);

	return 0;
}