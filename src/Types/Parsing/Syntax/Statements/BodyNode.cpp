#include "BodyNode.hpp"
using std::string;

string BodyNode::PrettyPrint() {
    return "Body:";
}

BodyNode::BodyNode() : SyntaxNode(SyntaxType::Body) {}
