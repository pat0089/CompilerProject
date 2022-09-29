#include "VariableReferenceNode.hpp"

VariableReferenceNode::VariableReferenceNode() : ExpressionNode(SyntaxType::Variable_Reference), IVariable("") {}
VariableReferenceNode::VariableReferenceNode(const std::string &name) : ExpressionNode(SyntaxType::Variable_Reference), IVariable(name) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string VariableReferenceNode::PrettyPrint() {
    return "Variable Reference: " + GetVariableName();
}
