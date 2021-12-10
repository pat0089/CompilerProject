#ifndef COMPILERPROJECT_LEXER_HPP
#define COMPILERPROJECT_LEXER_HPP
#include <regex>
#include <string>
#include <iostream>

//thanks to https://stackoverflow.com/questions/16749069/c-split-string-by-regex/16752826#answer-28142357

class Lexer {
public:
    const static std::regex isKeyword;
    const static std::regex isIdentifier;
    const static std::regex isParenthesis;
    const static std::regex isBrace;
    const static std::regex isSemicolon;
    const static std::regex isLiteral_int;
    const static std::regex isSymbol;
private:
};


#endif //COMPILERPROJECT_LEXER_HPP
