/*
 * Graphs.h
 *
 *  Created on: Aug 22, 2016
 *      Author: raziel
 */

#ifndef GRAPHS_H_
#define GRAPHS_H_
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

namespace Graphing
{
	int size;

	struct graphNode{
		int from, too, dist;
		graphNode* next;
	};

	static void addToLN(graphNode*& LN, int dist, int too, graphNode*& tail)
	{
		graphNode* p = new graphNode;
		p->dist = dist;
		p->too = too;

		if(LN==NULL)
		{
			p->next = LN;
			LN = p;
			tail = LN;
		}else
		{
			tail->next = p;
			tail = tail->next;
			p->next = NULL;
		}
	}

	static void addToLE(graphNode*& LE, int dist, int from, int too, graphNode*& tail)
	{
		graphNode* p = new graphNode;
		p->dist = dist;
		p->from = from;
		p->too = too;

		if(LE==NULL)
		{
			p->next = LE;
			LE = p;
			tail = LE;
		}else
		{
			tail->next = p;
			tail = tail->next;
			p->next = NULL;
		}
	}

	static void addNodeToLe(graphNode*& LE, graphNode* node, graphNode*& tail)
	{
		graphNode* p = new graphNode;
		p->dist = node->dist;
		p->from = node->from;
		p->too = node->too;

		if(LE==NULL)
		{
			p->next = LE;
			LE = p;
			tail = LE;
		}else
		{
			tail->next = p;
			tail = tail->next;
			p->next = NULL;
		}
	}

	static void show(graphNode* head)
	{
		graphNode* p = head;
		while(p!=NULL)
		{
			cout << "from: " << p->from << endl << "too: " << p->too << endl << "dist: " << p->dist << endl;
			cout << endl;
			p = p->next;

		}
	}

	static graphNode** readFromFileToLN()
	{
		graphNode** LN = NULL;

		int dist;

		fstream read;
		read.open("graf.txt");
		if(read.good())
		{
			read >> size;
			LN = new graphNode*[size];
			for(int i=0;i<size;i++)
				LN[i] = NULL;

			for(int i=0;i<size;i++)
			{
				graphNode* tail = NULL;
				for(int j=0;j<size;j++)
				{
					read >> dist;
					if(dist!=0 && j>=i)
						addToLN(LN[i], dist, j, tail);
				}
			}

			for(int i=0;i<size;i++)
				show(LN[i]);

		}
		read.close();

		return LN;
	}

	static void addGraphNodeToLE(graphNode*& LE, graphNode* node, graphNode*& tail)
	{
		graphNode* p = new graphNode;
		p->from = node->from;
		p->too = node->too;
		p->dist = node->dist;
		p->next = node->next;

		if(LE==NULL)
		{
			p->next = LE;
			LE = p;
			tail = LE;
		}else
		{
			tail->next = p;
			tail = tail->next;
			p->next = NULL;
		}
	}

	static graphNode* readFromFileToLE()
	{
		int dist;
		graphNode* tail = NULL;

		graphNode* LE = NULL;

		fstream read;
		read.open("graf.txt");
		if(read.good())
		{
			read >> size;

			for(int i=0;i<size;i++)
			{
				for(int j=0;j<size;j++)
				{
					read >> dist;
					if(dist!=0)
						addToLE(LE, dist, i, j, tail);
				}
			}
		}
		read.close();

		return LE;
	}

	static void LEToLN(graphNode*& LE, graphNode**& LN)
	{
		graphNode* p = LE;
		for(int i=0; i<size;i++)
		{
			graphNode* tail = NULL;
				while(p!=NULL && p->from==i)
				{
					addToLN(LN[i], p->dist, p->too, tail);
					p = p->next;
				}
		}
	}

	static graphNode* getGraphNodeFrom(graphNode* LE, int from)
	{
		graphNode* p = LE;
		while(p)
		{
			if(p->from == from)
				break;

			p = p->next;
		}

		return p;
	}

	static int** LEtoMatrixNeighbor(graphNode** LN)
	{
		int** neighborMatrix = new int*[size];
		for(int i=0;i<size;i++)
			neighborMatrix[i] = new int[size];

		for(int i=0;i<size;i++)
		{
			graphNode* temp = LN[i];
			for(int j=0;j<size;j++)
			{
				if(temp!=NULL)
				{
					if(temp->too==j)
					{
						neighborMatrix[i][j] = temp->dist;
						temp = temp->next;
					}else
						neighborMatrix[i][j] = 0;
				}else
					neighborMatrix[i][j] = 0;
			}
		}

		return neighborMatrix;
	}

	static bool fullColored(bool* color)
	{
		for(int i=0;i<size;i++)
		{
			if(color[i] == false)
				return false;
		}

		return true;
	}

	static graphNode* primAlgorithm(graphNode* LE)
	{
		graphNode* mst = NULL;
		graphNode* tail = NULL;
		graphNode* temp = NULL;

		int minimum = std::numeric_limits<int>::max();

		bool* color = new bool[size];
		for(int i=0;i<size;i++)
			color[i] = false;

		//Start from graph node number 0
		color[0] = true;

		graphNode* p = LE;

		//To see if we move on to next graph node, from 1 to 2 let's say
		int checkFrom = p->from;

		while(!fullColored(color))
		{
			//Check if null 'cause algorithm can go to last graph node before end, and next to it is null,
			//without it, algorithm would end earlier
			if(p==NULL || p->from!=checkFrom)
			{
				addNodeToLe(mst, temp, tail);

				//Going to graph node wich we just visited
				p = getGraphNodeFrom(LE, temp->too);

				//Setting basic stuff
				checkFrom = p->from;
				minimum = std::numeric_limits<int>::max();

				//Setting node to visited
				color[temp->too] = true;
			}
			if(p->dist<minimum && color[p->too]==false)
			{
				temp = p;
				minimum = p->dist;
			}
				p = p->next;
		}
		return mst;
	}

}

#endif /* GRAPHS_H_ */














