#include "DoWhileLoopNode.hpp"

DoWhileLoopNode::DoWhileLoopNode(StatementNode *statement, ExpressionNode *exp) : WhileLoopNode(SyntaxType::Do_While_Loop) {
    Add(statement);
    Add(exp);
}

std::string DoWhileLoopNode::PrettyPrint() {
    return "Do-While Loop: ";
}
