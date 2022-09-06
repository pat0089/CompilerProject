#include "StatementNode.hpp"

StatementNode::StatementNode() : SyntaxNode(SyntaxType::Statement) {}
StatementNode::StatementNode(SyntaxType stype) : SyntaxNode(stype) {}

std::string StatementNode::PrettyPrint() {
    return std::string("Statement");
}
