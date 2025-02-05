#include <iostream>  
#include <fstream>  
#include <algorithm>  
#include <string>  
#include <math.h>   
using namespace std;

string encrypt(string message, int key) {
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            char ch = (message[i] + key - 'a') % 26 + 'a';
            result += ch;
        }
        else if (message[i] >= 'A' && message[i] <= 'Z') {
            char ch = (message[i] + key - 'A') % 26 + 'A';
            result += ch;
        }
        else {
            throw runtime_error("Недопустимый символ в сообщении");
        }
    }
    return result;
}

string decrypt(string message, int key) {
    string result = "";

    for (int i = 0; i < message.length(); ++i) {
        // если символ - буква нижнего регистра
        if (islower(message[i])) {
            char c = (message[i] - key - 'a');
            if (c < 'a') {
                c += 26;
            }
            result += c;
        }
        // если символ - буква верхнего регистра
        else if (isupper(message[i])) {
            char c = (message[i] - key - 'A');
            if (c < 'A') {
                c += 26;
            }
            result += c;
        }
        // если символ - не буква, то его не меняем
        else {
            result += message[i];
        }
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
    setlocale(LC_ALL, "Russian");
    string message, password;
    int key;
    char answer; 
 
    cout << "Введите исходный текст: "; 
    getline(cin, message); 
 
    write_to_file("source.txt", message);
    password = get_password();
    // шифрование   
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
}
