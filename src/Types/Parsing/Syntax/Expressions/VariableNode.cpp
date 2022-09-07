#include "VariableNode.hpp"

VariableNode::VariableNode() : ExpressionNode(SyntaxType::Variable), IVariable("") {}
VariableNode::VariableNode(const std::string &name) : ExpressionNode(SyntaxType::Variable), IVariable(name) {}

std::string VariableNode::PrettyPrint() {
    return "Variable: " + GetVariableName();
}
