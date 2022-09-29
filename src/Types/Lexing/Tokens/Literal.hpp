#ifndef COMPILERPROJECT_LITERAL_HPP
#define COMPILERPROJECT_LITERAL_HPP
#include "Token.hpp"

class Literal : public Token {
public:
    explicit Literal(const std::string & toInit);
    std::string TypeString() const override;
    Token * Clone() override;
    Literal(const Literal & toCopy) = default;
};


#endif //COMPILERPROJECT_LITERAL_HPP
