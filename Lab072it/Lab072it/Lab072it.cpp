// Lab072it.cpp
// Heriak Vladyslav
// Лабораторна робота № 7.2.
// Опрацювання багатовимірних масивів ітераційним способом.
// Варіант 5

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int k, const int n, const int Low, const int High);
void Print(int** a, const int k, const int n);
int MinInRow(int** a, const int rowNo, const int n);
int SumMinOddRows(int** a, const int k, const int n);

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

	Create(a, k, n, Low, High);
	Print(a, k, n);

	int sum = SumMinOddRows(a, k, n);	// сума мінімальних елементів по непарних рядках
	cout << "sum of min elements in odd rows = " << sum << endl;

	for (int i = 0; i < k; i++)
		delete[] a[i];
	delete[] a;

	return 0;
}

// Формування матриці випадковими числами з діапазону [Low, High]
void Create(int** a, const int k, const int n, const int Low, const int High)
{
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = Low + rand() % (High - Low + 1);
}

// Виведення матриці у вигляді таблиці
void Print(int** a, const int k, const int n)
{
	cout << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << a[i][j];
		cout << endl;
	}
	cout << endl;
}

// Пошук мінімального елемента вказаного рядка матриці.
// rowNo - номер рядка (індекс), n - кількість стовпчиків
int MinInRow(int** a, const int rowNo, const int n)
{
	int min = a[rowNo][0];		// мінімальний елемент рядка, початкове значення: перший елемент
	for (int j = 1; j < n; j++)
		if (a[rowNo][j] < min)
			min = a[rowNo][j];
	return min;
}

// Обчислення суми мінімальних елементів по непарних рядках матриці.
// Непарні рядки за порядковим номером (1-й, 3-й, 5-й, ...)
// мають індекси 0, 2, 4, ..., тому індекс i збільшується на 2.
int SumMinOddRows(int** a, const int k, const int n)
{
	int sum = 0;		// сума мінімальних елементів непарних рядків
	for (int i = 0; i < k; i += 2)
		sum += MinInRow(a, i, n);
	return sum;
}