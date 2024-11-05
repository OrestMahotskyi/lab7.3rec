#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

// Функція для введення одного рядка матриці
void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = "; // Запит на введення елемента
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1) {
        InputRow(a, rowNo, colCount, colNo + 1); // Рекурсивний виклик для наступного стовпця
    }
}

// Функція для введення всіх рядків матриці
void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo < rowCount) {
        InputRow(a, rowNo, colCount, 0); // Введення рядка
        InputRows(a, rowCount, colCount, rowNo + 1); // Рекурсивний виклик для наступного рядка
    }
}

// Функція для перевірки наявності нульового елемента в рядку
bool HasZero(int** a, const int rowNo, const int colCount, int colNo) {
    if (colNo < colCount) {
        if (a[rowNo][colNo] == 0) {
            return true; // Знайдено нуль
        }
        return HasZero(a, rowNo, colCount, colNo + 1); // Рекурсивний виклик для наступного стовпця
    }
    return false; // Нульових елементів не знайдено
}

// Функція для підрахунку кількості рядків з принаймні одним нульовим елементом
int CountRowsWithZero(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo < rowCount) {
        return (HasZero(a, rowNo, colCount, 0) ? 1 : 0) + CountRowsWithZero(a, rowCount, colCount, rowNo + 1); // Рекурсивний виклик
    }
    return 0; // Повернення 0, якщо рядків не залишилося
}

// Функція для перевірки наявності однакових елементів в стовпці
void CheckIdenticalSequence(int** a, const int rowCount, int colNo, int currentRow, int& length, int& maxLength) {
    if (currentRow < rowCount) {
        if (currentRow == 0 || a[currentRow][colNo] == a[currentRow - 1][colNo]) {
            length++; // Збільшення довжини, якщо елементи однакові
        } else {
            if (length > maxLength) {
                maxLength = length; // Оновлення максимальної довжини
            }
            length = 1; // Скидання довжини до 1
        }
        CheckIdenticalSequence(a, rowCount, colNo, currentRow + 1, length, maxLength); // Рекурсивний виклик
    } else {
        if (length > maxLength) {
            maxLength = length; // Оновлення максимальної довжини, якщо потрібно
        }
    }
}

// Функція для знаходження стовпця з найдовшою послідовністю однакових елементів
void FindLongestSequence(int** a, const int rowCount, const int colCount, int colNo, int& maxCol, int& maxLength) {
    if (colNo < colCount) {
        int currentLength = 0; // Поточна довжина послідовності
        int currentMaxLength = 0; // Максимальна довжина послідовності для цього стовпця

        CheckIdenticalSequence(a, rowCount, colNo, 0, currentLength, currentMaxLength); // Виклик перевірки послідовності

        if (currentMaxLength > maxLength) {
            maxLength = currentMaxLength; // Оновлення максимальної довжини
            maxCol = colNo; // Оновлення номера стовпця
        }
        FindLongestSequence(a, rowCount, colCount, colNo + 1, maxCol, maxLength); // Рекурсивний виклик для наступного стовпця
    }
}

int main() {
    srand((unsigned)time(NULL)); // Ініціалізація генератора випадкових чисел
    int rowCount, colCount; // Кількість рядків і стовпців
    cout << "Кількість рядків = "; cin >> rowCount; // Запит на введення кількості рядків
    cout << "Кількість стовпців = "; cin >> colCount; // Запит на введення кількості стовпців

    // Динамічне виділення пам'яті для матриці
    int** a = new int*[rowCount];
    for (int i = 0; i < rowCount; i++) {
        a[i] = new int[colCount];
    }

    InputRows(a, rowCount, colCount, 0); // Введення всіх рядків матриці

    int zeroCount = CountRowsWithZero(a, rowCount, colCount, 0); // Підрахунок рядків з нульовими елементами
    cout << "Кількість рядків з принаймні одним нульовим елементом: " << zeroCount << endl; // Виведення результату
    int maxCol = -1; // Номер стовпця з найдовшою послідовністю
    int maxLength = 0; // Максимальна довжина послідовності
    FindLongestSequence(a, rowCount, colCount, 0, maxCol, maxLength); // Пошук стовпця з найдовшою послідовністю

    // Виведення результату
    cout << "Стовпець з найдовшою послідовністю однакових елементів: " << maxCol << " з довжиною " << maxLength << endl;

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0; // Завершення програми
}