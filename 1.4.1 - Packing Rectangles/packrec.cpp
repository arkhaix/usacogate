/*
ID: general10
PROG: packrec
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Rectangle
{
	int Width;
	int Height;

	int Area() { return Width * Height; }

	void SortProperties()
	{
		if(Width > Height)
			swap(Width, Height);
	}

	Rectangle() { Width=0; Height=0; }
};

vector<Rectangle> inputs;

bool operator<(const Rectangle& a, const Rectangle& b)
{
	if(a.Width != b.Width)
		return a.Width < b.Width;
	return a.Height < b.Height;
}

bool RectangleByHeight(const Rectangle& a, const Rectangle& b)
{
	return a.Height < b.Height;
}

bool RectangleByWidth(const Rectangle& a, const Rectangle& b)
{
	return a.Width < b.Width;
}

Rectangle Layout1()
{
	Rectangle res;

	for(int i=0;i<4;i++)
		res.Width += inputs[i].Width;

	res.Height = (*max_element(inputs.begin(), inputs.end(), RectangleByHeight)).Height;

	return res;
}

Rectangle Layout2()
{
	Rectangle res;

	for(int i=0;i<3;i++) res.Width += inputs[i].Width;
	res.Width = max(res.Width, inputs[3].Width);

	res.Height = (*max_element(inputs.begin(), inputs.begin()+3, RectangleByHeight)).Height;
	res.Height += inputs[3].Height;

	return res;
}

Rectangle Layout3()
{
	Rectangle res;

	for(int i=0;i<2;i++) res.Width += inputs[i].Width;
	res.Width = max(res.Width, inputs[3].Width);
	res.Width += inputs[2].Width;

	res.Height = max(inputs[0].Height, inputs[1].Height);
	res.Height += inputs[3].Height;
	res.Height = max(res.Height, inputs[2].Height);

	return res;
}

Rectangle Layout4()
{
	Rectangle res;

	res.Width = inputs[0].Width + inputs[3].Width;
	res.Width += max(inputs[1].Width, inputs[2].Width);

	res.Height = max(inputs[0].Height, inputs[3].Height);
	res.Height = max(res.Height, inputs[1].Height + inputs[2].Height);

	return res;
}

Rectangle Layout5()
{
	return Layout4();
}

Rectangle Layout6()
{
	Rectangle res;

	int base = 0;
	int top = 2;
	if(inputs[2].Width + inputs[3].Width > inputs[0].Width + inputs[1].Width)
	{
		base = 2;
		top = 0;
	}

	res.Width = inputs[base].Width + inputs[base+1].Width;

	if(inputs[base].Height < inputs[base+1].Height)
		res.Width = max(res.Width, inputs[base+1].Width + inputs[top].Width); 
	else
		res.Width = max(res.Width, inputs[base].Width + inputs[top+1].Width);

	res.Height = max(inputs[0].Height + inputs[2].Height, inputs[1].Height + inputs[3].Height);

	vector<Rectangle> sortedInputs = inputs;
	sort(sortedInputs.begin(), sortedInputs.end());

	res.Height = max(res.Height, sortedInputs[2].Height + sortedInputs[3].Height);

	return res;
}

set<Rectangle> solutions;
int bestArea = 1000000000;
void CheckBestSolution(Rectangle& solution)
{
	if(solution.Area() < bestArea)
	{
		solution.SortProperties();

		solutions.clear();
		solutions.insert(solution);
		bestArea = solution.Area();
	}
	else if(solution.Area() == bestArea)
	{
		solution.SortProperties();
		solutions.insert(solution);
	}
}


int main() 
{
	FILE *fin  = fopen("packrec.in", "r");
	FILE *fout = fopen("packrec.out", "w");

	for(int i=0;i<4;i++)
	{
		Rectangle input;
		fscanf(fin, "%d %d\n", &input.Width, &input.Height);
		inputs.push_back(input);
	}

	sort(inputs.begin(), inputs.end());

	Rectangle solution;

	do
	{
		for(int i=0;i<16;i++)
		{
			for(int j=0;j<4;j++)
				if(i & (1<<j))
					swap(inputs[j].Width, inputs[j].Height);

			solution = Layout1();
			CheckBestSolution(solution);

			solution = Layout2();
			CheckBestSolution(solution);

			solution = Layout3();
			CheckBestSolution(solution);

			solution = Layout4();
			CheckBestSolution(solution);

			solution = Layout5();
			CheckBestSolution(solution);

			solution = Layout6();
			CheckBestSolution(solution);

			for(int j=0;j<4;j++)
				if(i & (1<<j))
					swap(inputs[j].Width, inputs[j].Height);
		}
	} while(next_permutation(inputs.begin(), inputs.end()));
	
	vector<Rectangle> results(solutions.begin(), solutions.end());
	sort(results.begin(), results.end());

	fprintf(fout, "%d\n", bestArea);
	for(vector<Rectangle>::iterator iter = results.begin(); iter != results.end(); ++iter)
		fprintf(fout, "%d %d\n", iter->Width, iter->Height);

	fclose(fout);
	fclose(fin);

	return 0;
}