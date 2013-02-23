/*
ID: general10
PROG: clocks
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

struct State
{
	int Depth;
	int Path[36];
	int Clocks[9];

	State()
	{
		for(int i=0;i<9;i++) Clocks[i] = 0;
		for(int i=0;i<36;i++) Path[i] = 0;
		Depth = 0;
	}

	bool isSolved()
	{
		for(int i=0;i<9;i++)
			if(Clocks[i] != 0)
				return false;

		return true;
	}

	void Move1()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[1] += 3; res.Clocks[3] += 3; res.Clocks[4] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 1;
		res.Depth++;
		*this = res;
	}

	void Move2()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[1] += 3; res.Clocks[2] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 2;
		res.Depth++;
		*this = res;
	}

	void Move3()
	{
		State res = *this;
		res.Clocks[1] += 3; res.Clocks[2] += 3; res.Clocks[4] += 3; res.Clocks[5] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 3;
		res.Depth++;
		*this = res;
	}

	void Move4()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[3] += 3; res.Clocks[6] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 4;
		res.Depth++;
		*this = res;
	}

	void Move5()
	{
		State res = *this;
		res.Clocks[1] += 3; res.Clocks[3] += 3; res.Clocks[4] += 3; res.Clocks[5] += 3; res.Clocks[7] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 5;
		res.Depth++;
		*this = res;
	}

	void Move6()
	{
		State res = *this;
		res.Clocks[2] += 3; res.Clocks[5] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 6;
		res.Depth++;
		*this = res;
	}

	void Move7()
	{
		State res = *this;
		res.Clocks[3] += 3; res.Clocks[4] += 3; res.Clocks[6] += 3; res.Clocks[7] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 7;
		res.Depth++;
		*this = res;
	}

	void Move8()
	{
		State res = *this;
		res.Clocks[6] += 3; res.Clocks[7] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 8;
		res.Depth++;
		*this = res;
	}

	void Move9()
	{
		State res = *this;
		res.Clocks[4] += 3; res.Clocks[5] += 3; res.Clocks[7] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 9;
		res.Depth++;
		*this = res;
	}
};

bool StateByPath(const State& a, const State& b)
{
	if(a.Depth != b.Depth)
		return a.Depth < b.Depth;

	for(int i=0;i<a.Depth;i++)
	{
		if(a.Path[i] != b.Path[i])
			return a.Path[i] < b.Path[i];
	}

	return false;
}

vector<State> solutions;
string Go(State startState)
{
	int x;
	State state[9];

	for(int a=0;a<4;a++) { state[0] = startState; for(x=0;x<a;x++) state[0].Move1(); 
	for(int b=0;b<4;b++) { state[1] = state[0]; for(x=0;x<b;x++) state[1].Move2();
	for(int c=0;c<4;c++) { state[2] = state[1]; for(x=0;x<c;x++) state[2].Move3();
	for(int d=0;d<4;d++) { state[3] = state[2]; for(x=0;x<d;x++) state[3].Move4();
	for(int e=0;e<4;e++) { state[4] = state[3]; for(x=0;x<e;x++) state[4].Move5();
	for(int f=0;f<4;f++) { state[5] = state[4]; for(x=0;x<f;x++) state[5].Move6();
	for(int g=0;g<4;g++) { state[6] = state[5]; for(x=0;x<g;x++) state[6].Move7();
	for(int h=0;h<4;h++) { state[7] = state[6]; for(x=0;x<h;x++) state[7].Move8();
	for(int i=0;i<4;i++) { state[8] = state[7]; for(x=0;x<i;x++) state[8].Move9();
		if(state[8].isSolved())
			solutions.push_back(state[8]);
	} } } } } } } } }

	sort(solutions.begin(), solutions.end(), StateByPath);
	State bestSolution = solutions.front();

	string res = "";
	for(int i=0;i<bestSolution.Depth;i++)
	{
		res += (char)('0' + bestSolution.Path[i]);
		if(i < bestSolution.Depth-1)
			res += " ";
	}

	return res;
}

int main() 
{
	FILE *fin  = fopen("clocks.in", "r");
	FILE *fout = fopen("clocks.out", "w");

	State startState;

	for(int i=0;i<3;i++)
	{
		int clock[3];
		fscanf(fin, "%d %d %d\n", &clock[0], &clock[1], &clock[2]);
		for(int j=0;j<3;j++)
			startState.Clocks[(i*3)+j] = clock[j] % 12;
	}

	string res = Go(startState);

	fprintf(fout, "%s\n", res.c_str());

	fclose(fout);
	fclose(fin);

	return 0;
}