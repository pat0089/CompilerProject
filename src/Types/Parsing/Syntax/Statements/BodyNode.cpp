#include "BodyNode.hpp"
using std::string;

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string BodyNode::PrettyPrint() {
    return "Body:";
}

BodyNode::BodyNode() : SyntaxNode(SyntaxType::Body) {}
