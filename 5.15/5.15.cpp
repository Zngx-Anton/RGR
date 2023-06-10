#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Функция для шифрования методом Скитала
string encrypt(const string& plaintext, int rails) {
    int length = plaintext.length();
    int numRails = min(rails, length);
    int cycle = 2 * numRails - 2;
    string ciphertext;

    for (int i = 0; i < numRails; i++) {
        for (int j = i; j < length; j += cycle) {
            ciphertext += plaintext[j];
            int k = j + cycle - 2 * i;
            if (i != 0 && i != numRails - 1 && k < length)
                ciphertext += plaintext[k];
        }
    }

    return ciphertext;
}

// Функция для дешифрования методом Скитала
string decrypt(const string& ciphertext, int rails) {
    int length = ciphertext.length();
    int numRails = min(rails, length);
    int cycle = 2 * numRails - 2;
    string plaintext(length, ' ');

    int pos = 0;
    for (int i = 0; i < numRails; i++) {
        for (int j = i; j < length; j += cycle) {
            plaintext[j] = ciphertext[pos++];
            int k = j + cycle - 2 * i;
            if (i != 0 && i != numRails - 1 && k < length)
                plaintext[k] = ciphertext[pos++];
        }
    }

    return plaintext;
}

int main() {
    setlocale(LC_ALL, "rus");
    // Открываем исходный файл для чтения
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Ошибка при открытии файла." << endl;
        return 1;
    }

    // Читаем содержимое файла
    string plaintext((istreambuf_iterator<char>(inputFile)),
        istreambuf_iterator<char>());

    // Закрываем исходный файл
    inputFile.close();

    int rails;
    cout << "Введите количество ребер скитала: ";
    cin >> rails;

    // Шифрование
    string ciphertext = encrypt(plaintext, rails);
    cout << "Зашифрованный текст: " << ciphertext << endl;

    // Открываем файл для записи зашифрованного текста
    ofstream encryptedFile("encrypted.txt");
    if (!encryptedFile) {
        cout << "Ошибка при открытии файла для записи." << endl;
        return 1;
    }

    // Записываем зашифрованный текст в файл
    encryptedFile << ciphertext;

    // Закрываем файл
    encryptedFile.close();

    // Дешифрование
    string decryptedText = decrypt(ciphertext, rails);
    cout << "Расшифрованный текст: " << decryptedText << endl;

    // Открываем файл для записи расшифрованного текста
    ofstream decryptedFile("decrypted.txt");
    if (!decryptedFile) {
        cout << "Ошибка при открытии файла для записи." << endl;
        return 1;
    }

    // Записываем расшифрованный текст в файл
    decryptedFile << decryptedText;

    // Закрываем файл
    decryptedFile.close();

    return 0;
}
