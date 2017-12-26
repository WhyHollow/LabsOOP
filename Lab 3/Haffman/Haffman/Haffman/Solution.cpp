#include "stdafx.h"
#include "Solution.h"
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <thread>
#include <vector>

#include <iostream>

using namespace std;

void read(string fileName, string &s, map<char, int> &cnt, set<char> &symbols)
{
	/*чтение текста из файла и подсчет различных символов*/
	ifstream in(fileName);
	string f;
	while (getline(in, s))
	{
		f += s;
		for (int i = 0; i<s.size(); i++)
			symbols.insert(s[i]), cnt[s[i]]++;
	}
	s = f;
	in.close();
}

void down(map<char, string> &codes, Tree* root, string currentCode)
{
	/*получение кодов символов*/

	if (root->l && root->r)
	{
		down(codes, root->l, currentCode + "0");
		down(codes, root->r, currentCode + "1");
	}
	else
		codes[root->symb] = currentCode;
}

void encode(map<char, string> codes, string text, string fileName)
{
	//выход из(fileName.substr(0, fileName.size() - 4) + "_out.txt");
	for (int i = 0; i<text.size(); i++)
	{
		for (int j = 0; j < codes[text[i]].size(); j++) {
			cout << bool(codes[text[i]][j] - 48);
			//out << bool(codes[text[i]][j] - 48);
		}
	}
	//out.close();
}

string toBin(char symb)
{
	/*получить двоичное представление символа*/
	int code = int(symb);
	string res;
	while (code>1)
	{
		res += char(code % 2 + 48);
		code /= 2;
	}
	while (res.size()<8) res += "0";
	reverse(res.begin(), res.end());
	return res;
}

void solve(string fileName)
{
	string text;
	map<char, int> cnt;
	set<char> symbols;
	read(fileName, text, cnt, symbols); // чтение текста
	Tree *huffmanTree = makeTree(cnt, symbols); // создание дерева Хаффмана
	map<char, string> codes;
	down(codes, huffmanTree, ""); // получить коды
	encode(codes, text, fileName); // кодирование текста
	ofstream out(fileName.substr(0, fileName.size() - 4) + "_iоnBin.txt");
	for (int i = 0; i<text.size(); i++)
		cout << toBin(text[i]); // двоичное представление текста
	out.close();
}

void compress(vector<string> files) // сжимать файлы
{
	thread t[3];
	for (int i = 0; i<files.size(); i++)
	{
		t[i] = thread(solve, files[i]);
	}
	for (int i = 0; i<files.size(); i++)
		t[i].join();
}

vector<string> getFiles()
{
	vector<string> files;

	/* Получение файлов для сжатия*/
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	string f1 = "text1.txt";
	string f2 = "text2.txt";
	string f3 = "text3.txt";
/*	hf = FindFirstFile("*.txt", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			files.push_back(FindFileData.cFileName);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}*/
	files.push_back(f1);
	files.push_back(f2);
	files.push_back(f3);
	compress(files);
	return files;
}
