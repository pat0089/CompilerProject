#ifndef COMPILERPROJECT_TOKENLIST_HPP
#define COMPILERPROJECT_TOKENLIST_HPP
#include <set>
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

    //Tokens are always added to the end of the list
    void AddToken(Token * token);

    //Used for parsing
    Token * PopFront();

    //get the type of the frontmost token
    TokenType PeekType() const;
    Token * Front() const;

    //returns a reference to the next typed token in the list
    Token * SeekToNext(TokenType type, Token * from = nullptr);

    TokenList * SeekToPop(Token * toPopAfter);

    Token * SeekToNextSymbol();
    Token * SeekToNextLiteral();
    Token * SeekToNextKeyword();
    Token * SeekToNextIdentifier();

    Token * SeekToNextSymbol(SymbolType stype);
    Token * SeekToNextKeyword(KeywordType ktype);

    friend std::istream & operator >> (std::istream & is, TokenList & tokenList);
    friend std::ostream & operator << (std::ostream & os, const TokenList & tokenList);

private:

    std::deque<Token *>  *_tokens;

};

#endif //COMPILERPROJECT_TOKENLIST_HPP
