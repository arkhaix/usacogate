/*
ID: general10
PROG: ttwo
LANG: C++
*/
#include <algorithm>
#include <cmath>
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


char grid[10][10];

namespace Direction
{
	typedef int Type;

	enum
	{
		North,
		South,
		East,
		West
	};

	Direction::Type Next[] =
	{
		Direction::East,
		Direction::West,
		Direction::South,
		Direction::North
	};
}

struct Entity
{
	int x;
	int y;
	Direction::Type direction;

	int Position()
	{
		return (x*10)+y;
	}

	int Serialize()
	{
		int res = (x*10)+y;	//max 99, 7 bits
		res <<= 2;
		res |= direction;	//max 3, 2 bits

		return res;
	}

	void Move()
	{
		if(	(direction == Direction::North) &&
			(y-1 >= 0) &&
			(grid[y-1][x] != '*') ) {
			y--;
		}
		else if((direction == Direction::South) &&
			(y+1 < 10) &&
			(grid[y+1][x] != '*') ) {
			y++;
		}
		else if((direction == Direction::West) &&
			(x-1 >= 0) &&
			(grid[y][x-1] != '*') ) {
			x--;
		}
		else if((direction == Direction::East) &&
			(x+1 < 10) &&
			(grid[y][x+1] != '*') ) {
			x++;
		}
		else {
			direction = Direction::Next[direction];
		}
	}
};

Entity cows;
Entity farmer;

int GetState()
{
	int res = cows.Serialize();
	res <<= 9;
	res |= farmer.Serialize();
	return res;
}

int main() 
{
	FILE *fin  = fopen("ttwo.in", "r");
	FILE *fout = fopen("ttwo.out", "w");

	char buffer[80];
	for(int i=0;i<10;i++)
		strcpy(grid[i], fgets(buffer, 80, fin));

	for(int x=0;x<10;x++) {
		for(int y=0;y<10;y++) {
			if(grid[y][x] == 'C') {
				cows.x = x;
				cows.y = y;
				cows.direction = Direction::North;
			}
			else if(grid[y][x] == 'F') {
				farmer.x = x;
				farmer.y = y;
				farmer.direction = Direction::North;
			}
		}
	}

	int res = 0;
	set<int> visited;
	int state = GetState();
	while(cows.Position() != farmer.Position() && visited.find(state) == visited.end())
	{
		visited.insert(state);

		cows.Move();
		farmer.Move();

		state = GetState();
		res++;
	}

	if(cows.Position() == farmer.Position())
		fprintf(fout, "%d\n", res);
	else
		fprintf(fout, "0\n");

	fclose(fout);
	fclose(fin);

	return 0;
}
