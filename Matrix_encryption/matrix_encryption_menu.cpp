#include <iostream>   
#include <fstream>   
#include <algorithm>   
#include <string>   
#include <math.h>    
using namespace std; 
 
string e(string text) { 
    int u = text.length(); 
    int m; 
    m = ceil(sqrt(u)); 
    int k = 0; 
    string result1 = ""; 
    string result = ""; 
    for (int i = 0; i < m; i++) { 
        for (int j = 0; j < m; j++) { 
            if (k < u) { 
                result1 += text[k]; 
                k++; 
            } 
            else { 
                result1 += ' '; 
            } 
        } 
    } 
    char A[1000][1000]; 
    int i, j, n = 0; 
 
    for (int arr = 0; arr < sqrt(result1.length()); arr++) 
    { 
        for (int idx = 0; idx < sqrt(result1.length()); idx++) 
        { 
            A[arr][idx] = result1[idx + (arr * sqrt(result1.length()))]; 
        } 
    } 
    if (m % 2 == 1) { 
        i = sqrt(result1.length()) / 2, j = sqrt(result1.length()) / 2; 
        do { 
            n++; 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i][j--]); 
 
            if (n == sqrt(result1.length())) 
                break; 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i++][j]); 
            n++; 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i][j++]); 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i--][j]); 
        } while (n); 
    } 
    else { 
        i = sqrt(result1.length()) / 2, j = (sqrt(result1.length()) / 2) - 1; 
        do { 
            n++; 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i][j++]); 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i--][j]); 
            n++; 
 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i][j--]); 
 
            if (n == sqrt(result1.length())) 
                break; 
            for (int k = 0; k < n; k++) 
                result.push_back(A[i++][j]); 
        } while (n); 
    } 
    return result; 
} 
string d(string text) { 
    reverse(text.begin(), text.end()); 
    int u = text.length(); 
    int m; 
    m = ceil(sqrt(u)); 
    char** A = new char* [m]; 
    for (int i = 0; i < m; i++) 
        A[i] = new char[m]; 
    int top = 0, bottom = m - 1, left = 0, right = m - 1; 
    int n = 0; 
    while (n < text.length()) { 
        for (int i = left; i <= right && n < text.length(); i++) { 
            A[top][i] = text[n++]; 
        } 
        top++; 
        for (int i = top; i <= bottom && n < text.length(); i++) { 
            A[i][right] = text[n++]; 
        } 
        right--; 
        for (int i = right; i >= left && n < text.length(); i--) { 
            A[bottom][i] = text[n++]; 
        } 
        bottom--; 
        for (int i = bottom; i >= top && n < text.length(); i--) { 
            A[i][left] = text[n++]; 
        } 
        left++; 
    } 
 
    string result = ""; 
    for (int i = 0; i < m; i++) { 
        for (int j = 0; j < m; j++) { 
            result += A[i][j]; 
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
    string text, password; 
    char answer; 
 
    cout << "Введите исходный текст: "; 
    getline(cin, text); 
 
    write_to_file("source.txt", text); 
 
    password = get_password(); 
 
    // шифрование   
    if (password == "secret") { 
        text = read_from_file("source.txt"); 
        text = e(text); 
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
        text = d(text); 
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
