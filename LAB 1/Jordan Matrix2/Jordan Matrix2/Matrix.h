#pragma once
#pragma once
#include <vector>
namespace mtr {
	class Matrix {
	private:
		int N;
		std::vector<std::vector<int>> matrix;
		int det;
		std::vector<int> eigenvalues;
		std::vector<int> findDividers(int value);
		int multiplyVector(std::vector<int> values);
		void increaseVector(std::vector<int> &vec, int key);
		void findEigenvalues();
		int determinant(std::vector<std::vector<int>> tempMatrix);
	public:
		bool scan();
		void print();
		int getCell(std::pair<int, int> pos);
		bool setCell(std::pair<int, int> pos, int value);
		std::vector<int> getEigenvalues();
		int determinant();
		Matrix jordanForm();
		~Matrix();
	};

}