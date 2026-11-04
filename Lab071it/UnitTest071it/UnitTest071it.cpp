// UnitTest_Lab_7_1.cpp
// Heriak Vladyslav
// Unit-тест до лабораторної роботи № 7.1.
// Тестується функція Calc() (обчислення кількості та суми заданих елементів
// і заміна їх нулями). Результат повертається через параметри-посилання S і k.
// Варіант 5

#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab071it/Lab071it.cpp"	// підключення тестованого проекту

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab71
{
	// Створення динамічної матриці та копіювання в неї значень з одновимірного масиву
	int** CreateMatrix(const int* values, const int rowCount, const int colCount)
	{
		int** R = new int* [rowCount];	// матриця, яка передається у функцію Calc()
		for (int i = 0; i < rowCount; i++)
		{
			R[i] = new int[colCount];
			for (int j = 0; j < colCount; j++)
				R[i][j] = values[i * colCount + j];
		}
		return R;
	}

	// Звільнення пам'яті, виділеної для динамічної матриці
	void DeleteMatrix(int** R, const int rowCount)
	{
		for (int i = 0; i < rowCount; i++)
			delete[] R[i];
		delete[] R;
	}

	// Перевірка збігу всіх елементів матриці з очікуваними значеннями
	void AssertMatrixEqual(int** R, const int* expected,
		const int rowCount, const int colCount)
	{
		for (int i = 0; i < rowCount; i++)
			for (int j = 0; j < colCount; j++)
				Assert::AreEqual(expected[i * colCount + j], R[i][j],
					L"Matrix element differs from the expected value");
	}

	TEST_CLASS(UnitTestLab71)
	{
	public:

		// Змішана матриця 3x3: є додатні, від'ємні та нульові елементи,
		// частина елементів не задовольняє критерію і має залишитися без змін
		TEST_METHOD(TestCalc_Mixed3x3)
		{
			const int rowCount = 3;		// кількість рядків матриці
			const int colCount = 3;		// кількість стовпчиків матриці
			const int values[] = {
				-4,  3,  0,
				 2, -5,  6,
				 8, -1, -9 };
			// після Calc() лишаються лише елементи з обома парними індексами,
			// які не є додатними: -4, 0 (позиція 0,2) та -9
			const int expected[] = {
				-4, 0, 0,
				 0, 0, 0,
				 0, 0, -9 };

			int** R = CreateMatrix(values, rowCount, colCount);
			int S = 0;	// сума елементів, які задовольняють критерію
			int k = 0;	// кількість елементів, які задовольняють критерію
			Calc(R, rowCount, colCount, S, k);

			Assert::AreEqual(13, S, L"Wrong sum S");
			Assert::AreEqual(6, k, L"Wrong count k");
			AssertMatrixEqual(R, expected, rowCount, colCount);
			DeleteMatrix(R, rowCount);
		}

		// Усі елементи додатні: критерію задовольняють усі
		TEST_METHOD(TestCalc_AllPositive)
		{
			const int rowCount = 2;
			const int colCount = 2;
			const int values[] = {
				1, 2,
				3, 4 };
			const int expected[] = {
				0, 0,
				0, 0 };

			int** R = CreateMatrix(values, rowCount, colCount);
			int S = 0;
			int k = 0;
			Calc(R, rowCount, colCount, S, k);

			Assert::AreEqual(10, S, L"Wrong sum S");
			Assert::AreEqual(4, k, L"Wrong count k");
			AssertMatrixEqual(R, expected, rowCount, colCount);
			DeleteMatrix(R, rowCount);
		}

		// Жоден елемент не задовольняє критерію: матриця не змінюється,
		// а початкові значення S і k (не нульові) мають бути скинуті в 0
		TEST_METHOD(TestCalc_NoElementsSatisfyCriterion)
		{
			const int rowCount = 1;
			const int colCount = 1;
			const int values[] = { -5 };	// єдиний елемент: індекси (0,0) парні, не додатний
			const int expected[] = { -5 };

			int** R = CreateMatrix(values, rowCount, colCount);
			int S = 99;		// початкове значення, яке функція має обнулити
			int k = 99;		// початкове значення, яке функція має обнулити
			Calc(R, rowCount, colCount, S, k);

			Assert::AreEqual(0, S, L"S must be reset to 0");
			Assert::AreEqual(0, k, L"k must be reset to 0");
			AssertMatrixEqual(R, expected, rowCount, colCount);
			DeleteMatrix(R, rowCount);
		}

		// Нульовий елемент, в якого не обидва індекси парні, задовольняє критерію:
		// він додає 0 до суми, але збільшує кількість k
		TEST_METHOD(TestCalc_ZeroIsCountedWhenIndicesNotBothEven)
		{
			const int rowCount = 2;
			const int colCount = 2;
			const int values[] = {
				-1,  0,
				 0, -2 };
			// (0,0) = -1: обидва індекси парні, не додатний, лишається;
			// (0,1) = 0, (1,0) = 0, (1,1) = -2: задовольняють критерію
			const int expected[] = {
				-1, 0,
				 0, 0 };

			int** R = CreateMatrix(values, rowCount, colCount);
			int S = 0;
			int k = 0;
			Calc(R, rowCount, colCount, S, k);

			Assert::AreEqual(-2, S, L"Wrong sum S");
			Assert::AreEqual(3, k, L"Wrong count k");
			AssertMatrixEqual(R, expected, rowCount, colCount);
			DeleteMatrix(R, rowCount);
		}
	};
}