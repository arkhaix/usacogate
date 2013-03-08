/*
ID: general10
PROG: comehome
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
	Node* Connections[52];
	int EdgeLengths[52];
	int NumConnections;
	bool Visited;
	bool HasCow;
	unsigned int Distance;

	Node()
	{
		NumConnections = 0;
		for(int i=0;i<52;i++) 
		{
			Connections[i] = NULL;
			EdgeLengths[i] = 0;
		}

		Visited = false;
		HasCow = false;
		Distance = INT_MAX;
	}

	void AddConnection(Node* connection, int distance)
	{
		if(connection == this)
			return;

		for(int i=0;i<NumConnections;i++)
		{
			if(Connections[i] == connection)
			{
				EdgeLengths[i] = min(EdgeLengths[i], distance);

				for(int j=0;j<connection->NumConnections;j++)
				{
					if(connection->Connections[j] == this)
					{
						connection->EdgeLengths[j] = min(connection->EdgeLengths[j], distance);
						return;
					}
				}

				return;
			}
		}

		Connections[NumConnections] = connection;
		EdgeLengths[NumConnections] = distance;
		NumConnections++;

		if(connection->NumConnections == 0 || connection->Connections[connection->NumConnections-1] != this)
			connection->AddConnection(this, distance);
	}
};

int main() 
{
	FILE *fin  = fopen("comehome.in", "r");
	FILE *fout = fopen("comehome.out", "w");

	int numPaths;
	fscanf(fin, "%d\n", &numPaths);

	Node nodes[52];

	for(int i=0;i<numPaths;i++)
	{
		char startNode, endNode;
		int distance;
		fscanf(fin, "%c %c %d\n", &startNode, &endNode, &distance);

		if(startNode >= 'A' && startNode <= 'Z')
		{
			startNode = 26 + (startNode - 'A');
			nodes[startNode].HasCow = true;
		}
		else
		{
			startNode = startNode - 'a';
		}
		
		if(endNode >= 'A' && endNode <= 'Z')
		{
			endNode = 26 + (endNode - 'A');
			nodes[endNode].HasCow = true;
		}
		else
		{
			endNode = endNode - 'a';
		}

		nodes[startNode].AddConnection(&nodes[endNode], distance);
	}
	
	Node* source = &nodes[51];
	source->Distance = 0;

	while(true)
	{
		Node* next = NULL;
		for(int i=0;i<52;i++)
		{
			if(nodes[i].Visited == false && (next == NULL || nodes[i].Distance < next->Distance))
				next = &nodes[i];
		}

		if(next == NULL)
			break;

		for(int i=0;i<next->NumConnections;i++)
		{
			next->Connections[i]->Distance = min(
				next->Connections[i]->Distance,
				next->Distance + next->EdgeLengths[i]
			);
		}

		next->Visited = true;
	}

	Node* best = NULL;
	int bestIndex = -1;
	for(int i=0;i<51;i++)
	{
		if(nodes[i].HasCow && (best == NULL || nodes[i].Distance < best->Distance))
		{
			best = &nodes[i];
			bestIndex = i;
		}
	}

	fprintf(fout, "%c %d\n", (bestIndex < 26) ? ('a'+bestIndex) : ('A' + (bestIndex-26)), best->Distance);

	fclose(fout);
	fclose(fin);

	return 0;
}