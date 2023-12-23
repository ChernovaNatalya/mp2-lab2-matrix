// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <ctime>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
	/*
	TDynamicMatrix<int> a(5), b(5), c(5);
	int i, j;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование класс работы с матрицами"
		<< endl;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	c = a + b;
	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;
	*/

	int na, nb;
	cout << "Enter size of matrix A: ";
	cin >> na;
	TDynamicMatrix<int> A(na);
	cout << "Enter elements of matrix A: ";
	for (int i = 0; i < na; i++) {
		for (int j = 0; j < na; j++) {
			cin >> A[i][j];
		}
	}
	cout << "Enter size of matrix B: ";
	cin >> nb;
	TDynamicMatrix<int> B(nb);
	cout << "Enter elements of matrix B: ";
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < nb; j++) {
			cin >> B[i][j];
		}
	}
	TDynamicMatrix<int> C(nb);
	int f;
	cout << "What do you want?" << endl;
	cout << "1. A+B" << endl;
	cout << "2. A-B" << endl;
	cout << "3. A*B" << endl;
	cout << "Enter the number: " << endl;
	cin >> f;
	switch (f) {
	case 1:
		C = A + B;
		break;
	case 2:
		C = A - B;
		break;
	case 3:
		cout << A * B;
		C = A * B;
		break;
	default:
		cout << "ERROR";
		break;
	}
	cout << endl << A << endl << B << endl << C << endl;

	/*
	int n = 6000;
	TDynamicMatrix<int> m1(n), m2(n), m3(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m1[i][j] = i;
			m2[i][j] = i;
		}
	}
	unsigned int start_time = clock();
	m3 = m1 + m2;
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	cout << search_time;
*/
}
//---------------------------------------------------------------------------
