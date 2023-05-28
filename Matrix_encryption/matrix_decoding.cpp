#include <iostream> 
#include <string> 
#include <vector> 
#include <cmath>
#include <algorithm> 
using namespace std;

int main() {
    string s = "mlqrsnihgfkpuvwxytojedcba";

    string str = s;
    reverse(str.begin(), str.end());
    int u = str.length();
    int m;
    m = ceil(sqrt(u));// dimension of the matrix 
    char** A = new char* [m];
    for (int i = 0; i < m; i++)
        A[i] = new char[m];
    int top = 0, bottom = m - 1, left = 0, right = m - 1; // matrix boundaries
    int n = 0; // index of the character in the string 
    while (n < str.length()) {
        for (int i = left; i <= right && n < str.length(); i++) { // fill in the top line
            A[top][i] = str[n++];
        }
        top++;
        for (int i = top; i <= bottom && n < str.length(); i++) { //fill in the right column
            A[i][right] = str[n++];
        }
        right--;
        for (int i = right; i >= left && n < str.length(); i--) { // fill in the bottom line
            A[bottom][i] = str[n++];
        }
        bottom--;
        for (int i = bottom; i >= top && n < str.length(); i--) { // fill in the left column 
            A[i][left] = str[n++];
        }
        left++;
    }
    // we display the contents of the matrix on the screen 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << "";
        }
    }
    return 0;
}