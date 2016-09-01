/*
 * Templates.h
 *
 *  Created on: Aug 29, 2016
 *      Author: raziel
 */

#ifndef TEMPLATES_H_
#define TEMPLATES_H_
#include <iostream>
#include <string>

using namespace std;

namespace Hashing
{
	struct Node
	{
		char* data;
		Node* next;
	};

	void addNode(Node*& list, Node* node)
	{
		Node* p = new Node;
		p->data = node->data;
		p->next = node->next;

		if(list==NULL)
		{
			list = p;
			p->next = NULL;
		}else
		{
			p->next = list;
			list = p;
		}
	}

	static void showList(Node* list)
	{
		Node* p = list;
		while(p)
		{
			cout << p->data << "->";
			p = p->next;
		}
	}

	int hash(char* data, int size)
	{
		int modulo = 13;
		int sum = 0;
		int result = 0;

		for(int i=0;i<size;i++)
			sum += (int) data[i];

		result = sum%modulo;

		return result;
	}

	static void insertData(char* data, int size, Node**& list)
	{
		Node* p = new Node;
		p->data = data;
		p->next = NULL;

		int i = hash(data,size);
		addNode(list[i], p);
	}

	static void insertCollisionData(char* data, int size, Node**& list)
	{
		Node* p = new Node;
		p->data = data;
		p->next = NULL;

		int x = hash(data, size);
		if(list[x]==NULL)
			addNode(list[x], p);
		else
		{
			for(int i=0;i<size;i++)
			{
				x += i;
				if(list[x]==NULL)
				{
					addNode(list[x], p);
					break;
				}
			}
		}
	}
}

namespace Templating
{
	int hashData(char* data, int size)
	{
		int modulo = 13;
		int sum = 0;
		int result = 0;

		for(int i=0;i<size;i++)
			sum += (int) data[i];

		result = sum%modulo;

		return result;
	}

	char* stepForward(char* text, int patternSize, int& startTag)
	{
		char* result = new char[patternSize];

		for(int i=0; i<patternSize;i++)
		{
			result[i] = text[i+startTag+1];
		}

		startTag++;
		return result;
	}

	static int rabinKarp(char* text, char* pattern, int textSize, int patternSize)
	{
		int index = 0;
		int startTag = 0;
		int hashOne;
		int hashTwo;
		bool founded = false;

		//Setting compared string to beginning of text
		char* compared = new char[patternSize];
		for(int i=0;i<patternSize;i++)
			compared[i] = text[i];

		//Hash from pattern, it will stay the same all the time
		hashOne = hashData(pattern, patternSize);

		while(*text && !founded)
		{
			hashTwo = hashData(compared, patternSize);

			if(hashOne==hashTwo)
			{
				for(int i=0;i<patternSize;i++)
				{
					if(pattern[i] == compared[i])
					{
						index = startTag;
						if(i==patternSize-1)
							founded = true;
					}else
					{
						compared = stepForward(text, patternSize, startTag);
						break;
					}
				}
			}else
			{
				//Going one letter further
				compared = stepForward(text, patternSize, startTag);
			}
		}

		return index;
	}
}





#endif /* TEMPLATES_H_ */
