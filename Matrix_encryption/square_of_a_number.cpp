#include <iostream>   
#include <string>  
#include <math.h>  

using namespace std;
int main() {
    string str = "abcdefghijklmnopqrstuvwx";
    int a;
    a = sqrt(str.length());
    char A[1000][1000];
    int i, j, n = 0;

    int root = static_cast<int>(a);
    if (pow(root, 2) == str.length()) {
        cout << "The number of elements in a row is the square of the number" << endl;
    }
    else {
        cout << "The number of elements in a row is not the square of a number" << endl;
    }
}