#ifndef COMPILERPROJECT_KEYWORD_HPP
#define COMPILERPROJECT_KEYWORD_HPP
#include "Token.hpp"

enum class KeywordType { None , Return, Int };

class Keyword : public Token {
public:
    explicit Keyword(const std::string & toInit);
    std::string TypeString() const override;
    KeywordType KeyType() const;
private:
    KeywordType _keyType;
    static KeywordType GetKeyType();
};


#endif //COMPILERPROJECT_KEYWORD_HPP
