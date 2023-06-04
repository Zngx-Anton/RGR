#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <clocale>
#include <Windows.h>
using namespace std;

string atbash(string text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) { // uppercase
                result += (char)('Z' - (text[i] - 'A'));
            }
            else { // lowercase
                result += (char)('z' - (text[i] - 'a'));
            }
        }
        else { // not a letter
            result += text[i];
        }
    }
    return result;
}
string atbash_rus(string text) {
    string result = "";
    string a = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string b = a;
    reverse(b.begin(), b.end());
    string A = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    string B = A;
    reverse(B.begin(), B.end());
    for (int i = 0; i < text.length(); i++) {
        if (a.find(text[i]) != string::npos) { //если символ существует в строке "а" 
            int index = a.find(text[i]); //ищем его индекс 
            text[i] = b[index]; //находим символ на зеркальной стороне 
        }
        else if (A.find(text[i]) != string::npos) { //для символов в верхнем регистре 
            int index = A.find(text[i]);
            text[i] = B[index];
        }
        result += text[i]; //собираем результат 
    }
    return result;
}

string get_password() {
    string password;
    cout << "Введите пароль: ";
    cin >> password;
    return password;
}

void write_to_file(string filename, string text) {
    ofstream file(filename);
    file << text;
    file.close();
    cout << "Текст записан в файл " << filename << endl;
}

string read_from_file(string filename) {
    ifstream file(filename);
    string text((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return text;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string text, password;
    char answer;

    int language;
    cout << "1.Английский\n2.Русский\nChoose(1,2): ";
    cin >> language;
    cin.ignore();
    cout << "Введите исходный текст: ";
    getline(cin, text);
    write_to_file("source.txt", text);
  
    password = get_password();

    // шифрование
    if (language == 1) {
        
        if (password == "secret") {
            text = read_from_file("source.txt");
            text = atbash(text);
            write_to_file("encoded.txt", text);
            cout << "Текст зашифрован и записан в encoded.txt" << endl;
        }
        else {
            cout << "Неверный пароль, шифрование невозможно" << endl;
        }
        password = get_password();
        // дешифрование
        if (password == "secret") {
            text = read_from_file("encoded.txt");
            text = atbash(text);
            write_to_file("decoded.txt", text);
            cout << "Текст расшифрован и записан в decoded.txt" << endl;
        }
        else {
            cout << "Неверный пароль, дешифрование невозможно" << endl;
        }
    }


    else if (language == 2) {
        
        if (password == "secret") {
            text = read_from_file("source.txt");
            text = atbash_rus(text);
            write_to_file("encoded.txt", text);
            cout << "Текст зашифрован и записан в encoded.txt" << endl;
        }
        else {
            cout << "Неверный пароль, шифрование невозможно" << endl;
        }
        password = get_password();
        // дешифрование
        if (password == "secret") {
            text = read_from_file("encoded.txt");
            text = atbash_rus(text);
            write_to_file("decoded.txt", text);
            cout << "Текст расшифрован и записан в decoded.txt" << endl;
        }
        else {
            cout << "Неверный пароль, дешифрование невозможно" << endl;
        }
    }
    else {
        cout << "Wrong Choice" << endl;
    }


    cout << "Нажмите 'p', чтобы распечатать файлы: ";
    cin >> answer;

    if (answer == 'p' || answer == 'P') {
        cout << "Файл source.txt:" << endl;
        cout << endl;
        cout << read_from_file("source.txt") << endl;
        cout << endl;
        cout << "Файл encoded.txt:" << endl;
        cout << endl;
        cout << read_from_file("encoded.txt") << endl;
        cout << endl;
        cout << "Файл decoded.txt:" << endl;
        cout << endl;
        cout << read_from_file("decoded.txt") << endl;
    }

    return 0;
}
