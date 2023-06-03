#include <iostream>
#include <string>

using namespace std;

string atbash(string message) {
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        if (isupper(message[i])) {
            result += char('Z' - (message[i] - 'A'));
        }
        else if (islower(message[i])) {
            result += char('z' - (message[i] - 'a'));
        }
        else {
            result += message[i];
        }
    }
    return result;
}

int main() {
    string message;
    cout << "Enter message to encrypt using Atbash cipher: ";
    getline(cin, message);
    cout << "Encrypted message: " << atbash(message) << endl;
    return 0;
}
