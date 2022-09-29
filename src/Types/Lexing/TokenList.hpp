#ifndef COMPILERPROJECT_TOKENLIST_HPP
#define COMPILERPROJECT_TOKENLIST_HPP
#include <set>
#include <deque>
#include <iostream>
#include "Tokens/Token.hpp"

class Token;

enum class TokenType;
enum class KeywordType;
enum class SymbolType;


class TokenList {
public:
    TokenList();
    ~TokenList();
    TokenList(const TokenList & toCopy);

    //Used for parsing
    Token * PopFront();
    void PutbackFront(Token * t);

    //get the type of the frontmost token
    TokenType PeekType() const;
    Token * PeekFront() const;

    friend std::istream & operator >> (std::istream & is, TokenList & tokenList);
    friend std::ostream & operator << (std::ostream & os, const TokenList & tokenList);

    bool Verify() const;

    Token & operator[] (int i);

    bool Empty();

private:

    std::deque<Token *> *_tokens;
    bool match_all_braces() const;

};

#endif //COMPILERPROJECT_TOKENLIST_HPP
