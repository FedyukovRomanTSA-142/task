#include <iostream>
#include <cmath>
using namespace std;
/**
 * @brief Функция для вычисления значения переменной a по заданным константам.
 * @param x значение константы .
 * @param y значение константы .
 * @param z значение константы .
 * @return Результат вычисления переменной a.
 */
double calculateA(const double x, const double y, const double z);

/**
 * @brief Функция для вычисления значения переменной b по заданным константам.
 * @param y значение константы .
 * @return Результат вычисления переменной b.
 */
double calculateB(const double y);

/**
* @brief Главная функция
* @return Возвращает 0,если функция выполнена верно
*/
int main()
{
    const double x = 2.0;
    const double y = 0.7;
    const double z = -1.0;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << "a = " << calculateA(x, y, z) << endl;
    cout << "b = " << calculateB(y) << endl;
    return 0;
}

double calculateB(const double y)
{
    return y * cos(sin(y)) + 3;
}
double calculateA(const double x, const double y, const double z)
{
    return pow((x * y * z + fabs(z * sin(y))), 1 / 3);
}


