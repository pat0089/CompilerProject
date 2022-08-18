#ifndef COMPILERPROJECT_COMPILER_HPP
#define COMPILERPROJECT_COMPILER_HPP
#include <iostream>
#include <string>
#include <vector>
#include "Stages/Lexer.hpp"
#include "Stages/Parser.hpp"
#include "Stages/CodeGenerator.hpp"

class Compiler {
public:

    Compiler();
    ~Compiler();

    void Lex(std::istream & is);
    void Parse();
    void Generate(const std::string & fname);

    const TokenList & GetLexedList() const;
    const AST & GetAST() const;

    Parser & GetParser() const;
    Lexer & GetLexer() const;
    CodeGenerator & GetCodeGenerator() const;

private:
    Lexer * _lexer;
    Parser * _parser;
    CodeGenerator * _codeGenerator;
} static Compiler;

#endif //COMPILERPROJECT_COMPILER_HPP
