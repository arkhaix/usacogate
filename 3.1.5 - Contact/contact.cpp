/*
ID: general10
PROG: contact
LANG: C++
*/
#include <algorithm>
#include <climits>
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


struct Node
{
	int score;
	char value;
	Node* child[2];
	Node* parent;

	void RootAdd(const char* str, int length, int scoreStartLength)
	{
		if(length <= 0)
			return;

		if(*str == 0)
			return;

		int index = *str - '0';
		if(index < 0 || index > 1)
			return;

		if(child[index] == 0)
		{
			child[index] = new Node();
			child[index]->parent = this;
			child[index]->value = *str;
		}

		child[index]->Add(str, length, scoreStartLength);
	}

	void Add(const char* str, int length, int scoreStartLength)
	{
		if(length <= 0)
			return;

		if(*str == 0)
			return;

		int index = *str - '0';
		if(index < 0 || index > 1)
			return;

		if(scoreStartLength > 0)
			scoreStartLength--;

		if(scoreStartLength <= 0)
			score++;

		if(child[index] == 0)
		{
			child[index] = new Node();
			child[index]->parent = this;
			child[index]->value = *str;
		}

		length--;
		str++;

		child[index]->Add(str, length, scoreStartLength);
	}

	string ToString()
	{
		if(parent == 0)
			return "";

		return parent->ToString() + value;
	}

	Node()
	{
		score = 0;
		child[0] = child[1] = 0;
		parent = 0;
		value = 0;
	}
};

struct ScoredNode
{
	Node* node;

	ScoredNode(Node* n)
	: node(n)
	{ }
};

bool operator<(const ScoredNode& lhs, const ScoredNode& rhs)
{
	return lhs.node->score < rhs.node->score;
}

multiset<ScoredNode> res;
int resSize = 0;
int numOutputs;

void Visit(Node* node)
{
	ScoredNode s(node);

	res.insert(s);
	resSize++;
	
	while(resSize > numOutputs)
	{
		set<ScoredNode>::iterator iter = res.begin();
		//res.erase(iter);
		resSize--;
	}
	
	if(node->child[0] != 0)
		Visit(node->child[0]);

	if(node->child[1] != 0)
		Visit(node->child[1]);
}

int main() 
{
	FILE *fin  = fopen("contact.in", "r");
	FILE *fout = fopen("contact.out", "w");

	int minLength, maxLength;
	fscanf(fin, "%d %d %d", &minLength, &maxLength, &numOutputs);

	char str[200001] = {0};
	char tmp[1024];
	
	while(true)
	{
		const char* readStatus = fgets(tmp, 1023, fin);
		
		if(readStatus == NULL)
			break;

		int len = strlen(tmp);
		tmp[len-1] = 0;

		strcat(str, tmp);
	}

	int len = strlen(str);

	Node root;
	for(int i=0;i<len;i++)
		root.Add(&str[i], maxLength, minLength);

	Visit(&root);

	for(set<ScoredNode>::iterator iter = res.begin(); iter != res.end(); ++iter)
		fprintf(fout, "%d: %s\n", (*iter).node->score, (*iter).node->ToString().c_str());

	fclose(fout);
	fclose(fin);

	return 0;
}