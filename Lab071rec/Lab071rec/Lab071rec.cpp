// Lab071rec.cpp
// Heriak Vladyslav
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Рекурсивний спосіб.
// Варіант 5

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** R, const int rowNo, const int colCount, const int Low,
	const int High, int colNo);
void CreateRows(int** R, const int rowCount, const int colCount, const int Low,
	const int High, int rowNo);
void PrintRow(int** R, const int rowNo, const int colCount, int colNo);
void PrintRows(int** R, const int rowCount, const int colCount, int rowNo);
void Change(int** R, const int row1, const int row2, const int colCount, int colNo);
void SortPass(int** R, const int rowCount, const int colCount, const int i0, int i1);
void Sort(int** R, const int rowCount, const int colCount, int i0);
void CalcRow(int** R, const int rowNo, const int colCount, int colNo, int& S, int& k);
void CalcRows(int** R, const int rowCount, const int colCount, int rowNo, int& S, int& k);

int main()
{
	srand((unsigned)time(NULL));

	int Low = -8;		// нижня межа діапазону значень елементів матриці
	int High = 42;		// верхня межа діапазону значень елементів матриці

	int rowCount = 8;	// кількість рядків матриці
	int colCount = 7;	// кількість стовпчиків матриці

	int** R = new int* [rowCount];	// матриця R (динамічний двовимірний масив)
	for (int i = 0; i < rowCount; i++)
		R[i] = new int[colCount];

	CreateRows(R, rowCount, colCount, Low, High, 0);
	PrintRows(R, rowCount, colCount, 0);

	Sort(R, rowCount, colCount, 0);
	PrintRows(R, rowCount, colCount, 0);

	int S = 0;	// сума елементів, які задовольняють критерію (початкове значення 0)
	int k = 0;	// кількість елементів, які задовольняють критерію (початкове значення 0)
	CalcRows(R, rowCount, colCount, 0, S, k);
	cout << "S = " << S << endl;
	cout << "k = " << k << endl;
	cout << endl;
	PrintRows(R, rowCount, colCount, 0);

	for (int i = 0; i < rowCount; i++)
		delete[] R[i];
	delete[] R;

	return 0;
}

// Формування поточного рядка матриці випадковими числами з діапазону [Low, High].
// rowNo - номер поточного рядка, colNo - номер поточного стовпчика (початкове значення 0)
void CreateRow(int** R, const int rowNo, const int colCount, const int Low,
	const int High, int colNo)
{
	R[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < colCount - 1)
		CreateRow(R, rowNo, colCount, Low, High, colNo + 1);
}

// Формування всіх рядків матриці.
// rowNo - номер поточного рядка (початкове значення 0)
void CreateRows(int** R, const int rowCount, const int colCount, const int Low,
	const int High, int rowNo)
{
	CreateRow(R, rowNo, colCount, Low, High, 0);
	if (rowNo < rowCount - 1)
		CreateRows(R, rowCount, colCount, Low, High, rowNo + 1);
}

// Виведення поточного рядка матриці у вигляді рядка таблиці.
// rowNo - номер поточного рядка, colNo - номер поточного стовпчика (початкове значення 0)
void PrintRow(int** R, const int rowNo, const int colCount, int colNo)
{
	cout << setw(4) << R[rowNo][colNo];
	if (colNo < colCount - 1)
		PrintRow(R, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}

// Виведення всіх рядків матриці у вигляді таблиці.
// rowNo - номер поточного рядка (початкове значення 0)
void PrintRows(int** R, const int rowCount, const int colCount, int rowNo)
{
	PrintRow(R, rowNo, colCount, 0);
	if (rowNo < rowCount - 1)
		PrintRows(R, rowCount, colCount, rowNo + 1);
	else
		cout << endl;
}

// Обмін місцями двох рядків матриці.
// colNo - номер поточного стовпчика (початкове значення 0)
void Change(int** R, const int row1, const int row2, const int colCount, int colNo)
{
	int tmp = R[row1][colNo];	// допоміжна змінна для обміну значень
	R[row1][colNo] = R[row2][colNo];
	R[row2][colNo] = tmp;
	if (colNo < colCount - 1)
		Change(R, row1, row2, colCount, colNo + 1);
}

// Один прохід методу обміну ("бульбашки"): порівняння сусідніх рядків i1 та i1+1
// і обмін їх місцями, якщо порядок неправильний.
// Ключі впорядкування: 1-й стовпчик за спаданням,
// 2-й стовпчик за спаданням, 3-й стовпчик за зростанням.
// i0 - номер поточного проходу, i1 - номер поточного рядка (початкове значення 0)
void SortPass(int** R, const int rowCount, const int colCount, const int i0, int i1)
{
	if (i1 < rowCount - i0 - 1)
	{
		if ((R[i1][0] < R[i1 + 1][0])
			||
			(R[i1][0] == R[i1 + 1][0] &&
				R[i1][1] < R[i1 + 1][1])
			||
			(R[i1][0] == R[i1 + 1][0] &&
				R[i1][1] == R[i1 + 1][1] &&
				R[i1][2] > R[i1 + 1][2]))
			Change(R, i1, i1 + 1, colCount, 0);
		SortPass(R, rowCount, colCount, i0, i1 + 1);
	}
}

// Впорядкування рядків матриці: послідовне виконання проходів методу обміну.
// i0 - номер поточного проходу (початкове значення 0)
void Sort(int** R, const int rowCount, const int colCount, int i0)
{
	if (i0 < rowCount - 1)
	{
		SortPass(R, rowCount, colCount, i0, 0);
		Sort(R, rowCount, colCount, i0 + 1);
	}
}

// Обчислення кількості k та суми S елементів поточного рядка, які задовольняють
// критерію: додатні, або такі, що НЕ мають обидва індекси парними.
// Ці елементи замінюються нулями.
// rowNo - номер поточного рядка, colNo - номер поточного стовпчика (початкове значення 0)
void CalcRow(int** R, const int rowNo, const int colCount, int colNo, int& S, int& k)
{
	if (R[rowNo][colNo] > 0 || !(rowNo % 2 == 0 && colNo % 2 == 0))
	{
		S += R[rowNo][colNo];
		k++;
		R[rowNo][colNo] = 0;
	}
	if (colNo < colCount - 1)
		CalcRow(R, rowNo, colCount, colNo + 1, S, k);
}

// Обчислення кількості k та суми S елементів усієї матриці, які задовольняють критерію.
// Значення S і k мають бути обнулені перед першим викликом.
// rowNo - номер поточного рядка (початкове значення 0)
void CalcRows(int** R, const int rowCount, const int colCount, int rowNo, int& S, int& k)
{
	CalcRow(R, rowNo, colCount, 0, S, k);
	if (rowNo < rowCount - 1)
		CalcRows(R, rowCount, colCount, rowNo + 1, S, k);
}