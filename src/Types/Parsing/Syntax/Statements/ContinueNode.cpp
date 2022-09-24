#include "ContinueNode.hpp"

ContinueNode::ContinueNode() : StatementNode(SyntaxType::Continue) {}

std::string ContinueNode::PrettyPrint() {
    return "Continue";
}
