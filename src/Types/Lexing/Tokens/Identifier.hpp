#ifndef COMPILERPROJECT_IDENTIFIER_HPP
#define COMPILERPROJECT_IDENTIFIER_HPP
#include "Token.hpp"

class Identifier : public Token {
public:
    explicit Identifier(const std::string & toInit);
    std::string TypeString() const override;
    Token * Clone() override;
    Identifier(const Identifier & toCopy) = default;
};


#endif //COMPILERPROJECT_IDENTIFIER_HPP
