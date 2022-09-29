#include "WhileLoopNode.hpp"

WhileLoopNode::WhileLoopNode(ExpressionNode *exp, StatementNode *statement) : StatementNode(SyntaxType::While_Loop) {
    Add(exp);
    Add(statement);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string WhileLoopNode::PrettyPrint() {
    return "While Loop: ";
}

WhileLoopNode::WhileLoopNode(SyntaxType stype) : StatementNode(stype) {}
