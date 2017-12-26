#include "stdafx.h"
#include "Matrix.h"


using namespace std;

int main() {
	mtr::Matrix sample;
	sample.scan();
	sample.determinant();
	sample.getEigenvalues();
	sample = sample.jordanForm();
	sample.print();
	system("pause");
}


