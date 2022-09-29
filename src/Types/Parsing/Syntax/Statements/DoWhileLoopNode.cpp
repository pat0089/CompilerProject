#include "DoWhileLoopNode.hpp"

DoWhileLoopNode::DoWhileLoopNode(StatementNode *statement, ExpressionNode *exp) : WhileLoopNode(SyntaxType::Do_While_Loop) {
    Add(statement);
    Add(exp);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string DoWhileLoopNode::PrettyPrint() {
    return "Do-While Loop: ";
}
