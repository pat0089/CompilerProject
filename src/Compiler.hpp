#ifndef COMPILERPROJECT_COMPILER_HPP
#define COMPILERPROJECT_COMPILER_HPP
#include <iostream>
#include <string>
#include <vector>
#include "Token.hpp"

class Compiler {
public:
    std::vector<Token> Lex(std::string toLex);
    std::vector<Token> Lex(std::istream & is);
};

#endif //COMPILERPROJECT_COMPILER_HPP
