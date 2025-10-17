#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ============================================================================
// КОНСТАНТЫ И ПРОТОТИПЫ ФУНКЦИЙ
// ============================================================================

const int MIN_VALUE = -100;
const int MAX_VALUE = 200;
const int VALUE_RANGE = MAX_VALUE - MIN_VALUE + 1;

void fillRandom(int* arr, int size);
void fillKeyboard(int* arr, int size);
void printArray(int* arr, int size);
int sumNegative(int* arr, int size);
int countPositiveLessThanA(int* arr, int size, int A);
int lastDifferentSignsPair(int* arr, int size);

// ============================================================================
// ОСНОВНАЯ ПРОГРАММА
// ============================================================================

int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        cout << "Ошибка: размер массива должен быть положительным числом!" << endl;
        return 1;
    }

    // Динамическое выделение памяти для массива
    int* arr = new int[size];

    int choice;
    cout << "\nВыберите способ заполнения массива:" << endl;
    cout << "1 - Заполнить случайными числами" << endl;
    cout << "2 - Ввести с клавиатуры" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case 1:
        fillRandom(arr, size);
        break;
    case 2:
        fillKeyboard(arr, size);
        break;
    default:
        cout << "Неверный выбор! Заполняю случайными числами." << endl;
        fillRandom(arr, size);
        break;
    }

    printArray(arr, size);

    int sum = sumNegative(arr, size);
    cout << "1. Сумма отрицательных элементов: " << sum << endl;

    int A;
    cout << "\nВведите число A для второго задания: ";
    cin >> A;
    int count = countPositiveLessThanA(arr, size, A);
    cout << "2. Количество положительных элементов, не превосходящих " << A << ": " << count << endl;

    int lastPairIndex = lastDifferentSignsPair(arr, size);
    if (lastPairIndex != -1) {
        cout << "3. Номер последней пары соседних элементов с разными знаками: " << lastPairIndex + 1 << endl;
        cout << "   (элементы " << arr[lastPairIndex] << " и " << arr[lastPairIndex + 1] << ")" << endl;
    }
    else {
        cout << "3. Пар соседних элементов с разными знаками не найдено" << endl;
    }

    // Освобождение памяти
    delete[] arr;
    return 0;
}

// ============================================================================
// РЕАЛИЗАЦИИ ФУНКЦИЙ
// ============================================================================

void fillRandom(int* arr, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % VALUE_RANGE + MIN_VALUE;
    }
    cout << "Массив заполнен случайными числами в диапазоне [" << MIN_VALUE << "; " << MAX_VALUE << "]." << endl;
}

void fillKeyboard(int* arr, int size) {
    cout << "Введите " << size << " целых чисел в диапазоне [" << MIN_VALUE << "; " << MAX_VALUE << "]:" << endl;

    for (int i = 0; i < size; i++) {
        bool validInput = false;
        do {
            cout << "Элемент " << i + 1 << ": ";

            if (!(cin >> arr[i])) {
                cout << "Ошибка ввода! Введите целое число: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (arr[i] < MIN_VALUE || arr[i] > MAX_VALUE) {
                cout << "Число должно быть в диапазоне [" << MIN_VALUE << "; " << MAX_VALUE << "]. Повторите ввод: ";
            }
            else {
                validInput = true;
            }
        } while (!validInput);
    }
    cout << "Массив заполнен числами с клавиатуры." << endl;
}

void printArray(int* arr, int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sumNegative(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int countPositiveLessThanA(int* arr, int size, int A) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0 && arr[i] <= A) {
            count++;
        }
    }
    return count;
}

int lastDifferentSignsPair(int* arr, int size) {
    int lastIndex = -1;

    for (int i = 0; i < size - 1; i++) {
        bool currentNonNegative = arr[i] >= 0;
        bool nextNonNegative = arr[i + 1] >= 0;

        if (currentNonNegative != nextNonNegative) {
            lastIndex = i;
        }
    }

    return lastIndex;
}
