#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

/**
 * @brief оператор выбоа способа заполнения массива
 * @param RANDOM = 0 автоматическое заполнение
 * @param MANUALLY =1 ручное заполнение
 */
enum SELECT
{
    RANDOM = 0,
    MANUALLY = 1
};

/**
 * @brief проверяет размер массива
 * @param n - размер массива
 */
void checkN(const int n);

/**
 * @brief считывает размер массива
 * @return размер массива в беззнаковом типе данных
 */
size_t getSize();

/**
 * @brief считывает значение типа int
 * @return считанное значение целочисленное
 */
int getNumber();

/**
 * @brief вывод массива на экран
 * @param arr - массив
 * @param n - размер массива
 */
void printArray(const int* arr, const int n);

/**
 * @brief заполнение массива автоматически случайнвми числами в заданном диапазоне
 * @param arr - массив
 * @param n - размер массива
 * @param min - минимальное значение диапазона значений элементов массива
 * @param max - максимальное значение диапазона значений элементов массива
 */
void fillArrayRandom(int* arr, const int n, const int min, const int max);

/**
 * @brief проверяет диапазон
 * @param min - минимальное значение диапазона значений элементов массива
 * @param max - максимальное значение диапазона значений элементов массива
 */
void checkRange(const int min, const int max);

/**
 * @brief вычисляет сумму всех отрицательных элементов в массиве
 * @param arr: указатель на массив целых чисел, в котором нужно найти отрицательные элементы
 * @param n: количество элементов в массиве
 * @return sum
 */
int sumNegativeElements(const int* arr, const int n);

/**
 * @brief подсчитывает количество положительных элементов в массиве, которые не превышают значение a
 * @param arr: указатель на массив целых чисел, в котором нужно найти положительные элементы.
 * @param n: количество элементов в массиве
 * @param A: целое число, с которым сравниваются элементы
 * @return  int: количество положительных элементов в массиве, которые не превышают значение a
 */
int countPositiveElementsUpToA(const int* arr, const int n, const int a);

/**
 * @brief подсчитывает количество положительных элементов в массиве, которые не превышают значение a
 * @param arr: указатель на массив целых чисел, в котором нужно найти последнюю пару с разными знаками.
 * @param n: количество элементов в массиве
 * @return  int: индекс последней пары элементов с разными знаками если нет такой пары, то возвращается -1
 */
int findLastPairWithDifferentSigns(const int* arr, const int n);

/**
 * @brief заполнение массива вручную
 * @param arr - массив
 * @param n - размер массива
 * @param min - минимальное значение диапазона значений элементов массива
 * @param max - максимальное значение диапазона значений элементов массива
 */
void fillArray(int* arr, const int n, const int min, const int max);

/**
* @brief точка входа в программу
* @return 0 - если программма выполнена корректно, инече -1
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    int n = getSize();
    int* arr = new int[n];

    cout << "Введите минимальное и максимальное значение диапазона: ";
    int minValue = getNumber();
    int maxValue = getNumber();
    checkRange(minValue, maxValue);

    cout << "Введите выбор для заполнения массива: " << endl
        << RANDOM << " Для случайного заполнения" << endl
        << MANUALLY << " Для ручного заполнения" << endl;

    int choice = getNumber();

    switch ((enum SELECT)choice)
    {
    case RANDOM:
        fillArrayRandom(arr, n, minValue, maxValue);
        break;
    case MANUALLY:
        fillArray(arr, n, minValue, maxValue);
        break;
    default:
        cout << "Ваш выбор неверен" << endl;
        delete[] arr;
        return -1;
    }

    cout << "Элементы массива:" << endl;
    printArray(arr, n);

    // Вызов функций
    cout << "Сумма отрицательных элементов: " << sumNegativeElements(arr, n) << endl;

    cout << "Введите значение a: ";
    int a = getNumber();
    cout << "Количество положительных элементов до " << a << ": " << countPositiveElementsUpToA(arr, n, a) << endl;

    int lastPairIndex = findLastPairWithDifferentSigns(arr, n);
    if (lastPairIndex != -1)
    {
        cout << "Индекс последней пары с разными знаками: " << lastPairIndex << ", значение: " << arr[lastPairIndex] << ", " << arr[lastPairIndex - 1] << endl;
    }
    else
    {
        cout << "Не найдено ни одной пары с разными знаками." << endl;
    }

    delete[] arr;
    return 0;
}

void checkN(const int n)
{
    if (n <= 0)
    {
        cout << "Неправильный размер массива" << endl;
        abort();
    }
}

size_t getSize()
{
    cout << "Введите размер массива: ";
    int n = 0;
    cin >> n;
    checkN(n);
    return (size_t)n;
}

int getNumber()
{
    int number = 0;
    cin >> number;
    if (cin.fail())
    {
        cout << "Неправильный ввод данных";
        abort();
    }
    return number;
}

void printArray(const int* arr, const int n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

void fillArrayRandom(int* arr, const int n, const int min, const int max)
{
    srand(time(0));
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

void checkRange(const int min, const int max)
{
    if (min > max)
    {
        cout << "Введен неправильный диапазон" << endl;
        abort();
    }
}

int sumNegativeElements(const int* arr, const int n)
{
    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            sum += arr[i];
        }
    }
    return sum;
}

int countPositiveElementsUpToA(const int* arr, const int n, const int A)
{
    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] > 0 && arr[i] <= A)
        {
            count++;
        }
    }
    return count;
}

int findLastPairWithDifferentSigns(const int* arr, const int n)
{
    for (int i = n - 1; i > 0; i--) // Исправлено: i++ на i-- и тип на int
    {
        if (arr[i] * arr[i - 1] < 0)
        {
            return i;
        }
    }
    return -1;
}

void fillArray(int* arr, const int n, const int min, const int max)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << "Enter value for arr[" << i << "]: ";
        arr[i] = getNumber();
        if (arr[i] < min || arr[i] > max)
        {
            cout << "Значение вне диапазона" << endl;
            i--;
        }
    }
}
