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

	long long ToKey()
	{
		long long key = 0;

		for(int i=0;i<9;i++)
		{
			key *= 12;
			key += Clocks[i];
		}

		return key;
	}

	bool isSolved()
	{
		for(int i=0;i<9;i++)
			if(Clocks[i] != 0)
				return false;

		return true;
	}

	State Move1()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[1] += 3; res.Clocks[3] += 3; res.Clocks[4] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 1;
		res.Depth++;
		return res;
	}

	State Move2()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[1] += 3; res.Clocks[2] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 2;
		res.Depth++;
		return res;
	}

	State Move3()
	{
		State res = *this;
		res.Clocks[1] += 3; res.Clocks[2] += 3; res.Clocks[4] += 3; res.Clocks[5] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 3;
		res.Depth++;
		return res;
	}

	State Move4()
	{
		State res = *this;
		res.Clocks[0] += 3; res.Clocks[3] += 3; res.Clocks[6] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 4;
		res.Depth++;
		return res;
	}

	State Move5()
	{
		State res = *this;
		res.Clocks[1] += 3; res.Clocks[3] += 3; res.Clocks[4] += 3; res.Clocks[5] += 3; res.Clocks[7] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 5;
		res.Depth++;
		return res;
	}

	State Move6()
	{
		State res = *this;
		res.Clocks[2] += 3; res.Clocks[5] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 6;
		res.Depth++;
		return res;
	}

	State Move7()
	{
		State res = *this;
		res.Clocks[3] += 3; res.Clocks[4] += 3; res.Clocks[6] += 3; res.Clocks[7] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 7;
		res.Depth++;
		return res;
	}

	State Move8()
	{
		State res = *this;
		res.Clocks[6] += 3; res.Clocks[7] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 8;
		res.Depth++;
		return res;
	}

	State Move9()
	{
		State res = *this;
		res.Clocks[4] += 3; res.Clocks[5] += 3; res.Clocks[7] += 3; res.Clocks[8] += 3;
		for(int i=0;i<9;i++) res.Clocks[i] %= 12;
		res.Path[ res.Depth ] = 9;
		res.Depth++;
		return res;
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
set<int> visited;
void Dfs(int maxDepth, State& curState)
{
	if(curState.Depth > maxDepth)
		return;

	if(curState.isSolved())
	{
		solutions.push_back(curState);
		return;
	}

	int key = curState.ToKey();
	set<int>::iterator keyIter = visited.find(key);

	if(keyIter != visited.end())
		return;

	visited.insert(key);

	State nextState = curState.Move1();
	Dfs(maxDepth, nextState);

	nextState = curState.Move2();
	Dfs(maxDepth, nextState);

	nextState = curState.Move3();
	Dfs(maxDepth, nextState);

	nextState = curState.Move4();
	Dfs(maxDepth, nextState);

	nextState = curState.Move5();
	Dfs(maxDepth, nextState);

	nextState = curState.Move6();
	Dfs(maxDepth, nextState);

	nextState = curState.Move7();
	Dfs(maxDepth, nextState);

	nextState = curState.Move8();
	Dfs(maxDepth, nextState);

	nextState = curState.Move9();
	Dfs(maxDepth, nextState);
}

string Go(State startState)
{
	int maxDepth = 0;
	while(solutions.empty())
	{
		visited.clear();
		maxDepth++;
		Dfs(maxDepth, startState);
	}

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