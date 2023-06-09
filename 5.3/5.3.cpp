#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>   
using namespace std; 
// Функция шифрования
string encrypt(string plaintext, string key) {
    string ciphertext = "";

    // Создаем таблицу замены
    vector<vector<char>> table(26, vector<char>(26));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            table[i][j] = 'A' + (i + j) % 26;
        }
    }

    string key_only_letters = "";
    for (char c : key) {
        if (isalpha(c)) {
            key_only_letters += toupper(c);
        }
    }

    int col = 0;

    // Шифруем каждый символ открытого текста
    for (char c : plaintext) {
        if (isalpha(c)) {
            c = toupper(c);
            int row = key_only_letters[col % key_only_letters.length()] - 'A';
            ciphertext += table[row][c - 'A'];
            col++;
        }
    }

    return ciphertext;
}

// Функция расшифровки
string decrypt(string ciphertext, string key) {
    string plaintext = "";

    // Создаем таблицу замены
    vector<vector<char>> table(26, vector<char>(26));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            table[i][j] = 'A' + (i + j) % 26;
        }
    }

    string key_only_letters = "";
    for (char c : key) {
        if (isalpha(c)) {
            key_only_letters += toupper(c);
        }
    }

    int col = 0;

    // Расшифровываем каждый символ шифротекста
    for (char c : ciphertext) {
        if (isalpha(c)) {
            c = toupper(c);
            int row = key_only_letters[col % key_only_letters.length()] - 'A';
            for (int i = 0; i < 26; i++) {
                if (table[row][i] == c) {
                    plaintext += 'A' + i;
                    break;
                }
            }
            col++;
        }
    }

    return plaintext;
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
    setlocale(LC_ALL, "Russian");
    string message, password,key;
    char answer;
    bool all_upper = true;
    cout << "Введите исходный текст: ";
    getline(cin, message);
    for(char c: message){
        if(islower(c)){
            all_upper = false;
            cout <<"Ошибка: строка содержит символы нижнего регистра.\n";
            break;
        }
    }
    if (all_upper){
        cout << "Введите ключ: ";
        getline(cin,key);
    
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
}
