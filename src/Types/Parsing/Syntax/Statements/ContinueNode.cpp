#include "ContinueNode.hpp"

ContinueNode::ContinueNode() : StatementNode(SyntaxType::Continue) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string ContinueNode::PrettyPrint() {
    return "Continue";
}
