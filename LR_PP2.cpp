#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

void introduction()
{
	cout << "If you want 'a' to become a calculation accuracy, input it with decimal floating point" << '\n' <<
		"If you want 'a' to become a sum of first n numbers of the series, input it as an integer" << '\n' <<
		"'a' must be positive" << '\n' << '\n';
}
long double input_check()
{
	/*
	Функция, проверяет, являются ли введенные пользователем данные числом

	Если фукнция stod не срабатывает, то выводит ошибку "invalid_argument", обрабатывает ее через catch
	Если функция stod сработала, то дополнительно провяряем строку. Удаляем первое вхождение точки через erase,
	после этого циклом проходим по элементам

	Возвращает:
		number: long double  число, переведенное из input: string, которое ввел пользователь

	*/
	string input;
	bool ok = true;
	long double number = 0;

	while (ok)
	{
		getline(cin, input);
		try
		{
			number = stold(input);

			if (input.find('.') != input.npos)   input.erase(input.find('.'), 1);

			for (int i = 1; i < input.length(); ++i)
			{
				if (isdigit(input[i]) == false) throw (1);
			}
			return number;
		}
		catch (invalid_argument)
		{
			cerr << "Error(1)! Write a number!" << endl;
		}
		catch (int i)
		{
			cerr << "Error(2)! Write a number!" << endl;
		}
	}
}



long double elem_calc(long double x, long long n)
{
	/*
	Функция, считает элемент последовательности
	Аргументы: 
		x: long double  -  переменная
		n: long long  -  порядковый номер элемента
	Возвращает:
		result: long double - подсчитанное число
	*/
	long long factorial = 1;
	for (int i = 1; i <= n; ++i)
	{
		factorial *= i;
	}
	return ((pow(2, n / 2) * cos(2 * acos(0) * n / 4) * pow(x, n)) / factorial);
}


const long long one = 1;
vector <long double> iteration_calc(int n, double x0, long double sum)
{
	/*
	Функция, возвращает вектор данных для дальнейшего использования
	Аргументы: 
		n: int - порядковый номер итерации
		x0: double - переменная
		sum: long double - сумма, подсчитанная в предыдущих итерациях
	Возвращает: 
		data: vector <long double> - вектор, состоящий из данных, их используем в других векторах
	*/
	vector <long double> data;
	long double an = elem_calc(x0, n);
	sum += an;
	
	long double en = (elem_calc(x0, n + one) / sum);

	data.push_back(an); data.push_back(sum); data.push_back(en);
	return data;
}


/*Выходные данные: номер итерации (n), последний просуммированный член ряда (An),
текущая частичная сумма (Sn), точность вычисления заданной текущей частичной суммы (Cn). */
void output(int n, vector <long double> An, vector <long double> Sn, vector <long double> En)          
{
	if (abs(En[n]) > numeric_limits<long double>::min())
	cout << "[ n = " << setw(15) << n << " ][ " << "An = " << setw(15) << An[n] << " ][ " << "Sn = " << setw(15) << Sn[n] << " ][ "
		<< "En = " << setw(15) << En[n] << " ]" << '\n';
}

int YN_function()
{
	/*
	Функция узнает, вводит пользователь Y или N.
	В зависимости от этого возвращает:
		'1', если введено 'Y'
		'0', если введено 'N'
	*/
	string button;
	int end = 0;
	while (end == 0)
	{
		getline(cin, button);
		if (button[0] == 'Y' && button.length() == 1) return  1;
		if (button[0] == 'N' && button.length() == 1)  return 0;
		if (end == 0) cout << "Write 'Y' or 'N'!" << endl;
	}
}


bool finish = true;  
vector <long double> An{ 0 }, Sn{ 0 }, En{ 0 };
long double a0 = 0.0; double x0 = 0.0;
int length = 0;

int main()
{
	introduction();

	while (finish)  
	{
		cout << "Enter x: ";
		double x = input_check();

		cout << '\n' << "Enter a: ";
		long double a = input_check();

		long long n = 1;
		long double an = 0.0, sum = 0.0, en = 0.0;
		
		if (x0 == x)    //если предыдущее значение совпадает с текущим
		{
			if (a == (long long)a)   //а - число итераций
			{
				cout << "'a' is a number" << '\n' << '\n';
				cout << "Was entered previous X. Writing old calculations:" << endl;
				int count = a;

				for (n = 1; n <= count; ++n)
				{
					if (n <= length)  output(n, An, Sn, En);
					if (n==length) cout << "New calculations are: " << endl;
					if (n > length)
					{
						vector <long double> data = iteration_calc(n, x, Sn[n - 1]);
						An.push_back(data[0]);	Sn.push_back(data[1]);   En.push_back(data[2]); length = n;
						output(n, An, Sn, En);
					}
				}
			}
			else  //a - погрешность
			{
				cout << "'a' is an accuracy" << '\n' << '\n';
				cout << "Was entered previous X. Writing old calculations:" << endl;
				do
				{
					if (n <= length)   output(n, An, Sn, En);
					if (n == length) cout << "New calculations are: " << endl;
					if (n > length)
					{
						vector <long double> data = iteration_calc(n, x, Sn[n - 1]);
						An.push_back(data[0]);	Sn.push_back(data[1]);   En.push_back(data[2]); length = n;
						output(n, An, Sn, En);
					}
					n++;
				} while (a >= abs(En[n - 1]));
			}
		}
		else
		{
			An.resize(1); Sn.resize(1); En.resize(1);
			Sn;

			if (a == (long long)a)   //а - число итераций
			{
				cout << "'a' is a number" << '\n' << '\n';
				for (n = 1; n <= a; ++n)
				{
					vector <long double> data = iteration_calc(n, x, Sn[n - 1]);
					An.push_back(data[0]);	Sn.push_back(data[1]);   En.push_back(data[2]); length = n;

					output(n, An, Sn, En);
				}
			}
			else  //a - погрешность
			{
				cout << "'a' is an accuracy" << '\n' << '\n';
				do
				{
					vector <long double> data = iteration_calc(n, x, Sn[n - 1]);
					An.push_back(data[0]);	Sn.push_back(data[1]);   En.push_back(data[2]); length = n;

					output(n, An, Sn, En);

					n++;
				} while (a >= abs(En[n - 1]));
			}
		}
		a0 = a; x0 = x; 

		cout << '\n' << "Do you want to continue? Input 'Y' or 'N'" << endl;
		finish = YN_function();
	}
}