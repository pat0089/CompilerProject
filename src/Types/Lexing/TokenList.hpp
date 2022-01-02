#ifndef COMPILERPROJECT_TOKENLIST_HPP
#define COMPILERPROJECT_TOKENLIST_HPP
#include <iostream>
#include "Tokens/Token.hpp"

using std::istream;
using std::ostream;

class Token;

enum class TokenType;
enum class KeywordType;
enum class SymbolType;


class TokenList {
public:
    TokenList();
    explicit TokenList(Token * tokens);
    ~TokenList();
    TokenList(const TokenList & toCopy);

    //Tokens are always added to the end of the list
    void AddToken(Token * token);

    //Used for parsing
    Token * PopFront();
    void PutbackFront(Token * token);

    //get the type of the frontmost token
    TokenType PeekType() const;
    Token * PeekFront();

    //returns a nullptr-terminated list of tokens from the front until the type of token is found, inclusive
    Token * SeekAndPop(TokenType type);
    Token * SeekSymbolPop(SymbolType stype);

    //returns the pointer to the next typed token in the list
    Token * SeekTo(TokenType type) const;
    Token * SeekToNextSymbol(SymbolType stype) const;
    Token * SeekToNextSymbol() const;
    Token * SeekToNextLiteral() const;
    Token * SeekToNextKeyword(KeywordType ktype) const;
    Token * SeekToNextKeyword() const;
    Token * SeekToNextIdentifier() const;

    friend std::istream & operator >> (std::istream & is, TokenList & tokenList);
    friend std::ostream & operator << (std::ostream & os, const TokenList & tokenList);

private:
    Token * _front;
    Token * _back;

    //returns a nullptr-terminated list of tokens from the front until the token is found, inclusive
    Token * PopFromFront(Token * token);
};

#endif //COMPILERPROJECT_TOKENLIST_HPP
