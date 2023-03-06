#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <windows.h>

using namespace std;

const vector<char> a = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm' };
const vector<char> A = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
const vector<char> sumb = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
const vector<char> sumbol = { '!', '@', '#', '$', '%', '&', '(', ')', '*', '+', '-', '<', '=', '>', '?', '[', ']', '^', '_', '{', '|', '}', '~' };

void passGenerator(int passLength, int numOfPasswords) {
    vector<char> symbols;
    symbols.reserve(a.size() + A.size() + sumb.size() + sumbol.size());
    symbols.insert(symbols.end(), a.begin(), a.end());
    symbols.insert(symbols.end(), A.begin(), A.end());
    symbols.insert(symbols.end(), sumb.begin(), sumb.end());
    symbols.insert(symbols.end(), sumbol.begin(), sumbol.end());

    mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(0, symbols.size() - 1);

    ofstream out("out.txt");
    if (!out.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи" << endl;
        return;
    }

    for (int k = 0; k < numOfPasswords; k++) {
        for (int i = 0; i < passLength; i++) {
            out << symbols[dist(gen)];
        }
        out << endl;
    }

    out.close();
}

int main() {

    system("title 2.0");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);


    int passLength, numOfPasswords;
    cout << "Введите длину пароля для генерации: ";
    cin >> passLength;

    cout << "Введите количество паролей для генерации: ";
    cin >> numOfPasswords;

    cout << "Будет сгенерировано паролей: " << numOfPasswords << endl << endl;

    auto startTime = chrono::high_resolution_clock::now();
    passGenerator(passLength, numOfPasswords);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    cout << "Пароли успешно сгенерированы и записаны в файл out.txt" << endl;
    cout << "Программа завершена" << endl;
    cout << "Время работы программы: " << duration.count() / 1000000.0 << " секунд" << endl;

    system("pause");
    return 0;
}