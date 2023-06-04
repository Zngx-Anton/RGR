#include <algorithm>  
#include <iostream>  
#include <string>  
#include <locale>  
using namespace std;
string atbash(string s) {
    string result = "";
    string a = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string b = a;
    reverse(b.begin(), b.end());
    string A = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    string B = A;
    reverse(B.begin(), B.end());
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (a.find(c) != string::npos) { //если символ существует в строке "а"
            int index = a.find(c); //ищем его индекс
            c = b[index]; //находим символ на зеркальной стороне
        }
        else if (A.find(c) != string::npos) { //для символов в верхнем регистре
            int index = A.find(c);
            c = B[index];
        }
        result += c; //собираем результат
    }
    return result;
}
int main() {
    setlocale(LC_ALL, "Rus");
    string plaintext = "Привет, мир!";
    string ciphertext = atbash(plaintext);
    cout << "Исходный текст: " << plaintext << endl;
    cout << "Шифротекст: " << ciphertext << endl;
    return 0;
}
