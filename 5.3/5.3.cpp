#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>   
using namespace std; 
// Функция шифрования
string encrypt(string plaintext, string key) {
    string ciphertext = "";

    // Создаем таблицу замены
    char table[26][26];
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

    // Шифруем каждую букву открытого текста
    for (char c : plaintext) {
        if (isalpha(c)) {
            c = toupper(c);
            int row = key_only_letters[c-'A'] - 'A';
            int col = rand() % 26;
            ciphertext += table[row][col];
        }
    }

    return ciphertext;
}

// Функция расшифровки
string decrypt(string ciphertext, string key) {
    string plaintext = "";

    // Создаем таблицу замены
    char table[26][26];
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

    // Расшифровываем каждую букву шифротекста
    for (char c : ciphertext) {
        if (isalpha(c)) {
            c = toupper(c);
            int row = key_only_letters[c-'A'] - 'A';
            for (int i = 0; i < 26; i++) {
                if (table[row][i] == c) {
                    plaintext += 'A' + i;
                    break;
                }
            }
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

int main() {
    setlocale(LC_ALL,"RUS");
    string message, key, password;
    char answer;
    
    cout << "Введите исходный текст: "; 
    getline(cin, message); 
 
    write_to_file("source.txt", message); 
 
    password = get_password(); 
    
    if (password == "secret") { 
        message = read_from_file("source.txt"); 
        message = encrypt(message,key); 
        write_to_file("encoded.txt", message); 
        cout << "Текст зашифрован и записан в encoded.txt" << endl; 
    }
else { 
        cout << "Неверный пароль, шифрование невозможно" << endl; 
    }
    
    password = get_password();
    
    // дешифрование   
    if (password == "secret") { 
        message = read_from_file("encoded.txt"); 
        message = decrypt(message,key); 
        write_to_file("decoded.txt", message); 
        cout << "Текст расшифрован и записан в decoded.txt" << endl; 
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
