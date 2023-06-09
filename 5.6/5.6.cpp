#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>  
#include <locale.h>
using namespace std;
// Функция шифрования
string encrypt(string text, int k, int* perm) {
    string result = "";
    int n = text.length();
    int groups = n / k;
    if (n % k != 0) {
        groups++;
    }
    for (int i = 0; i < groups; i++) {
        int start = i * k;
        int end = min(start + k, n);
        string group = text.substr(start, end - start);
        if (group.length() < k) {
            group.append(k - group.length(), ' ');
        }
        for (int j = 0; j < k; j++) {
            result += group[perm[j] - 1];
        }
    }
    return result;
}

// Функция дешифрования
string decrypt(string text, int k, int* perm) {
    string result = "";
    int n = text.length();
    int groups = n / k;
    for (int i = 0; i < groups; i++) {
        int start = i * k;
        int end = min(start + k, n);
        string group = text.substr(start, end - start);
        string decrypted_group = "";
        for (int j = 0; j < k; j++) {
            decrypted_group += group[find(perm, perm+k, j+1) - perm];
        }
        result += decrypted_group;
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

int main() {
    int k = 4;
    int perm[] = {3, 2, 4, 1};
    string plaintext;
    cout << "Введите исходный текст: ";
    getline(cin,plaintext);
    char answer;
    write_to_file("source.txt", plaintext);
    string password = get_password();
    // шифрование   
    if (password == "secret") {
        plaintext = read_from_file("source.txt");
        plaintext = encrypt(plaintext, k, perm);
        write_to_file("encoded_plaintext.txt", plaintext);
        cout << "Текст зашифрован и записан в encoded_plaintext.txt" << endl;
    }
    else {
        cout << "Неверный пароль, шифрование невозможно" << endl;
    }

    password = get_password();
    // дешифрование   
    if (password == "secret") {
        plaintext = read_from_file("encoded_plaintext.txt");
        plaintext = decrypt(plaintext, k, perm);
        write_to_file("decoded_plaintext.txt", plaintext);
        cout << "Текст расшифрован и записан в decoded_plaintext.txt" << endl;
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
        cout << "Файл encoded_plaintext.txt:" << endl;
        cout << endl;
        cout << read_from_file("encoded_plaintext.txt") << endl;
        cout << endl;
        cout << "Файл decoded_plaintext.txt:" << endl;
        cout << endl;
        cout << read_from_file("decoded_plaintext.txt") << endl;
    }
    
    return 0;
}
