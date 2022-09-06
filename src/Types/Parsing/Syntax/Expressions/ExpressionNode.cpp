#include "ExpressionNode.hpp"
ExpressionNode::ExpressionNode() : StatementNode(SyntaxType::Expression) {}
ExpressionNode::ExpressionNode(SyntaxType stype) : StatementNode(stype) {}

std::string ExpressionNode::PrettyPrint() {
    return "Expression";
}
