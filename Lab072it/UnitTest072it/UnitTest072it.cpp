// UnitTest_Lab072it.cpp
// Heriak Vladyslav
// Unit-тест до лабораторної роботи № 7.2 (ітераційний спосіб).
// Тестуються функції SumMinOddRows() (сума мінімальних елементів по непарних
// рядках матриці) та MinInRow() (мінімальний елемент рядка).
// Результат обох функцій повертається як значення функції.
// Варіант 5

#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab072it/Lab072it.cpp"	// підключення тестованого проекту

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab072it
{
	// Створення динамічної матриці та копіювання в неї значень з одновимірного масиву
	int** CreateMatrix(const int* values, const int k, const int n)
	{
		int** a = new int* [k];		// матриця, яка передається у функції, що тестуються
		for (int i = 0; i < k; i++)
		{
			a[i] = new int[n];
			for (int j = 0; j < n; j++)
				a[i][j] = values[i * n + j];
		}
		return a;
	}

	// Звільнення пам'яті, виділеної для динамічної матриці
	void DeleteMatrix(int** a, const int k)
	{
		for (int i = 0; i < k; i++)
			delete[] a[i];
		delete[] a;
	}

	TEST_CLASS(UnitTestLab072it)
	{
	public:

		// Матриця 5x3: у парних рядках (2-й і 4-й) розташовані дуже малі значення,
		// які не повинні потрапити в суму; враховуються лише 1-й, 3-й і 5-й рядки
		TEST_METHOD(TestSumMinOddRows_Mixed5x3)
		{
			const int k = 5;	// кількість рядків матриці
			const int n = 3;	// кількість стовпчиків матриці
			const int values[] = {
				  4,  -2,   7,		// 1-й рядок, мінімум -2
				-10, -20, -30,		// 2-й рядок, не враховується
				  5,   9,   3,		// 3-й рядок, мінімум 3
				100, -50,   0,		// 4-й рядок, не враховується
				  8,   6,   1 };	// 5-й рядок, мінімум 1

			int** a = CreateMatrix(values, k, n);
			int sum = SumMinOddRows(a, k, n);

			Assert::AreEqual(2, sum, L"Wrong sum of minimums in odd rows");
			DeleteMatrix(a, k);
		}

		// Матриця з одного рядка: сума дорівнює мінімуму цього рядка
		TEST_METHOD(TestSumMinOddRows_SingleRow)
		{
			const int k = 1;
			const int n = 4;
			const int values[] = { 3, -1, 8, 0 };

			int** a = CreateMatrix(values, k, n);
			int sum = SumMinOddRows(a, k, n);

			Assert::AreEqual(-1, sum, L"Wrong sum for a single row");
			DeleteMatrix(a, k);
		}

		// Матриця з двох рядків: враховується тільки перший (непарний) рядок
		TEST_METHOD(TestSumMinOddRows_TwoRows)
		{
			const int k = 2;
			const int n = 2;
			const int values[] = {
				 5,  2,
				-9, -9 };

			int** a = CreateMatrix(values, k, n);
			int sum = SumMinOddRows(a, k, n);

			Assert::AreEqual(2, sum, L"Only the first row must be counted");
			DeleteMatrix(a, k);
		}

		// Матриця з одного стовпчика: мінімум кожного рядка дорівнює його єдиному елементу
		TEST_METHOD(TestSumMinOddRows_SingleColumn)
		{
			const int k = 3;
			const int n = 1;
			const int values[] = { 4, -7, 6 };

			int** a = CreateMatrix(values, k, n);
			int sum = SumMinOddRows(a, k, n);

			Assert::AreEqual(10, sum, L"Wrong sum for a single column");
			DeleteMatrix(a, k);
		}

		// Усі елементи рядка однакові та від'ємні
		TEST_METHOD(TestSumMinOddRows_EqualNegativeElements)
		{
			const int k = 3;
			const int n = 2;
			const int values[] = {
				-3, -3,
				 1,  1,
				-5, -5 };

			int** a = CreateMatrix(values, k, n);
			int sum = SumMinOddRows(a, k, n);

			Assert::AreEqual(-8, sum, L"Wrong sum for negative elements");
			DeleteMatrix(a, k);
		}

		// Мінімальний елемент рядка стоїть на початку, посередині та в кінці рядка
		TEST_METHOD(TestMinInRow_MinAtDifferentPositions)
		{
			const int k = 3;
			const int n = 3;
			const int values[] = {
				2, 5,  9,		// мінімум на початку рядка
				9, 1,  5,		// мінімум посередині рядка
				7, 8, -3 };		// мінімум в кінці рядка

			int** a = CreateMatrix(values, k, n);

			Assert::AreEqual(2, MinInRow(a, 0, n), L"Wrong minimum of row 0");
			Assert::AreEqual(1, MinInRow(a, 1, n), L"Wrong minimum of row 1");
			Assert::AreEqual(-3, MinInRow(a, 2, n), L"Wrong minimum of row 2");
			DeleteMatrix(a, k);
		}
	};
}