#include "stdafx.h"
#include "Matrix.h"
#include <fstream>
#include <algorithm>


using namespace std;

mtr::Matrix::~Matrix() {
}

std::vector<int> mtr::Matrix::findDividers(int value) {
	vector<int> res;
	vector<vector<int>> tempMatrix;
	for (int i = 1; i < abs(value) / 2 + 1; i++)//обмеження бо найбільший дільник для а це а/2
												//Перебираем всі можливі дільки визначника та дивимось чи вони перетворюють його в 0 
		if (value % i == 0) {
			tempMatrix = matrix;
			for (int j = 0; j < N; j++)
				tempMatrix[j][j] -= i;
			if (determinant(tempMatrix) == 0)
				res.push_back(i);
			tempMatrix = matrix;
			//повертаем матрицю до початкового вигляду 
			for (int j = 0; j < N; j++)
				tempMatrix[j][j] -= -i;
			if (determinant(tempMatrix) == 0)
				res.push_back(-i);
		}
	res.push_back(value);
	return res;
}

int mtr::Matrix::multiplyVector(vector<int> values) {
	int multiply = 1;
	for each (int value in values) {
		multiply *= value;
	}
	return multiply;
}

void mtr::Matrix::increaseVector(std::vector<int> &vec, int key) {
	if (vec.back() < key)
		vec.back()++;
	else {
		vec.pop_back();
		increaseVector(vec, key);
		vec.push_back(0);
	}
}

void mtr::Matrix::findEigenvalues() {
	vector<int> dividers = findDividers(det);//отримали власні значення
	eigenvalues.resize(N, dividers[0]);
	int multiply = multiplyVector(eigenvalues);//рахуемо добуток власних значень
	vector<int> count(N, 0);//заповнили вектор нулями
	while (multiply != det) {//якщо вони рівні то ми знайшли всі власні значення
							 //весь цей while знаходить кратні власні значення
		increaseVector(count, dividers.size() - 1);
		for (int i = 0; i < eigenvalues.size(); i++)
			eigenvalues[i] = dividers[count[i]];
		multiply = multiplyVector(eigenvalues);
	}
	sort(eigenvalues.begin(), eigenvalues.end());
}

int mtr::Matrix::determinant(std::vector<std::vector<int>> tempMatrix) {
	if (tempMatrix.size() == 1)
		return tempMatrix[0][0];
	vector<vector<int>> deleatableMatrix;
	int det = 0;
	for (int i = 0; i < tempMatrix.size(); i++) {
		deleatableMatrix = tempMatrix;
		deleatableMatrix.erase(deleatableMatrix.begin() + i);
		for (int j = 0; j < deleatableMatrix.size(); j++)
			deleatableMatrix[j].erase(deleatableMatrix[j].begin());
		det += pow(-1, i) * determinant(deleatableMatrix) * tempMatrix[i][0];
	}
	return det;
}

bool mtr::Matrix::scan() {
	ifstream in("Matrix.txt");
	if (!in.eof())
		in >> N;
	else return false;
	matrix.resize(N);
	for (int i = 0; i < N; i++) {
		matrix[i].resize(N);
		for (int j = 0; j < N; j++)
			if (!in.eof())
				in >> matrix[i][j];
			else return false;
	}
	return true;
}

void mtr::Matrix::print() {
	ofstream out("Jordan matrix.txt");
	for each (vector<int> raw in matrix) {
		for each (int cell in raw)
			out << cell << ' ';
		out << endl;
	}
}

int mtr::Matrix::getCell(std::pair<int, int> pos) {
	if (pos.first < N && pos.second < N)
		return matrix[pos.first][pos.second];
}

bool mtr::Matrix::setCell(std::pair<int, int> pos, int value) {
	if (pos.first < N && pos.second < N)
		matrix[pos.first][pos.second] = value;
	else return false;
	return true;
}

std::vector<int> mtr::Matrix::getEigenvalues() {
	if (eigenvalues.size() == 0)
		findEigenvalues();
	return eigenvalues;
}

int mtr::Matrix::determinant() {
	det = determinant(matrix);
	return det;
}

mtr::Matrix mtr::Matrix::jordanForm() {
	vector<vector<int>> jordan(N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			jordan[i].push_back(0);//заповнюеться вся нулями 
	for (int i = 0; i < eigenvalues.size(); i++) {
		jordan[i][i] = eigenvalues[i];//На діагоналі вставляються власні значення
		if (i + 1 < N && eigenvalues[i + 1] == eigenvalues[i])
			jordan[i][i + 1] = 1;//якщо кратні власні значення то біля першого ставиться 1
	}
	Matrix jordanMatrix;
	jordanMatrix.matrix = jordan;
	return jordanMatrix;
}
