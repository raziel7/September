/*
 * Lists.h
 *
 *  Created on: Aug 25, 2016
 *      Author: raziel
 */

#ifndef LISTS_H_
#define LISTS_H_
#include <iostream>
#include <cstdlib>

using namespace std;

namespace Listing
{
	struct uniNode{
		int val;
		uniNode* next;
	};

	struct biNode{
		int val;
		biNode* next;
		biNode* prev;
	};

	static void addUniNode(uniNode*& list, int value)
	{
		uniNode* u = new uniNode;
		u->val = value;

		if(list==NULL)
		{
			list = u;
			u->next = NULL;
		}else
		{
			u->next = list;
			list = u;
		}
	}

	static void addBiNode(biNode*& list, int value)
	{
		biNode* b = new biNode;
		b->val = value;

		if(list==NULL)
		{
			list = b;
			b->next = NULL;
			b->prev = NULL;
		}else
		{
			b->next = list;
			b->next->prev = b;
			list = b;
		}
	}

	static uniNode* makeUni(int size)
	{
		srand(time(NULL));
		uniNode* list = NULL;

		int a = 0;

		for(int i=0;i<size;i++)
		{
			a = rand()%100;
			addUniNode(list, a);
		}

		return list;
	}

	static biNode* makeBi(int size)
	{
		srand(time(NULL));
		biNode* list = NULL;

		int a = 0;

		for(int i=0;i<size;i++)
		{
			a = rand()%100;
			addBiNode(list, a);
		}

		return list;
	}

	static void show(uniNode* list)
	{
		uniNode* u = list;
		while(u)
		{
			cout << u->val << " | ";
			u = u->next;
		}

	}

	static void show(biNode* list)
	{
		biNode* b = list;
		while(b)
		{
			cout << b->val << " | ";
			b = b->next;
		}

	}

	static void swapList(uniNode*& list, int x, int y)
	{
		if(list==NULL)
			return;
		else
		{
			int delta = y-x;
			uniNode* p1 = list;
			uniNode* p2 = list;
			uniNode* h = NULL;

			while(x>1)
			{
				p1 = p1->next;
				x--;
			}

			if(delta==1)
			{
				p2 = p1->next->next;
				h = p1->next->next->next;
				p1->next->next->next = p1->next;
				p1->next->next = h;
				p1->next = p2;
			}else
			{
				while(y>1)
				{
					p2 = p2->next;
					y--;
				}

				if(x==0)
				{
					list = p2->next;
					p2->next = p1;
					p1 = p1->next;
					p2->next->next = list->next;
					list->next = p1;
				}else
				{
					h = p2->next->next;
					p2->next->next = p1->next->next;
					p1->next->next = h;
					h = p2->next;
					p2->next = p1->next;
					p1->next = h;
				}
			}
		}
	}

	void backToTheEnd(uniNode*& list, uniNode* node)
	{
		uniNode* h = node->next;
		node->next = h->next;

		h->next = list;
		list = h;
	}

	static void exe1(uniNode*& list)
	{
		uniNode* p = list;
		int max = 0;

		//Search for max value
		while(p)
		{
			if(p->val>max)
				max = p->val;

			p = p->next;
		}

		//Back to start
		p = list;
		while(p->next->val != max)
			p = p->next;

		//Main task
		while(p->next)
			backToTheEnd(list, p);
	}

	void merge(int*& list, int*& leftArray, int*& rightArray, int g, int h)
	{
		int i = 0;
		int j = 0;
		int x = 0;

		while(i<=g && j<=h)
		{
			if(leftArray[i]<rightArray[j])
				list[x++] = leftArray[i++];
			else
				list[x++] = rightArray[j++];
		}

		if(i<j)
		{
			while(i<g)
				list[x++] = leftArray[i++];
		}else
			while(j<h)
				list[x++] = rightArray[j++];
	}

	static void mergeSort(int*& list, int size)
	{
		if(size>1)
		{
			int g = size/2;
			int h = size-g;

			int* leftArray = new int[g];
			int* rightArray = new int[h];

			for(int i=0;i<g;i++)
				leftArray[i] = list[i];

			for(int i=g;i<size;i++)
				rightArray[i] = list[i];

			mergeSort(leftArray, g);
			mergeSort(rightArray, h);

			merge(list, leftArray, rightArray, g, h);
		}
	}
}

#endif /* LISTS_H_ */
