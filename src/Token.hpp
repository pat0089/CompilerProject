#ifndef COMPILERPROJECT_TOKEN_HPP
#define COMPILERPROJECT_TOKEN_HPP
#include <string>
#include <iostream>
#include "Lexer.hpp"
class Lexer;

class Token {

public:

    enum Type {None, Keyword, Identifier, Parenthesis, Brace, Semicolon, Literal_int};

    Token();
    Token(const std::string& chars, const Type& type);
    explicit Token(const std::string & chars);
    std::string GetRaw() const;
    Type GetType() const;
    std::string TypeString() const;

    friend std::istream & operator >> (std::istream & is, Token & token);
    friend std::ostream & operator << (std::ostream & os, Token & token);


protected:

    std::string _readCharacters;
    Type _type;

    static Type ParseType(const std::string & toParse);
    void Set(const std::string & toSet);
};


#endif //COMPILERPROJECT_TOKEN_HPP
