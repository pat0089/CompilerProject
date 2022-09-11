#include "ConditionalExpressionNode.hpp"

ConditionalExpressionNode::ConditionalExpressionNode(ExpressionNode *decision, ExpressionNode *res1, ExpressionNode * res2) : ExpressionNode(SyntaxType::Conditional_Expression) {
    Add(decision);
    Add(res1);
    Add(res2);
}

std::string ConditionalExpressionNode::PrettyPrint() {
    return "Conditional Expression: ";
}
