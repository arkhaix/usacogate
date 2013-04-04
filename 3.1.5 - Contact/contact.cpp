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

	void RootAdd(const char* str, int minLength, int maxLength)
	{
		if(maxLength <= 0)
			return;

		if(str == 0 || *str == 0)
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

		child[index]->Add(str, minLength, maxLength);
	}

	void Add(const char* str, int minLength, int maxLength)
	{
		// Exit conditions

		if(maxLength <= 0)
			return;

		if(str == 0 || *str == 0)
			return;


		// Account for this node

		minLength--;
		maxLength--;

		if(minLength <= 0)
			score++;


		// Recurse on the relevant child node, if any

		++str;

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

		child[index]->Add(str, minLength, maxLength);
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
	if(lhs.node->score != rhs.node->score)
		return lhs.node->score < rhs.node->score;

	string lhsStr = lhs.node->ToString();
	string rhsStr = rhs.node->ToString();

	if(lhsStr.length() != rhsStr.length())
		return lhsStr.length() < rhsStr.length();

	int cmp = lhsStr.compare(rhsStr);
	return cmp < 0;
}

map<int, vector<ScoredNode> > res;
int numOutputs;

void Visit(Node* node)
{
	ScoredNode s(node);

	if(node->score > 0)
		res[node->score].push_back(s);
	
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
		if(tmp[len-1] == '\n')
			tmp[len-1] = 0;

		strcat(str, tmp);
	}

	int len = strlen(str);

	Node root;
	for(int i=0;i<len;i++)
		root.RootAdd(&str[i], minLength, maxLength);

	Visit(&root);

	map<int, vector<ScoredNode> >::iterator iter = res.end();
	int frequenciesPrinted = 0;
	while(true)
	{
		bool lastFrequency = false;

		--iter;
		if(iter == res.begin())
			lastFrequency = true;

		frequenciesPrinted++;
		if(frequenciesPrinted >= numOutputs)
			lastFrequency = true;

		fprintf(fout, "%d\n", iter->first);

		sort(iter->second.begin(), iter->second.end());

		int patternsPrinted = 0;
		for(unsigned int i=0;i<iter->second.size();i++)
		{
			fprintf(fout, "%s", iter->second[i].node->ToString().c_str());

			patternsPrinted++;
			if(patternsPrinted == 6 && i != iter->second.size()-1)
			{
				fprintf(fout, "\n");
				patternsPrinted = 0;
			}
			else if(i != iter->second.size()-1)
			{
				fprintf(fout, " ");
			}
		}

		fprintf(fout, "\n");

		if(lastFrequency == true)
			break;
	}

	fclose(fout);
	fclose(fin);

	return 0;
}