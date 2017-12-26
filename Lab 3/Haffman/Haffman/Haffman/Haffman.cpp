// Haffman.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include <bits/stdc++.h>
#include "Tree.h"
#include "Solution.h"

using namespace std;

void Solve()
{
	vector<string> fileNames = getFiles();
	compress(fileNames);
}

int main()
{
	Solve();
	 system("pause");
	return 0;
}

