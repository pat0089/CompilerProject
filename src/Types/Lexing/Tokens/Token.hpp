#ifndef COMPILERPROJECT_TOKEN_HPP
#define COMPILERPROJECT_TOKEN_HPP
#include <string>
#include <iostream>
#include "../../../Stages/Lexer.hpp"

enum class TokenType { None, Identifier, Keyword, Literal, Symbol };

class Token {

public:

    TokenType Type() const;

    std::string & GetRaw() const;

    friend std::ostream & operator << (std::ostream & os, const Token & token);
    bool operator == (const Token & token) const;

    //Factory function for Token subtypes
    static Token * Create(const std::string & rawString, int curChar, int curLine);

    //copy constructor for derived members
    virtual Token * Clone() = 0;
    Token(const Token & toCopy);

    virtual ~Token();

    virtual std::string TypeString() const = 0;

    int GetChar() const;
    int GetLine() const;

protected:

    std::string * _readCharacters;

    TokenType _tokenType;

    static TokenType GetType(const std::string & rawString);

    Token();
    explicit Token(const std::string & chars, int curChar, int curLine);

    int _line = 0;
    int _char = 0;

};

#endif //COMPILERPROJECT_TOKEN_HPP
