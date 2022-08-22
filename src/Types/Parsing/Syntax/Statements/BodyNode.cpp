#include "BodyNode.hpp"
using std::string;

string BodyNode::PrettyPrint() {
    return string("Body:");
}

BodyNode::BodyNode() : SyntaxNode(SyntaxType::Body) {}
