#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
* @brief Рассчитывает сумму N членов последовательности
* @param n количество членов последовательности
* @return возвращает значение суммы
*/
double sumFirstN(const int n);

/**
* @brief Вычисляет сумму членов последовательности, по модулю не меньших заданного числа e
* @param e минимальное значение модуля члена последовательности
* @return возвращает значение суммы
*/
double sumModuloE(const double e);

/**
* @brief Вычисляет рекуррентное выражение
* @param k индекс члена последовательности
* @return -1.0 / (k + 1) / (k + 2)
*/
double recur(const int k);

/**
* @brief Функция для проверки ввода n
* @return возвращает n если введено правильно, в противном случае -1
*/
int getValidN();

/**
* @brief Функция для проверки ввода e
* @return возвращает e если введено правильно, в противном случае -1
*/
double getValidE();

/**
* @brief Точка входа для программы
* @return 0
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    
    int n = getValidN();
    if (n == -1)
    {
        cerr << "Ошибка ввода n" << endl;
        return 1;
    }

    cout << "Сумма первых " << n << " членов последовательности: " << sumFirstN(n) << endl;

    double e = getValidE();
    if (e == -1)
    {
        cerr << "Ошибка ввода e" << endl;
        return 1;
    }

    cout << "Сумма всех членов последовательности, модуль которых не меньше " << e << ": " << sumModuloE(e) << endl;

    return 0;
}

int getValidN()
{
    int n = 0;
    cout << "Введите значение n: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: n должно быть положительным целым числом." << endl;
        return -1;
    }

    return n;
}

double getValidE()
{
    double e = 0.0;
    cout << "Введите значение e: ";
    cin >> e;

    if (cin.fail() || e <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: e должно быть положительным числом." << endl;
        return -1.0;
    }

    return e;
}

double sumFirstN(const int n)
{
    const double a0 = 1.0;
    double current = a0;
    double sum = current;

    for (int k = 0; k < n - 1; ++k) {
        current *= recur(k);
        sum += current;
    }

    return sum;
}

double sumModuloE(const double e)
{
    double sum = 0.0;
    double current = 1.0;
    int k = 0;

    while (abs(current) >= e)
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
