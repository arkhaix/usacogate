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
	char Depth;
	char Path[36];
	char Clocks[9];

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

	static set<long long> Visited;
};

set<long long> State::Visited;

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

State startState;

bool Success(int* testClocks)
{
	int total = 0;
	for(int i=0;i<9;i++)
		total += testClocks[i];

	return total == (12*9);
}

string Go()
{
	queue<State>* heapStates = new queue<State>();
	queue<State>& states = *heapStates;
	states.push(startState);

	vector<State> solutions;

	while(solutions.empty() && !states.empty())
	{
		State curState = states.front();
		states.pop();

		if(State::Visited.find(curState.ToKey()) != State::Visited.end())
			continue;

		State::Visited.insert(curState.ToKey());

		State nextState = curState.Move1();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move2();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move3();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move4();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move5();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move6();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move7();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move8();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);

		nextState = curState.Move9();
		states.push(nextState);
		if(nextState.isSolved())
			solutions.push_back(nextState);
	}

	State::Visited.clear();

	sort(solutions.begin(), solutions.end(), StateByPath);
	State bestSolution = solutions.front();

	string res = "";
	for(int i=0;i<bestSolution.Depth;i++)
	{
		res += (char)('0' + bestSolution.Path[i]);
		if(i < bestSolution.Depth-1)
			res += " ";
	}

	delete heapStates;

	return res;
}

int main() 
{
	FILE *fin  = fopen("clocks.in", "r");
	FILE *fout = fopen("clocks.out", "w");

	for(int i=0;i<3;i++)
	{
		int clock[3];
		fscanf(fin, "%d %d %d\n", &clock[0], &clock[1], &clock[2]);
		for(int j=0;j<3;j++)
			startState.Clocks[(i*3)+j] = clock[j] % 12;
	}

	string res = Go();

	fprintf(fout, "%s\n", res.c_str());

	fclose(fout);
	fclose(fin);

	return 0;
}