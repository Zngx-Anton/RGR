#include <iostream>
#include <string>
using namespace std;

int main() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string reverse_alphabet = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

    string message;
    getline(cin, message);

    // We go through each letter in the message
    for (int i = 0; i < message.length(); i++) {
        // If the letter is a letter of the English alphabet
        if (isalpha(message[i])) {
            // We determine its index in the alphabet
            int index = alphabet.find(toupper(message[i]));
            // Replace with a letter from the replacement alphabet
            message[i] = reverse_alphabet[index];
        }
    }

    cout << "Encrypted message: " << message << endl;

    return 0;
}