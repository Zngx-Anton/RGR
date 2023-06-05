#include <iostream>  
#include <fstream>  
#include <algorithm>  
#include <string>  
#include <math.h>   
#include <clocale>
#include <Windows.h>
using namespace std;
string mappedKey;
string text;
void messageAndKey() {
    string msg;
    cout << "Введите текст: ";
    getline(cin, msg);
    

    //message to uppercase
    for (int i = 0; i < msg.length(); i++) {
        msg[i] = toupper(msg[i]);
    }

    string key;
    cout << "Введите ключ: ";
    getline(cin, key);

    //key to uppercase
    for (int i = 0; i < key.length(); i++) {
        key[i] = toupper(key[i]);
    }

    //mapping key to message
    string keyMap = "";
    for (int i = 0, j = 0; i < msg.length(); i++) {
        if (msg[i] == 32) {
            keyMap += 32;
        }
        else {
            if (j < key.length()) {
                keyMap += key[j];
                j++;
            }
            else {
                j = 0;
                keyMap += key[j];
                j++;
            }
        } //if-else
    } //for

    text = msg;
    mappedKey = keyMap;
}

int tableArr[26][26];
void createVigenereTable() {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            int temp;
            if ((i + 65) + j > 90) {
                temp = ((i + 65) + j) - 26;

                //adding ASCII of alphabet letter in table index position
                tableArr[i][j] = temp;
            }
            else {
                temp = (i + 65) + j;

                //adding ASCII of alphabet letter in table index position
                tableArr[i][j] = temp;
            }
        } // for j loop
    } // for i loop

}

string cipherEncryption(string text, string mappedKey) {
    createVigenereTable();
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == 32 && mappedKey[i] == 32) {
            result += " ";
        }
        else {
            int x = (int)text[i] - 65;
            int y = (int)mappedKey[i] - 65;
            result += (char)tableArr[x][y];
        }
    }

    return result;
}

int itrCount(int key, int msg) {
    int counter = 0;
    string result = "";

    //starting from ASCII of letter of Key and ending at letter of message
    // to get full 26 letters of alphabet
    for (int i = 0; i < 26; i++) {
        if (key + i > 90) {
            result += (char)(key + (i - 26));
        }
        else {
            result += (char)(key + i);
        }
    } //for

    for (int i = 0; i < result.length(); i++) {
        if (result[i] == msg) {
            break;
        }
        else {
            counter++;
        }
    }
    return counter;
}

string cipherDecryption(string text, string mappedKey) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == 32 && mappedKey[i] == 32) {
            result += " ";
        }
        else {
            int temp = itrCount((int)mappedKey[i], (int)text[i]);
            result += (char)(65 + temp);
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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string password;
    char answer;

    messageAndKey();

    write_to_file("source.txt", text);

    password = get_password();

    // шифрование  
    if (password == "secret") {
        text = read_from_file("source.txt");
        
        text = cipherEncryption(text, mappedKey);
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
        
        text = cipherDecryption(text, mappedKey);
        write_to_file("decoded.txt", text);
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
