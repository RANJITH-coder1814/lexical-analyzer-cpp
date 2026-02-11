#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

bool isKeyword(const string &word) {
    string keywords[] = {
        "int","float","double","char","if","else","for","while",
        "do","break","continue","return","void","switch","case"
    };
    for (string k : keywords)
        if (k == word) return true;
    return false;
}

bool isOperator(char ch) {
    string op = "+-*/%=<>!";
    return op.find(ch) != string::npos;
}

bool isSeparator(char ch) {
    string sep = "(),;{}[]";
    return sep.find(ch) != string::npos;
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Error opening file!\n";
        return 1;
    }

    char ch;
    string buffer;

    cout << "=========== LEXICAL ANALYZER OUTPUT ===========\n\n";

    while (file.get(ch)) {

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            buffer = ch;
            while (file.get(ch) && (isalnum(ch) || ch == '_'))
                buffer += ch;

            if (isKeyword(buffer))
                cout << "Keyword     : " << buffer << endl;
            else
                cout << "Identifier  : " << buffer << endl;

            file.unget();
        }

        // Number
        else if (isdigit(ch)) {
            buffer = ch;
            while (file.get(ch) && isdigit(ch))
                buffer += ch;

            cout << "Number      : " << buffer << endl;
            file.unget();
        }

        // Operator
        else if (isOperator(ch)) {
            cout << "Operator    : " << ch << endl;
        }

        // Separator
        else if (isSeparator(ch)) {
            cout << "Separator   : " << ch << endl;
        }
    }

    file.close();
    return 0;
}
