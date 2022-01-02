#ifndef COMPILERPROJECT_PROGRAMNODE_HPP
#define COMPILERPROJECT_PROGRAMNODE_HPP
#include "FunctionNode.hpp"
#include "../../SyntaxNode.hpp"

class ProgramNode : public SyntaxNode {
public:
    explicit ProgramNode(FunctionNode * main);
    FunctionNode & Main() const;
    std::string PrettyPrint() override;

    FunctionNode & operator[](int i) const;

protected:
    FunctionNode * _main;
};

#endif //COMPILERPROJECT_PROGRAMNODE_HPP
