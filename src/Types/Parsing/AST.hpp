#ifndef COMPILERPROJECT_AST_HPP
#define COMPILERPROJECT_AST_HPP
#include "SyntaxNode.hpp"
#include "Syntax/ParsedNodes.hpp"
#include <string>
using std::string;
class AST {
public:
    //returns a reference to the ProgramNode of the AST
    ProgramNode * Program() const;

    void Program(ProgramNode * main);
    friend std::ostream & operator << (std::ostream & os, const AST & ast);


private:
    SyntaxNode * _head = nullptr;
    void recursiveOutput(const SyntaxNode * snode, std::ostream & os, int layer) const;
    void outputNode(const SyntaxNode * snode, std::ostream & os) const;
};


#endif //COMPILERPROJECT_AST_HPP
