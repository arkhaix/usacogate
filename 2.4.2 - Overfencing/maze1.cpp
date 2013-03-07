/*
ID: general10
PROG: maze1
LANG: C++
*/
#include <algorithm>
#include <climits>
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


struct Node
{
	Node* Connections[4];
	int NumConnections;
	bool IsExit;
	bool Visited;
	int CurDistance;
	int MinDistance;

	Node()
	{
		for(int i=0;i<4;i++)
			Connections[i] = NULL;
		NumConnections = 0;
		IsExit = false;
		Visited = false;
		CurDistance = INT_MAX;
		MinDistance = INT_MAX;
	}
};

int main() 
{
	FILE *fin  = fopen("maze1.in", "r");
	FILE *fout = fopen("maze1.out", "w");

	Node graph[101][39];
	char grid[203][80];

	int width, height;
	fscanf(fin, "%d %d\n", &width, &height);

	int gridWidth = 1+(2*width);
	int gridHeight = 1+(2*height);

	char buffer[80];
	for(int i=0;i<gridHeight;i++)
		strcpy(grid[i], fgets(buffer, 80, fin));

	vector<Node*> exits;

	for(int r=0;r<height;r++) {
		int gridR = 1+(r*2);
		for(int c=0;c<width;c++) {
			int gridC = 1+(c*2);

			Node* node = &graph[r][c];

			if(grid[gridR-1][gridC] == ' ') {
				if(r == 0) { 
					node->IsExit = true;
					exits.push_back(node);
				}
				else {
					node->Connections[ node->NumConnections ] = &graph[r-1][c];
					node->NumConnections++;
				}
			}

			if(grid[gridR+1][gridC] == ' ') {
				if(r == height-1) { 
					node->IsExit = true;
					exits.push_back(node);
				}
				else {
					node->Connections[ node->NumConnections ] = &graph[r+1][c];
					node->NumConnections++;
				}
			}

			if(grid[gridR][gridC-1] == ' ') {
				if(c == 0) { 
					node->IsExit = true;
					exits.push_back(node);
				}
				else {
					node->Connections[ node->NumConnections ] = &graph[r][c-1];
					node->NumConnections++;
				}
			}

			if(grid[gridR][gridC+1] == ' ') {
				if(c == width-1) { 
					node->IsExit = true;
					node->MinDistance = 0;
					exits.push_back(node);
				}
				else {
					node->Connections[ node->NumConnections ] = &graph[r][c+1];
					node->NumConnections++;
				}
			}
		}
	}

	for(int exitNodeIndex = 0; exitNodeIndex < exits.size(); exitNodeIndex++) {
		Node* source = exits[exitNodeIndex];

		for(int r=0;r<height;r++) {
			for(int c=0;c<width;c++) {
				if(&graph[r][c] == source)
					graph[r][c].CurDistance = 0;
				else
					graph[r][c].CurDistance = INT_MAX;

				graph[r][c].Visited = false;
			}
		}

		while(true)
		{
			Node* curNode = NULL;
			for(int r=0;r<height;r++)
				for(int c=0;c<width;c++)
					if(graph[r][c].Visited == false && 
					(curNode == NULL || graph[r][c].CurDistance < curNode->CurDistance) )
						curNode = &graph[r][c];

			if(curNode == NULL)
				break;

			curNode->Visited = true;

			for(int i=0;i<curNode->NumConnections;i++) {
				Node* connection = curNode->Connections[i];
				connection->CurDistance = min(connection->CurDistance, curNode->CurDistance+1);
			}

			for(int r=0;r<height;r++)
				for(int c=0;c<width;c++)
					graph[r][c].MinDistance = min(graph[r][c].MinDistance, graph[r][c].CurDistance);
		}
	}

	int res = 0;
	for(int r=0;r<height;r++)
		for(int c=0;c<width;c++)
			res = max(res, graph[r][c].MinDistance);

	fprintf(fout, "%d\n", res+1);

	fclose(fout);
	fclose(fin);

	return 0;
}