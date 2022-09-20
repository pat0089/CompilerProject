#include "BreakNode.hpp"

BreakNode::BreakNode() : StatementNode(SyntaxType::Break) {}

std::string BreakNode::PrettyPrint() {
    return "Break";
}
