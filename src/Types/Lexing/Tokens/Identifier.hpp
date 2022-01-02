#ifndef COMPILERPROJECT_IDENTIFIER_HPP
#define COMPILERPROJECT_IDENTIFIER_HPP
#include "Token.hpp"

class Identifier : public Token {
public:
    explicit Identifier(const std::string & toInit);
    std::string TypeString() const override;
};


#endif //COMPILERPROJECT_IDENTIFIER_HPP
