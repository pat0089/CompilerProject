#include <iostream>
#include "src/Token.hpp"
#include <vector>

vector<Token> lex(string readInFile) {
    vector<Token> toReturn;
    istringstream iss(readInFile);
    for (string s; iss >> s;) {
        toReturn.emplace_back(s);
    }
    return toReturn;
}

int main() {
    string hello = "Hello, World! 1234\n+11231244\t-1.0e2 123 \n\n\t";
    vector<Token> lexed = lex(hello);
    cout << hello << endl;

    for (int i = 0; i < lexed.size(); i++) {
        switch (lexed[i].type) {
            case Token::Number:
                cout << "Type: Number\n" + lexed[i].GetChars() << endl;
                break;
            case Token::String:
                cout << "Type: String\n" + lexed[i].GetChars() << endl;
                break;
            case Token::None:
                cout << "Empty Token\n";
                break;
            default:
                cerr << "ERROR: Unknown Token Type!" << endl;
                break;
        }
        cout << endl;
    }
    return 0;
}
