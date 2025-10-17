#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void fillRandom(int* arr, size_t size, int minVal, int maxVal);
void fillKeyboard(int* arr, size_t size, int minVal, int maxVal);
void printArray(int* arr, size_t size);
int sumNegative(int* arr, size_t size);
int countPositiveLessThanA(int* arr, size_t size, int A);
int lastDifferentSignsPair(int* arr, size_t size);
int getValidatedInput(const string& prompt, int minVal, int maxVal);

int main() {
    setlocale(LC_ALL, "Russian");

    int minValue, maxValue;
    cout << "Введите минимальное значение для массива: ";
    cin >> minValue;
    cout << "Введите максимальное значение для массива: ";
    cin >> maxValue;

    if (minValue >= maxValue) {
        cout << "Ошибка: минимальное значение должно быть меньше максимального!" << endl;
        return 1;
    }

    int size = getValidatedInput("Введите размер массива: ", 1, 1000);

    int* arr = new int[size];

    cout << "\nВыберите способ заполнения массива:" << endl;
    cout << "1 - Заполнить случайными числами" << endl;
    cout << "2 - Ввести с клавиатуры" << endl;
    
    int choice = getValidatedInput("Ваш выбор: ", 1, 2);

    switch (choice) {
    case 1:
        fillRandom(arr, size, minValue, maxValue);
        break;
    case 2:
        fillKeyboard(arr, size, minValue, maxValue);
        break;
    }

    printArray(arr, size);

    int sum = sumNegative(arr, size);
    cout << "1. Сумма отрицательных элементов: " << sum << endl;

    int A = getValidatedInput("\nВведите число A для второго задания: ", minValue, maxValue);
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

    delete[] arr;
    return 0;
}

int getValidatedInput(const string& prompt, int minVal, int maxVal) {
    int value;
    bool validInput = false;
    
    do {
        cout << prompt;
        
        if (!(cin >> value)) {
            cout << "Ошибка ввода! Введите целое число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (value < minVal || value > maxVal) {
            cout << "Число должно быть в диапазоне [" << minVal << "; " << maxVal << "]. Повторите ввод: ";
        }
        else {
            validInput = true;
        }
    } while (!validInput);
    
    return value;
}

void fillRandom(int* arr, size_t size, int minVal, int maxVal) {
    srand(time(0));
    int range = maxVal - minVal + 1;
    
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % range + minVal;
    }
    cout << "Массив заполнен случайными числами в диапазоне [" << minVal << "; " << maxVal << "]." << endl;
}

void fillKeyboard(int* arr, size_t size, int minVal, int maxVal) {
    cout << "Введите " << size << " целых чисел в диапазоне [" << minVal << "; " << maxVal << "]:" << endl;

    for (size_t i = 0; i < size; i++) {
        arr[i] = getValidatedInput("Элемент " + to_string(i + 1) + ": ", minVal, maxVal);
    }
    cout << "Массив заполнен числами с клавиатуры." << endl;
}

void printArray(int* arr, size_t size) {
    cout << "Массив: ";
    for (size_t i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sumNegative(int* arr, size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] < 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int countPositiveLessThanA(int* arr, size_t size, int A) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] > 0 && arr[i] <= A) {
            count++;
        }
    }
    return count;
}

int lastDifferentSignsPair(int* arr, size_t size) {
    int lastIndex = -1;

    for (size_t i = 0; i < size - 1; i++) {
        bool currentNonNegative = arr[i] >= 0;
        bool nextNonNegative = arr[i + 1] >= 0;

        if (currentNonNegative != nextNonNegative) {
            lastIndex = static_cast<int>(i);
        }
    }

    return lastIndex;
}
