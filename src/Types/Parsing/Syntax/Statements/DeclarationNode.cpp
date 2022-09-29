#include "DeclarationNode.hpp"

DeclarationNode::DeclarationNode() : StatementNode(SyntaxType::Declaration), IVariable("") {}

DeclarationNode::DeclarationNode(const std::string &name, ExpressionNode *option_expr) : StatementNode(SyntaxType::Declaration), IVariable(name) {
    if (option_expr) Add(option_expr);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string DeclarationNode::PrettyPrint() {
    return "Declaration: " + GetVariableName();
}