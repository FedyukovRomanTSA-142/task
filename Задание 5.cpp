
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
*@brief Расчитывает сумму N члена
*@param N члены последовательности
*@return возвращает значение суммы
*/
double sumFirstN(const int n);

/**
*@brief Вычисления членов последовательности, по модулю не меньших заданного числа e
*param Числа которые больше e
*@return возвращает значение суммы
*/
double sumModuloE(const double  e);


/**
*@brief вычисляет рекурентное выражение
*param k переменная
*@return -1.0 / (k + 1) / (k + 2)
*/
double recur(const int k);


/**
*@brief Функция для проверки ввода n
*@return возвращает n если ввидена правильно, в противном случае -1
*/
int getValidN();

/**
*@brief Функция для проверки ввода e
*@return возвращает n если ввидена правильно, в противном случае -1
*/
double getValidE();

/**
*@brief Точка входа для программы
*@return 0
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    int n = getValidN();
    if (n == -1)
    {
        return 1; // Возвращаем код ошибки
    }

    cout << "Сумма первых " << n << " членов последовательности: " << sumFirstN(n) << endl;

    double e = getValidE();
    if (e == -1)
    {
        return 1; // Возвращаем код ошибки
    }

    cout << "Сумма всех членов последовательности, модуль которых не меньше " << e << ": " << sumModuloE(e) << endl;

    return 0;
}


// Функция для проверки корректности ввода значения n
int getValidN()
{
    int n;
    cout << "Введите значение n: ";
    cin >> n;

    if (cin.fail())
    {
        return -1;
    }

    if (n <= 0)
    {
        cout << "Ошибка: n должно быть положительным числом." << endl;
        return -1; // Возвращаем -1 для обработки ошибки
    }

    return n;
}

// Функция для проверки корректности ввода значения e
double getValidE()
{
    double e;
    cout << "Введите значение e: ";
    cin >> e;

    if (e < numeric_limits<double>::epsilon())
    {
        cout << "Ошибка: e должно быть положительным числом." << endl;
        return -1; // Возвращаем -1 для обработки ошибки
    }

    return e;
}


// Функция для вычисления первых членов последовательности
double sumFirstN(const int n)
{
    const double a0 = 1;
    double current = a0;
    double sum = current;

    for (int k = 0; k < n - 1; ++k) {
        current *= recur(k);
        sum += current;
    }

    return sum;
}

    // Функция для вычисления членов последовательности, по модулю не меньших заданного числа e. 
    double sumModuloE(const double  e)
    {
        double sum = 0;
        double current = 1;
        int k = 0;

        while (abs(current) < e)
        {
            sum += current;
            current *= recur(k++);

        }

        return sum;
    }

    double recur(const int k)
    {
        return -1.0 / (k + 1) / (k + 2);
    }