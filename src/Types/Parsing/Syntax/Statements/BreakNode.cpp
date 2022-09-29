#include "BreakNode.hpp"

BreakNode::BreakNode() : StatementNode(SyntaxType::Break) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string BreakNode::PrettyPrint() {
    return "Break";
}
