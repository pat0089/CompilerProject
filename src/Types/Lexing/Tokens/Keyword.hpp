#ifndef COMPILERPROJECT_KEYWORD_HPP
#define COMPILERPROJECT_KEYWORD_HPP
#include "Token.hpp"

enum class KeywordType { None, Return, Int, If, Else };

class Keyword : public Token {
public:
    explicit Keyword(const std::string & toInit);
    Keyword(const Keyword & toCopy);
    ~Keyword();
    std::string TypeString() const override;
    KeywordType KeyType() const;
    Token * Clone() override;
private:
    KeywordType _keyType;
    static KeywordType GetKeyType(const std::string & rawString);
};


#endif //COMPILERPROJECT_KEYWORD_HPP
