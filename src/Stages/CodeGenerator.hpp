#ifndef COMPILERPROJECT_CODEGENERATOR_HPP
#define COMPILERPROJECT_CODEGENERATOR_HPP
#include <functional>
#include "../Types/Parsing/AST.hpp"

class CodeGenerator {
    //what does this do?
    // takes in an AST and generates the x86 assembly for it
public:

    void Generate(const AST & ast, const string & fname);

private:

    void Generate(SyntaxNode & snode, std::ofstream & file);

    void WriteFunction(FunctionNode & fnode, std::ofstream & file);

    void WriteToRegister(const std::string & reg, ConstantNode & cnode, std::ofstream & file);

    void WriteReturn(ReturnNode & rnode, std::ofstream & file);
};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
