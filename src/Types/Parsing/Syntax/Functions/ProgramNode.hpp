#ifndef COMPILERPROJECT_PROGRAMNODE_HPP
#define COMPILERPROJECT_PROGRAMNODE_HPP
#include "FunctionNode.hpp"
#include "../../SyntaxNode.hpp"

class ProgramNode : public SyntaxNode {
public:
    ProgramNode();

    std::string PrettyPrint() override;

};

#endif //COMPILERPROJECT_PROGRAMNODE_HPP
