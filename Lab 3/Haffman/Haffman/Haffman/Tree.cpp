#include "stdafx.h"
#include "Tree.h"

Tree *unite(Tree *a, Tree *b) // ����������� ���� �������� ��������
{
	Tree *un = new Tree();
	un->val = a->val + b->val;
	un->l = a;
	un->r = b;
	return un;
}

Tree* makeTree(map<char, int> cnt, set<char> symbols) // ������������ ������ ��������
{
	multiset<Tree*, less_comp> prior;
	Tree *root = new Tree();
	root->val = cnt[0];
	root->symb = 0;
	prior.insert(root);
	for (auto i = symbols.begin(); i != symbols.end(); i++) // ��������� ���� � �������� � ��� ���������� � ������	
	{
		Tree *root = new Tree();
		root->val = cnt[*i];
		root->symb = *i;
		prior.insert(root);
	}
	while (prior.size()>1) // ����������� ���� �������� � ����������� ��������� ���������
	{
		Tree *f = *prior.begin();
		prior.erase(prior.begin());
		Tree *s = *prior.begin();
		prior.erase(prior.begin());
		prior.insert(unite(f, s));
	}
	return *prior.begin();
}
