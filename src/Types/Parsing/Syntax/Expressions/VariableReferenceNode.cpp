#include "VariableReferenceNode.hpp"

VariableReferenceNode::VariableReferenceNode() : ExpressionNode(SyntaxType::Variable_Reference), IVariable("") {}
VariableReferenceNode::VariableReferenceNode(const std::string &name) : ExpressionNode(SyntaxType::Variable_Reference), IVariable(name) {}

std::string VariableReferenceNode::PrettyPrint() {
    return "Variable_Reference: " + GetVariableName();
}
