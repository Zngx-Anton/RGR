#include <iostream>
#include <cmath>
#include <string>

using namespace std;
int main() {
    string s = "abcdefghijklmnopqrstuvw";
    int u = s.length();
    int m;
    m = ceil(sqrt(u));
    char A[1000][1000];
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (k < u) {
                A[i][j] = s[k];
                k++;
            }
            else {
                A[i][j] = ' ';
            }
        }
    }
    int i, j, n = 0;
    if (m % 2 == 1) {
        i = sqrt(s.length()) / 2, j = sqrt(s.length()) / 2;
        do {
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j--];

            if (n == sqrt(s.length()))
                break;
            for (int k = 0; k < n; k++)
                cout << A[i++][j];
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j++];
            for (int k = 0; k < n; k++)
                cout << A[i--][j];
        } while (n);
    }
    else {
        i = sqrt(s.length()) / 2, j = (sqrt(s.length()) / 2) - 1;
        do {
            n++;
            for (int k = 0; k < n; k++)
                cout << A[i][j++];
            for (int k = 0; k < n; k++)
                cout << A[i--][j];
            n++;

            for (int k = 0; k < n; k++)
                cout << A[i][j--];

            if (n == sqrt(s.length()))
                break;
            for (int k = 0; k < n; k++)
                cout << A[i++][j];
        } while (n);
    }
    return 0;
}