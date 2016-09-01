/*
 * Trees.h
 *
 *  Created on: Aug 25, 2016
 *      Author: raziel
 */

#ifndef TREES_H_
#define TREES_H_
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

namespace Treeing
{
	string cr,cl,cp;

	struct Leaf{
		int val;
		Leaf* left;
		Leaf* right;
		Leaf* parent;
	};

	static int* makeArray(int size)
	{
		srand(time(NULL));
		int a = 0;

		int* list = new int[size];
		for(int i=0;i<size;i++)
		{
			a = rand()%10;
			list[i] = a;
		}

		return list;
	}

	static void swapArray(int* list, int x, int y)
	{
		if(list)
		{
			int buffor = list[x];
			list[x] = list[y];
			list[y] = buffor;
		}
	}

	static Leaf* getNode(Leaf* root, int value)
	{
		Leaf* p = root;

		while(p->val != value)
		{
			if(value<p->val)
				p = p->left;
			else if(value>p->val)
				p = p->right;
		}

		return p;
	}

	static void printBT(string sp, string sn, Leaf* root)
	{
	  string s;

	  if(root != NULL)
	  {
	    s = sp;
	    if(sn == cr) s[s.length() - 2] = ' ';
	    printBT(s + cp, cr, root->right);

	    s = s.substr(0,sp.length()-2);
	    cout << s << sn << root->val << endl;

	    s = sp;
	    if(sn == cl) s[s.length() - 2] = ' ';
	    printBT(s + cp, cl, root->left);
	  }
	}

	static void printTree(Leaf* root)
	{
		cr = cl = cp = "  ";
		cr[0] = 218; cr[1] = 196;
		cl[0] = 192; cl[1] = 196;
		cp[0] = 179;
		printBT("", "", root);
	}

	static void insertBST(Leaf*& root, Leaf* parent, int value)
	{
		if(root==NULL)
		{
			root = new Leaf;
			root->val = value;
			root->left = NULL;
			root->right = NULL;
			root->parent = parent;
		}else
		{
			if(value<root->val)
				insertBST(root->left, root, value);
			else
				insertBST(root->right, root, value);
		}
	}

	static Leaf* makeTree(int* list, int size)
	{
		Leaf* root = NULL;

		for(int i=0;i<size;i++)
			insertBST(root, NULL, list[i]);

		return root;
	}

	Leaf* findSuccesor(Leaf* root)
	{
		Leaf* p = root->right;

		while(p->left)
			p = p->left;

		return p;
	}

	Leaf* findPredecessor(Leaf* root)
	{
		Leaf* p = root->left;

		while(p->right)
			p = p->right;

		return p;
	}

	int getTreeHeight(Leaf* root)
	{
		if(root)
		{
			int leftHeight = getTreeHeight(root->left);
			int rightHeight = getTreeHeight(root->right);

			if(leftHeight>rightHeight)
				return (leftHeight+1);
			else
				return (rightHeight+1);
		}else
			return 0;
	}

	static void heapify(int*& list, int heapsize, int n)
	{
		int l = (2*n)+1;
		int r = (2*n)+2;
		int largest;

		//Comparing left with parent
		if(l<=heapsize && list[l]>list[n])
			largest = l;
		else
			largest = n;

		//Comparing larger from last comparission with right one
		if(r<=heapsize && list[r]>list[largest])
			largest = r;

		if(largest!=n)
		{
			swap(list[largest], list[n]);
			heapify(list, heapsize, largest);
		}
	}

	static void maxHeap(int*& list, int n)
	{
		for(int i=(n/2);i>=0;i--)
			heapify(list, n, i);
	}

	static void heapSort(int*& list, int heapsize)
	{
		maxHeap(list, heapsize);
		while(heapsize!=0)
		{
			swapArray(list, 0, heapsize);
			heapsize--;
			maxHeap(list, heapsize);
		}
	}

	static void rotR(Leaf*& root, Leaf* A)
	{
		Leaf* B = A->left;
		Leaf* p = A->parent;

		if(B)
		{
			A->left = B->right;
			if(A->left)
				A->left->parent = A;

			B->right = A;
			B->parent = p;
			A->parent = B;

			if(p)
			{
				if(p->left == A)
					p->left = B;
				else
					p->right = B;
			}else
				root = B;
		}
	}

	static void rotL(Leaf*& root, Leaf* A)
	{
		Leaf* B = A->right;
		Leaf* p = A->parent;

		if(B)
		{
			A->right = B->left;
			if(A->right)
				A->right->parent = A;

			B->left = A;
			B->parent = p;
			A->parent = B;

			if(p)
			{
				if(p->left == A)
					p->left = B;
				else
					p->right = B;
			}else
				root = B;
		}
	}

	int log2(int x)
	{
		int y = 1;
		while((x >>=1) > 0)
			y <<= 1;

		return y;
	}

	static void rebalanceTree(Leaf*& root)
	{
		int n,i,s;
		Leaf* p = root;

		n = 0;

		while(p)
		{
			if(p->left)
			{
				rotR(root, p);
				p = p->parent;
			}else
			{
				n++;
				p = p->right;
			}
		}

		s = n+1-log2(n+1);
		p = root;

		for(i=0;i<s;i++)
		{
			rotL(root, p);
			p = p->parent->right;
		}

		n = n-s;
		while(n>1)
		{
			n>>=1;
			p = root;
			for(i=0;i<n;i++)
			{
				rotL(root, p);
				p = p->parent->right;
			}
		}
	}

	static void inOrder(Leaf* root)
	{
		if(root)
		{
			inOrder(root->left);
			cout << root->val << " | ";
			inOrder(root->right);
		}
	}

	static void deleteLeaf(Leaf*& root, int value)
	{
		Leaf* p = getNode(root, value);
		Leaf* parent = p->parent;
		Leaf* successor = findSuccesor(p);

			if(successor->right)
			{
				Leaf* h = successor->parent;
				successor->right->parent = successor->parent;

				h->left = successor->right;
			}

			successor->left = p->left;
			successor->right = p->right;
			successor->parent = parent;

			if(parent)
			{
				if(parent->left == p)
					parent->left = successor;
				else if(parent->right == p)
					parent->right = successor;
			}else
			{
				root = successor;
			}

			delete p;
	}
}







#endif /* TREES_H_ */
