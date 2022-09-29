#include "ExpressionNode.hpp"
ExpressionNode::ExpressionNode() : StatementNode(SyntaxType::Expression) {}
ExpressionNode::ExpressionNode(SyntaxType stype) : StatementNode(stype) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string ExpressionNode::PrettyPrint() {
    return "Expression";
}
