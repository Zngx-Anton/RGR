#include <iostream>
#include <cmath>
#include <string>

using namespace std;
int main() {
    string s = "abcdefghijklmnopqrstuvwx";
    int n = s.length();
    int m;
    m = ceil(sqrt(n));
    char A[1000][1000];

    // Filling the matrix with string characters
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (k < n) {
                A[i][j] = s[k];
                k++;
            }
            else {
                A[i][j] = ' ';
            }
        }
    }

    // Matrix output
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}