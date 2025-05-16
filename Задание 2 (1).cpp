#include <iostream>
#include <cmath>
using namespace std;
/**
*@brief Считывает значиния с клавиатуры с проверкой ввода
*@return возвращает значение, если оно правильное , иначе завершает программу
*/
double getValue();

/**
*@brief проверяет существование треуольника по введенным сторонам
* @param a - первая стророна треугольника
* @param b - вторая стророна треугольника
* @param c - третья стророна треугольника
* @param length - длина прямоугольника
* @param width - ширина прямоугольника
* @return возвращает значение a,b,c, если треугольник существует, иначе завершает программу
*/
double checkExist(const double a, const double b, const  double c, const double length, const double width);

/**
*@brief рассчитывает периметр треугольника
* @param a первая стророна треугольника
* @param b вторая стророна треугольника
* @param c третья стророна треугольника
* @return возвращает периметр
*/
double getPerimetr(const double a, const double b, const double c);

/**
*@brief рассчитывает площадь прямоугольника
* @param length первая стророна прямоугольника
* @param width вторая стророна прямоугольника
* @return возвращает площадь прямоугольника
*/
double getrectangleArea(const double length, const double width);

/**
*@brief рассчитывает площадь треугольника
* @param a первая стророна треугольника
* @param b вторая стророна треугольника
* @param c третья стророна треугольника
* @return p - площадь треугольника
*/
double gettheareaofthetriangle(const double a, const double b, const double c);
/**
* @brief проверяет что введенные данные положительные
* @param a первая стророна треугольника
* @param b вторая стророна треугольника
* @param c третья стророна треугольника
* @param length - длина прямоугольника
* @param width - ширина прямоугольника
*/
void isPositive(const double a, const double b, const double c, const double length, const double width);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите длину прямоугольника: ";
    double length = getValue();

    cout << "Введите ширину прямоугольника: ";
    double width = getValue();

    cout << "Введите длину стороны a треугольника: ";
    double a = getValue();

    cout << "Введите длину стороны b треугольника: ";
    double b = getValue();

    cout << "Введите длину стороны c треугольника: ";
    double c = getValue();
    isPositive(a, b, c, length, width);
    checkExist(a, b, c, length, width);
    cout << "Площадь прямоугольника: " << getrectangleArea(length, width) << endl;
    cout << "Периметр треугольника: " << getPerimetr(a, b, c) << endl;
    cout << "Площадь треугольника: " << gettheareaofthetriangle(a, b, c) << endl;
    return 0;
}

double getValue()
{
    double value;
    cin >> value;
    if (cin.fail())
    {
        cout << "Некорректное значение" << endl;
        abort();
    }
    return value;
}

double checkExist(const double a, const double b, const double c, const double length, const double width)
{
    if (a + b <= c || a + c <= b || b + c <= a)
    {
        cout << "Треугольник не существует" << endl;
        abort();
    }
    return a, b, c;
}

void isPositive(const double a, const double b, const double c, const double length, const double width)
{
    if (a <= 0 || b <= 0 || c <= 0 || length <= 0 || width <= 0)
    {
        cout << "Стороны треугольника или прямоугольника не могут быть меньше или равны 0" << endl;
        abort();
    }
}

double getrectangleArea(const double length, const double width)
{
    return (length * width);
}

double getPerimetr(const double a, const double b, const double c)
{
    return (a + b + c);
}

double gettheareaofthetriangle(const double a, const double b, const double c)
{
    const double p = (a + b + c) / 2;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    return S;
}
