#include <iostream>
#include <string>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string atbash_alphabet = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA";

string atbash_cipher(string input)
{
    string output = "";

    for(char c: input)
    {
        size_t index = alphabet.find(c);

        if(index != string::npos)
        {
            output += atbash_alphabet[index];
        }
        else
        {
            output += c;
        }
    }

    return output;
}

int main()
{
    int choice;
    string message;

    cout << "Menu:\n";
    cout << "1. Encrypt with Atbash cipher\n";
    cout << "2. Decrypt Atbash cipher\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore();

    if(choice == 1)
    {
        cout << "Enter message to encrypt: ";
        getline(cin, message);

        cout << "Encrypted message: " << atbash_cipher(message) << endl;
    }
    else if(choice == 2)
    {
        cout << "Enter message to decrypt: ";
        getline(cin, message);

        cout << "Decrypted message: " << atbash_cipher(message) << endl;
    }
    else
    {
        cout << "Invalid choice.";
    }

    return 0;
}
