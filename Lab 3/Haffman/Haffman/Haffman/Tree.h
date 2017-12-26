#pragma once
#include <map>
#include <set>
#pragma once
using namespace std;
struct Tree // Huffman tree
{
	int val;
	char symb;
	Tree *l, *r;
	Tree() : val(0), l(nullptr), r(nullptr) {}
};

struct less_comp // comparator for trees
{
	bool operator() (Tree *a, Tree *b)
	{
		return a->val <= b->val;
	}
};

Tree *unite(Tree *a, Tree *b); // unite two trees

Tree* makeTree(map<char, int> cnt, set<char> symbols); // create new tree

