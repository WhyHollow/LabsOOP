#include "Tree.h"
#pragma once
#include <string>
#include <vector>
using namespace std;
void read(string fileName, string &s, map<char, int> &cnt, set<char> &symbols);
void down(map<char, string> &codes, Tree* root, string currentCode);
void encode(map<char, string> codes, string text, string fileName);
string toBin(char symb);
void solve(string fileName);
void compress(vector<string> files);
vector<string> getFiles();
