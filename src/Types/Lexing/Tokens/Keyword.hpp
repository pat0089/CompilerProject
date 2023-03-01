#ifndef COMPILERPROJECT_KEYWORD_HPP
#define COMPILERPROJECT_KEYWORD_HPP
#include "Token.hpp"

enum class KeywordType { None, Return, Int, If, Else, For, While, Do, Break, Continue };

class Keyword : public Token {
public:
    explicit Keyword(const std::string & toInit, int curChar, int curLine);
    Keyword(const Keyword & toCopy);
    ~Keyword() override = default;
    std::string TypeString() const override;
    KeywordType KeyType() const;
    Token * Clone() override;
private:
    KeywordType _keyType;
    static KeywordType GetKeyType(const std::string & rawString);
};


#endif //COMPILERPROJECT_KEYWORD_HPP
