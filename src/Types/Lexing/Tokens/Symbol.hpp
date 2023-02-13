#ifndef COMPILERPROJECT_SYMBOL_HPP
#define COMPILERPROJECT_SYMBOL_HPP
#include "Token.hpp"

enum class SymbolType { None , Semicolon, Colon, Question_Mark,
    Open_Parenthesis, Close_Parenthesis,
    Open_Brace, Close_Brace,
    Open_Bracket, Close_Bracket,
    Open_Chevron, Close_Chevron,
    Period, Comma, Equals,
    Plus, Minus, ForwardSlash,
    Asterisk, BackSlash, And,
    Hashmark, Exclaimation, Tilde,
    Vertical_Line, Carrot, Percent,
};

class Symbol : public Token {
public:
    explicit Symbol(const std::string & toInit, int curChar, int curLine);
    Symbol(const Symbol & toCopy);
    std::string TypeString() const override;
    SymbolType SymType() const;
    static std::string GetString(SymbolType stype);
    Token * Clone() override;
private:
    SymbolType _symType;
    static SymbolType GetSymType(const std::string & rawString);
};


#endif //COMPILERPROJECT_SYMBOL_HPP
