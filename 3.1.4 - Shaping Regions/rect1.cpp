
/*
ID: general10
PROG: rect1
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

struct Rect
{
	int bottom, top;
	int left, right;
	int color;
};

list<Rect> rects;
map<int, int> res;

struct PendingInsert
{
	list<Rect>::iterator pos;
	Rect element;
};

int main() 
{
	FILE *fin  = fopen("rect1.in", "r");
	FILE *fout = fopen("rect1.out", "w");

	int totalWidth, totalHeight, numRectangles;
	fscanf(fin, "%d %d %d", &totalWidth, &totalHeight, &numRectangles);

	for(int i=0;i<numRectangles;i++)
	{
		Rect x;
		fscanf(fin, "%d %d %d %d %d", &x.left, &x.bottom, &x.right, &x.top, &x.color);
		rects.push_back(x);
	}

	for(int i=0;i<totalWidth;i++)
	{
		list<Rect> columnRegions;
		list<PendingInsert> regionsToInsert;

		for(list<Rect>::iterator iter = rects.begin(); iter != rects.end(); ++iter)
		{
			Rect frontRect = *iter;
			if(frontRect.left > i || frontRect.right <= i)
				continue;

			for(list<Rect>::iterator covered = columnRegions.begin(); covered != columnRegions.end(); ++covered)
			{
				Rect& coveredRect = *covered;
				if(coveredRect.top - coveredRect.bottom <= 0)
					continue;

				// frontRect covers all of coveredRect
				if(frontRect.bottom <= coveredRect.bottom && frontRect.top >= coveredRect.top)
					coveredRect.bottom = coveredRect.top = 0;

				// frontRect covers bottom of coveredRect
				else if(frontRect.bottom <= coveredRect.bottom && frontRect.top > coveredRect.bottom && frontRect.top < coveredRect.top)
					coveredRect.bottom = frontRect.top;

				// frontRect covers top of coveredRect
				else if(frontRect.top >= coveredRect.top && frontRect.bottom < coveredRect.top && frontRect.bottom > coveredRect.bottom)
					coveredRect.top = frontRect.bottom;

				// frontRect inside coveredRect
				else if(frontRect.top <= coveredRect.top && frontRect.bottom >= coveredRect.bottom)
				{
					Rect nc(coveredRect);
					nc.top = frontRect.bottom;

					columnRegions.insert(covered, nc);
					//PendingInsert pi;
					//pi.element = nc;
					//pi.pos = covered;
					//regionsToInsert.push_back(pi);

					coveredRect.bottom = frontRect.top;
				}

				// frontRect outside coveredRect
				else
				{
				}
			}

			//for(list<PendingInsert>::iterator iter = regionsToInsert.begin(); iter != regionsToInsert.end(); ++iter)

			regionsToInsert.clear();

			columnRegions.push_back(frontRect);

			list<Rect>::iterator test = columnRegions.begin(); 
			while(test != columnRegions.end())
			{
				if(test->bottom == 0 && test->top == 0)
				{
					columnRegions.erase(test);
					test = columnRegions.begin();
				}
				else
					++test;
			}
		}

		for(list<Rect>::iterator iter = columnRegions.begin(); iter != columnRegions.end(); ++iter)
		{
			Rect& r = *iter;
			res[r.color] += r.top - r.bottom;
		}

		vector<int> nodes(totalHeight, -1);
		int rectCount=0;
		for(list<Rect>::iterator iter = columnRegions.begin(); iter != columnRegions.end(); ++iter)
		{
			for(int y = iter->bottom; y < iter->top; y++)
			{
				if(nodes[y] != -1)
				{
					Rect a, b;
					list<Rect>::iterator argh = columnRegions.begin();
					int z=0;
					for(;z<nodes[y];z++,++argh);
					a = *argh;
					for(;z<rectCount;z++,++argh);
					b = *argh;

					printf("bad things. node[%d,%d] is overlapped by rects (%d,%d,%d,%d) and (%d,%d,%d,%d)\n", i, y, a.left, a.bottom, a.right, a.top, b.left, b.bottom, b.right, b.top);
				}
				
				nodes[y] = rectCount;
			}

			rectCount++;
		}
	}

	res[1] = totalWidth * totalHeight;
	for(map<int, int>::iterator iter = res.begin(); iter != res.end(); ++iter)
		if(iter->first != 1)
			res[1] -= iter->second;

	for(map<int, int>::iterator iter = res.begin(); iter != res.end(); ++iter)
		if(iter->second != 0)
			fprintf(fout, "%d %d\n", iter->first, iter->second);

	fclose(fout);
	fclose(fin);

	return 0;
}