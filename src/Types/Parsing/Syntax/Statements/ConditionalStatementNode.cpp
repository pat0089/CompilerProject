#include "ConditionalStatementNode.hpp"

ConditionalStatementNode::ConditionalStatementNode(ExpressionNode *exp, StatementNode *snode, StatementNode *option) : StatementNode(SyntaxType::Conditional_Statement) {
    Add(exp);
    Add(snode);
    if (option) Add(option);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string ConditionalStatementNode::PrettyPrint() {
    return "Conditional Statement: ";
}
