#include "Token.hpp"

Token::Token() {
    _readCharacters = "";
    type = None;
}

bool isKeyword(string toCheck) {
    return (toCheck == "int" ||
            toCheck == "return");
}

Token::Token(string chars) {
    _readCharacters = chars;
    //thanks to https://www.regular-expressions.info/floatingpoint.html for the regex for all types of numbers
    regex isNumber("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
    if (regex_match(_readCharacters, isNumber)) {
        type = Number;
    } else if (_readCharacters.empty()) {
        type = None;
    } else if (isKeyword(_readCharacters)) {
        type = Keyword;
    } else {
        type = String;
    }
}

string Token::GetChars() {
    return _readCharacters;
}


