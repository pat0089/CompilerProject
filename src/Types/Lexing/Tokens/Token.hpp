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
    void SetRaw(const std::string & toSet);

    friend std::ostream & operator << (std::ostream & os, const Token & token);
    bool operator == (const Token & token) const;

    //Factory function for Token subtypes
    static Token * Create(const std::string & rawString);

    Token(const Token & toCopy);
    ~Token();

    virtual std::string TypeString() const = 0;

protected:

    std::string * _readCharacters;

    TokenType _tokenType;

    static TokenType GetType(const std::string & rawString);

    Token();
    explicit Token(const std::string & chars);

};

#endif //COMPILERPROJECT_TOKEN_HPP
