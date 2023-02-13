#ifndef COMPILERPROJECT_LEXER_HPP
#define COMPILERPROJECT_LEXER_HPP
#include <regex>
#include <string>
#include <iostream>
#include "../Types/Lexing/TokenList.hpp"
class TokenList;
//thanks to https://stackoverflow.com/questions/16749069/c-split-string-by-regex/16752826#answer-28142357

class Lexer {
public:

    Lexer();
    ~Lexer();

    //Lexer regexes
    const static std::regex isKeyword;
    const static std::regex isIdentifier;
    const static std::regex isLiteral;
    const static std::regex isSymbol;

    //Lexing functionality
    void Lex(std::istream & is);

    bool Verify();

    friend std::istream & operator >> (std::istream & is, Lexer & lexer);
    friend std::ostream & operator << (std::ostream & os, const Lexer & lexer);

    //Post-Lex list
    const TokenList & GetList() const;
    static std::string LexNextToken(std::istream & is);

    static int GetCurChar();
    static int GetCurLine();

private:
    TokenList * _tokens;
    bool _verified = false;
    static int _line;
    static int _char;
};


#endif //COMPILERPROJECT_LEXER_HPP
