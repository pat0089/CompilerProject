#include "DeclarationNode.hpp"

DeclarationNode::DeclarationNode() : StatementNode(SyntaxType::Declaration), IVariable("") {}

DeclarationNode::DeclarationNode(const std::string &name, ExpressionNode *option_expr) : StatementNode(SyntaxType::Declaration), IVariable(name) {
    if (option_expr) Add(option_expr);
}

std::string DeclarationNode::PrettyPrint() {
    return "Declaration: " + GetVariableName();
}