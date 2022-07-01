#ifndef COMPILERPROJECT_CODEGENERATOR_HPP
#define COMPILERPROJECT_CODEGENERATOR_HPP
#include "../Types/Parsing/AST.hpp"

class CodeGenerator {
    //what does this do?
    // takes in an AST and generates the x86 assembly for it
public:

    void Generate(const AST & ast, const string & fname);

private:

    void Generate(SyntaxNode & snode, std::ofstream & file);

};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
