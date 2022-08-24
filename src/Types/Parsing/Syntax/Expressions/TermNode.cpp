#include "TermNode.hpp"

TermNode::TermNode() : ExpressionNode(SyntaxType::Term) {}
TermNode::TermNode(SyntaxType stype) : ExpressionNode(stype) {}