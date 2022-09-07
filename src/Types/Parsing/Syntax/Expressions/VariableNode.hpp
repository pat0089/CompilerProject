#ifndef COMPILERPROJECT_VARIABLENODE_HPP
#define COMPILERPROJECT_VARIABLENODE_HPP
#include "ExpressionNode.hpp"
#include "IVariable.hpp"

class VariableNode : public ExpressionNode, public IVariable {
public:
    VariableNode();
    explicit VariableNode(const std::string & name);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_VARIABLENODE_HPP
