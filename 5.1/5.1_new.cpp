#include <iostream>  
#include <fstream>  
#include <algorithm>  
#include <string>  
#include <math.h>   
using namespace std;

string encrypt(string message, int key) { //шифрование
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        if (message[i] >= 'a' && message[i] <= 'z') { //для нижнего регистра
            char ch = (message[i] + key - 'a') % 26 + 'a'; 
            result += ch;
        }
        else if (message[i] >= 'A' && message[i] <= 'Z') {//для верхнего регистра
            char ch = (message[i] + key - 'A') % 26 + 'A';
            result += ch;
        }
        else {
            throw runtime_error("Недопустимый символ в сообщении");
        }
    }
    return result;
}

string decrypt(string message, int key) { //дешифрование
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        char ch = message[i];
        if (isalpha(ch)) { //проверка на то, является ли буквой
            if (islower(ch)) { //для нижнего регистра
                ch -= key;
                if (ch < 'a') {
                    ch += 26;
                }
            }
            else { //для верхнего регистра
                ch -= key;
                if (ch < 'A') {
                    ch += 26;
                }
            }
        }
        result += ch;
    }
    return result;
}

string get_password() {
    string password;
    cout << "Введите пароль: ";
    cin >> password;
    return password;
}

void write_to_file(string file_name, string text) {
    ofstream file(file_name);
    file << text;
    file.close();
    cout << "Текст записан в файл: " << file_name << endl;
}

string read_from_file(string file_name) {
    ifstream file(file_name);
    string text((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return text;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string message, password;
    int key;
    char answer;

    cout << "Введите исходный текст: ";
    getline(cin, message);

    cout << "Введите ключ: ";
    cin >> key;

    write_to_file("source.txt", message);
    password = get_password();
    // шифрование   
    if (password == "secret") {
        message = read_from_file("source.txt");
        message = encrypt(message, key);
        write_to_file("encoded_message.txt", message);
        cout << "Текст зашифрован и записан в encoded_message.txt" << endl;
    }
    else {
        cout << "Неверный пароль, шифрование невозможно" << endl;
    }

    password = get_password();
    // дешифрование   
    if (password == "secret") {
        message = read_from_file("encoded_message.txt");
        message = decrypt(message, key);
        write_to_file("decoded_message.txt", message);
        cout << "Текст расшифрован и записан в decoded_message.txt" << endl;
    }
    else {
        cout << "Неверный пароль, дешифрование невозможно" << endl;
    }
    cout << "Нажмите 'p', чтобы распечатать файлы: ";
    cin >> answer;
    if (answer == 'p' || answer == 'P') {
        cout << "Файл source.txt:" << endl;
        cout << endl;
        cout << read_from_file("source.txt") << endl;
        cout << endl;
        cout << "Файл encoded_message.txt:" << endl;
        cout << endl;
        cout << read_from_file("encoded_message.txt") << endl;
        cout << endl;
        cout << "Файл decoded_message.txt:" << endl;
        cout << endl;
        cout << read_from_file("decoded_message.txt") << endl;
    }
}
