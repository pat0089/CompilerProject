#include "ConditionalExpressionNode.hpp"

ConditionalExpressionNode::ConditionalExpressionNode(ExpressionNode *decision, ExpressionNode *res1, ExpressionNode * res2) : ExpressionNode(SyntaxType::Conditional_Expression) {
    Add(decision);
    Add(res1);
    Add(res2);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string ConditionalExpressionNode::PrettyPrint() {
    return "Conditional Expression: ";
}
