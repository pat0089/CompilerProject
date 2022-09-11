#include "ConditionalStatementNode.hpp"

ConditionalStatementNode::ConditionalStatementNode(ExpressionNode *exp, StatementNode *snode, StatementNode *option) : StatementNode(SyntaxType::Conditional_Statement) {
    Add(exp);
    Add(snode);
    if (option) Add(option);
}

std::string ConditionalStatementNode::PrettyPrint() {
    return "Conditional Statement: ";
}
