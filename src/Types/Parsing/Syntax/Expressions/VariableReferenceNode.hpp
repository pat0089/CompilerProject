#ifndef COMPILERPROJECT_VARIABLEREFERENCENODE_HPP
#define COMPILERPROJECT_VARIABLEREFERENCENODE_HPP
#include "ExpressionNode.hpp"
#include "IVariable.hpp"

class VariableReferenceNode : public ExpressionNode, public IVariable {
public:
    VariableReferenceNode();
    explicit VariableReferenceNode(const std::string & name);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_VARIABLEREFERENCENODE_HPP
