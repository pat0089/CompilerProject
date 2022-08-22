#ifndef COMPILERPROJECT_FUNCTIONNODE_HPP
#define COMPILERPROJECT_FUNCTIONNODE_HPP
#include "../../SyntaxNode.hpp"
#include "Parameters.hpp"
#include "../Statements/BodyNode.hpp"

class FunctionNode : public SyntaxNode {
public:

    FunctionNode();
    explicit FunctionNode(std::string toInit);
    std::string & Name() const;
    std::string PrettyPrint() override;
    Parameters & Params() const;
    BodyNode & Body() const;

private:
    std::string * _name;
};


#endif //COMPILERPROJECT_FUNCTIONNODE_HPP
