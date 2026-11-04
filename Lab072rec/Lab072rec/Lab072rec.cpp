// Lab072rec.cpp
// Heriak Vladyslav
// Лабораторна робота № 7.2.
// Опрацювання багатовимірних масивів рекурсивним способом.
// Варіант 5

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int n, const int Low,
	const int High, int colNo);
void CreateRows(int** a, const int k, const int n, const int Low,
	const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int n, int colNo);
void PrintRows(int** a, const int k, const int n, int rowNo);
int MinInRow(int** a, const int rowNo, const int n, int colNo);
int SumMinOddRows(int** a, const int k, const int n, int rowNo);

int main()
{
	srand((unsigned)time(NULL));

	int Low = -20;		// нижня межа діапазону значень елементів матриці
	int High = 50;		// верхня межа діапазону значень елементів матриці

	int k;				// кількість рядків матриці
	int n;				// кількість стовпчиків матриці
	cout << "k = "; cin >> k;
	cout << "n = "; cin >> n;

	if (k < 1 || n < 1)
	{
		cout << "k and n must be positive" << endl;
		return 1;
	}

	int** a = new int* [k];		// матриця a (динамічний двовимірний масив)
	for (int i = 0; i < k; i++)
		a[i] = new int[n];

	CreateRows(a, k, n, Low, High, 0);
	cout << endl;
	PrintRows(a, k, n, 0);

	int sum = SumMinOddRows(a, k, n, 0);	// сума мінімальних елементів по непарних рядках
	cout << "sum of min elements in odd rows = " << sum << endl;

	for (int i = 0; i < k; i++)
		delete[] a[i];
	delete[] a;

	return 0;
}

// Формування поточного рядка матриці випадковими числами з діапазону [Low, High].
// rowNo - номер поточного рядка, colNo - номер поточного стовпчика (початкове значення 0)
void CreateRow(int** a, const int rowNo, const int n, const int Low,
	const int High, int colNo)
{
	a[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < n - 1)
		CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

// Формування всіх рядків матриці.
// rowNo - номер поточного рядка (початкове значення 0)
void CreateRows(int** a, const int k, const int n, const int Low,
	const int High, int rowNo)
{
	CreateRow(a, rowNo, n, Low, High, 0);
	if (rowNo < k - 1)
		CreateRows(a, k, n, Low, High, rowNo + 1);
}

// Виведення поточного рядка матриці у вигляді рядка таблиці.
// rowNo - номер поточного рядка, colNo - номер поточного стовпчика (початкове значення 0)
void PrintRow(int** a, const int rowNo, const int n, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < n - 1)
		PrintRow(a, rowNo, n, colNo + 1);
	else
		cout << endl;
}

// Виведення всіх рядків матриці у вигляді таблиці.
// rowNo - номер поточного рядка (початкове значення 0)
void PrintRows(int** a, const int k, const int n, int rowNo)
{
	PrintRow(a, rowNo, n, 0);
	if (rowNo < k - 1)
		PrintRows(a, k, n, rowNo + 1);
	else
		cout << endl;
}

// Пошук мінімального елемента вказаного рядка матриці.
// rowNo - номер рядка (індекс), colNo - номер поточного стовпчика (початкове значення 0)
int MinInRow(int** a, const int rowNo, const int n, int colNo)
{
	int min;		// мінімальний елемент серед решти елементів рядка (правіше від поточного)
	if (colNo < n - 1)
		min = MinInRow(a, rowNo, n, colNo + 1);
	else
		min = a[rowNo][colNo];		// останній елемент рядка вважається мінімальним
	if (a[rowNo][colNo] < min)
		return a[rowNo][colNo];
	else
		return min;
}

// Обчислення суми мінімальних елементів по непарних рядках матриці.
// Непарні рядки за порядковим номером (1-й, 3-й, 5-й, ...)
// мають індекси 0, 2, 4, ..., тому rowNo збільшується на 2.
// rowNo - номер поточного рядка (початкове значення 0)
int SumMinOddRows(int** a, const int k, const int n, int rowNo)
{
	if (rowNo < k)
		return MinInRow(a, rowNo, n, 0) + SumMinOddRows(a, k, n, rowNo + 2);
	else
		return 0;
}