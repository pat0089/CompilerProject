#ifndef COMPILERPROJECT_TOKEN_H
#define COMPILERPROJECT_TOKEN_H
#include <regex>
#include <string>

using namespace std;

class Token {

public:

    Token();
    explicit Token(string chars);

    enum Type { None, Number, Keyword, String };
    Type type;

    string GetChars();

private:
    string _readCharacters;
};


#endif //COMPILERPROJECT_TOKEN_H
