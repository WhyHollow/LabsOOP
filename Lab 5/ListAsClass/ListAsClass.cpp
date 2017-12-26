// ListAsClass.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>

using namespace std;


class matrix
{
public:
	int n, m;
	class List
	{
	public:
		int data;
		List* next;
	};
	List* *mtx = new List*[n];//створюємо матрицю List
	List** create(int n, int m)//стрворюємо Списки для рядків и елементів
	{
		int i;
		List* temp;
		for (int j = 0; j < n; j++)//Створює лісти рядків
		{
			mtx[j] = new List;
			mtx[j]->data = 0;
			temp = mtx[j];
			for (i = 1; i < m; i++)//Створюемо елементии заповнюємо нулями
			{
				temp->next = new List;
				temp->next->data = 0;
				temp = temp->next;
			}
			temp->next = NULL;
		}
		return mtx;
	}
	void write(int y, int x, int val)//Запис
	{
		List* temp = mtx[y];//Вибираемо рядок
		int i = 0;
		while (i < x) { temp = temp->next; i++; }// Идемо до потрібного елемента
		temp->data = val;//Записуємо його значення
	}
	int read(int y, int x)//Читання
	{
		int val;
		List* temp = mtx[y];
		int i = 0;
		while (i < x) { temp = temp->next; i++; }
		val = temp->data;
		return val;
	}
};


int main()
{
	ifstream fin;
	fin.open("matrix.txt");
	matrix mtx;
	fin >> mtx.n;
	fin >> mtx.m;
	mtx.mtx = mtx.create(mtx.n, mtx.m);//створює  матрицю
	int val;
	for (int i = 0; i < mtx.n; i++)//Записує значення
	{
		for (int j = 0; j < mtx.m; j++)
		{
			val = 0;
			fin >> val;
			mtx.write(i, j, val);
		}
	}
	cout << "the size of matrix is:" << mtx.n << "x" << mtx.m << endl;
	cout << endl;
	cout << "the matrix:" << endl;
	for (int i = 0; i < mtx.n; i++)
	{
		for (int j = 0; j < mtx.m; j++)
		{
			val = mtx.read(i, j);
			cout << val << "  ";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
}

