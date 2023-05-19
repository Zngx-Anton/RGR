// шифровка
#include <iostream>  
#include <string> 
#include <math.h> 
using namespace std;
int main() {
    string str = "abcdefghijklmnop";
    int a;
    a = sqrt(str.length());
    char A[1000][1000];
    int i, j, n = 0;
    for (int arr = 0; arr < sqrt(str.length()); arr++)
    {
        for (int idx = 0; idx < sqrt(str.length()); idx++)
        {
            A[arr][idx] = str[idx + (arr * sqrt(str.length()))];
        }
    }
    if (a % 2 == 1) {
        i = sqrt(str.length()) / 2, j = sqrt(str.length()) / 2;
        do {
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j++];

            if (n == sqrt(str.length()))
                break;
            for (int k = 0; k < n; k++)
                cout << A[i--][j];
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j--];
            for (int k = 0; k < n; k++)
                cout << A[i++][j];
        } while (n);
    }
    else {
        i = 2, j = 1;
        do {
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j++];
            for (int k = 0; k < n; k++)
                cout << A[i--][j];
            n++;

            for (int k = 0; k < n; k++)
                cout << A[i][j--];

            if (n == sqrt(str.length()))
                break;
            for (int k = 0; k < n; k++)
                cout << A[i++][j];
        } while (n);
    }
}
